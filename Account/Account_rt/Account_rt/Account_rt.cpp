#include "Account_rt.h"
Account_rt::Account_rt(
	const string& username,
	const string& password,
	const string& model = "SIM",
	const string& broker_name = "PaperTrading",
	const string& trade_host = "mongodb://localhost:27017", //������Ը�Ϊͨ��env��ȡ
	price_t init_cash = 1000000,
	const string& taskid = rt::generate_uuid_v4()
) :
	m_user_id(username),
	m_user_name(username),
	m_password(password),
	m_source_id("QIFI_Account"),
	m_portfolio("PaperTrade"),
	m_model(model),
	m_broker_name(broker_name),
	m_investor_name(""),
	m_bank_password(""),
	m_capital_password(""),
	m_wsuir(""),
	m_bank_id("SIM"),
	m_bankname("SIMBank"),
	m_trade_host(trade_host),
	m_db(rt::MongoJob("RealTime")),//����Ҫ���������￪���β�
	m_pub_host(""),
	//m_trade_host(""),
	m_last_updatetime(""),
	m_status("200"), //���200��ʾʲô��
	m_trading_day(""),
	m_init_cash(init_cash),
	m_pre_balance(0.0),
	m_static_balance(0.0),
	m_deposit(0.0),
	m_withdraw(0.0),
	m_withdrawQuota(0.0),
	m_close_profit(0.0),
	m_premium(0.0),
	m_event_id(0), //string���͵�m_event_id ���������͵�0
	m_task_id(taskid),
	m_money(0.0),
	//-------------------
	m_transfers("{}"),
	m_banks("{}"),
	m_frozen("{}"),
	m_events("{}"),
	m_positions("{}"),
	m_trades("{}"),
	m_orders("{}") {
	m_market_preset = rt::MARKET_PRESET();
}