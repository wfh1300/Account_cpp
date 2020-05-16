#include "Account_rt.h"
Account_rt::Account_rt(
	const string& username,
	const string& password,
	const string& model,
	const string& broker_name,
	const string& trade_host, //这里可以改为通过env获取
	price_t init_cash,
	const string& taskid
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
	m_wsuri(""),
	m_bank_id("SIM"),
	m_bankname("SIMBank"),
	m_trade_host(trade_host),
	m_db(rt::MongoJob("RealTime")),//有需要可以在这里开放形参
	m_pub_host(""),
	//m_trade_host(""),
	m_last_updatetime(""),
	m_status("200"), //这个200表示什么？
	m_trading_day(""),
	m_init_cash(init_cash),
	m_pre_balance(0.0),
	m_static_balance(0.0),
	m_deposit(0.0),
	m_withdraw(0.0),
	m_withdrawQuota(0.0),
	m_close_profit(0.0),
	m_premium(0.0),
	m_event_id(0), //string类型的m_event_id 输入了整型的0
	m_task_id(taskid),
	m_money(0.0),
	//-------------------
	m_transfers("{}"),
	m_banks("{}"),
	m_frozen("{}"),
	m_events("{}"),
	//m_positions(),
	m_trades("{}"),
	m_orders("{}") {
	m_market_preset = rt::MARKET_PRESET();
}

void Account_rt::initial() {
	reload();
	if ((m_pre_balance == 0) && (m_balance() == 0) && (m_model == "SIM")) {
		log("create new account");
		create_simaccount();
	}
	sync();
}

void Account_rt::reload() {
	//如果能直接返回JsonJob不是省去了来回翻译的步骤
	string message = m_db.find_account("accounts", m_user_id, m_password);
	//下午3点停盘之前
	auto curr_time = hku::Datetime::now();
	if (curr_time.hour() <= 15) {
		//to_iso_extended_string 2020-05-15
		//to_simple_string 2020-May-15
		m_trading_day = hku::bd::to_iso_extended_string(curr_time.date());
	}
	//超过下午3点，只能下一个交易日交易
	else {
		//星期一到四时，下一个交易日为明天
		if (curr_time.dayOfWeek() <= 4 && curr_time.dayOfWeek() >= 0) {
			m_trading_day = hku::bd::to_iso_extended_string((curr_time + hku::TimeDelta(1)).date());
		}
		else {
			//星期日是0还是1？
			m_trading_day = hku::bd::to_iso_extended_string((curr_time + hku::TimeDelta(7 - curr_time.dayOfWeek())).date());
		}
	}

	if (!message.empty()) {
		rt::JsonJob parser(message);
		m_money = parser["money"].GetDouble();
		m_source_id = parser["sourceid"].GetString();
		m_pre_balance = parser["pre_balance"].GetDouble();
		m_deposit = parser["doposit"].GetDouble();
		m_withdraw = parser["withdraw"].GetDouble();
		m_withdrawQuota = parser["withdrawQuota"].GetDouble();
		m_close_profit = parser["close_profit"].GetDouble();
		m_static_balance = parser["static_balance"].GetDouble();
		//m_events只有用string类型才能被"{key: value}"赋值,否则{key: value}赋值不上去JsonJob
		//string就是它们相互转换的中间格式
		m_events = rt::JsonJob(parser["events"]);
		m_trades = rt::JsonJob(parser["trades"]);
		m_task_id = parser.hasMember("taskid") ? parser["taskid"].GetString() : m_task_id;


		//从数据库中恢复Position_rt;
		auto positions = parser["positions"].GetObject();
		for (auto iter = positions.begin(); iter != positions.end(); ++iter) {
			iter->value["instrument_id"].GetString();
		}
		positions
			orders;
		m_banks = rt::JsonJob(parser["banks"]);
		m_status = parser["status"].GetString();
		m_wsuri = parser["wsuri"].GetString();
		on_reload();
		//Value 可以直接==string类型，不需要GetString()的
		if (!(parser["trading_day"].GetString() == m_trading_day)) {
			settle();
		}
	}
	
}
