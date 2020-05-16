//2020/05/13
//wfh1300
#pragma once
#include <string>
#include "utilities/Parameter_rt.h"
//#include <iostream>
#include <hikyuu/datetime/Datetime.h>
#include <hikyuu/DataType.h>
#include "utilities/util_rt.h"
#include "Market_Preset.h"
#include "DataBase/MongoJob.h"
#include "utilities/type_rt.h"
#include "utilities/JsonJob.h"
#include "Position_rt.h"

using namespace std;
using namespace hku;
class Account_rt {
	/*
	@ 1.兼容多持仓组合
	@ 2.动态计算权益
	@ 使用 model = SIM/REAL 来切换模拟盘/实盘
	*/
public:
	Account_rt (
		const string& username,
		const string& password,
		const string& model = "SIM",
		const string& broker_name = "PaperTrading",
		const string& trade_host = "mongodb://localhost:27017", //这里可以改为通过env获取
		price_t init_cash = 1000000,
		const string& taskid = rt::generate_uuid_v4()
		);
	virtual ~Account_rt() {}

	//未实现
	void initial();
	void reload();
	void sync();
	void settle();
	void ask_deposit(price_t money);
	void ask_withdraw(price_t money);
	void create_simaccount();
	bool add_position(/*Position_rt? position*/);
	void log(const string& message);
	string open_orders();
	string message();
	string account_msg();
	string position_msg();
	price_t position_profit();
	price_t float_profit();
	price_t frozen_margin();
	string transform_dt(/*string? times*/);
	//惰性计算
	price_t m_available();
	price_t m_margin();
	price_t m_commission();
	price_t m_balance();

	virtual void on_reload();
	virtual void on_sync();

	bool order_check(const string& code, amount_t amount, price_t price, int towards, const string& order_id);
	string send_order(const string& code, amount_t amount, price_t price, int towards, const string& order_id);
	void cancel_order(const string& order_id);
	void make_deal(/*dict order*/);
	void receive_deal(
		const string& code,
		price_t trade_price,
		amount_t trade_amount,
		int trade_towards,
		const string& trade_time,
		const string& order_id,
		const string& trade_id);
	string get_position();
	void on_price_change(const string& code, price_t price);

private:
	string m_user_id;
	string m_user_name;
	string m_password;
	string m_source_id;								//识别号
	rt::MARKET_PRESET m_market_preset;
	string m_portfolio;								//QAPapertrade
	string m_model;									//sim
	string m_broker_name;							//所属期货公司
	string m_investor_name;							//实盘的开户人姓名
	string m_bank_password;
	string m_capital_password;
	string m_wsuri;
	string m_bank_id;								//"SIM"
	string m_bankname;								//"SIMBANK"
	string m_trade_host;
	rt::MongoJob m_db;								//它这里直接就是mongodb的数据库类型
	string m_pub_host;
	string m_last_updatetime; //没有继续采用 hku::Datetime
	string m_status;
	string m_trading_day;
	price_t m_init_cash;
	price_t m_pre_balance;
	price_t m_static_balance;
	price_t m_deposit;								//入金 (向银行存钱)
	price_t m_withdraw;								//出金 (从银行取钱)
	price_t m_withdrawQuota;						//可取金额
	price_t m_close_profit;
	price_t m_premium;								//期权权利金
	string m_event_id;
	string m_task_id;
	price_t m_money;
	//下面的使用string类型的Json更加适合
	rt::JsonJob m_transfers;						//QIFI协议，这里估计是json {}
	rt::JsonJob m_banks;							//{}
	rt::JsonJob m_frozen;							//{}
	rt::JsonJob m_events;							//{}
	map<string, rt::Position_rt> m_positions;		//{}
	rt::JsonJob m_trades;							//{}
	rt::JsonJob m_orders;							//{}
};

