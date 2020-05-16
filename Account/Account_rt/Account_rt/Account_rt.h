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
	@ 1.���ݶ�ֲ����
	@ 2.��̬����Ȩ��
	@ ʹ�� model = SIM/REAL ���л�ģ����/ʵ��
	*/
public:
	Account_rt (
		const string& username,
		const string& password,
		const string& model = "SIM",
		const string& broker_name = "PaperTrading",
		const string& trade_host = "mongodb://localhost:27017", //������Ը�Ϊͨ��env��ȡ
		price_t init_cash = 1000000,
		const string& taskid = rt::generate_uuid_v4()
		);
	virtual ~Account_rt() {}

	//δʵ��
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
	//���Լ���
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
	string m_source_id;								//ʶ���
	rt::MARKET_PRESET m_market_preset;
	string m_portfolio;								//QAPapertrade
	string m_model;									//sim
	string m_broker_name;							//�����ڻ���˾
	string m_investor_name;							//ʵ�̵Ŀ���������
	string m_bank_password;
	string m_capital_password;
	string m_wsuri;
	string m_bank_id;								//"SIM"
	string m_bankname;								//"SIMBANK"
	string m_trade_host;
	rt::MongoJob m_db;								//������ֱ�Ӿ���mongodb�����ݿ�����
	string m_pub_host;
	string m_last_updatetime; //û�м������� hku::Datetime
	string m_status;
	string m_trading_day;
	price_t m_init_cash;
	price_t m_pre_balance;
	price_t m_static_balance;
	price_t m_deposit;								//��� (�����д�Ǯ)
	price_t m_withdraw;								//���� (������ȡǮ)
	price_t m_withdrawQuota;						//��ȡ���
	price_t m_close_profit;
	price_t m_premium;								//��ȨȨ����
	string m_event_id;
	string m_task_id;
	price_t m_money;
	//�����ʹ��string���͵�Json�����ʺ�
	rt::JsonJob m_transfers;						//QIFIЭ�飬���������json {}
	rt::JsonJob m_banks;							//{}
	rt::JsonJob m_frozen;							//{}
	rt::JsonJob m_events;							//{}
	map<string, rt::Position_rt> m_positions;		//{}
	rt::JsonJob m_trades;							//{}
	rt::JsonJob m_orders;							//{}
};

