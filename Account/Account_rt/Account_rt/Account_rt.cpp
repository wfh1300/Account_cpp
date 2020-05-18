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
	m_db_coll("accounts"),
	//-------------------
	m_transfers("{}"),
	m_banks("{}"),
	m_frozen("{}"),
	m_events("{}"),
	//m_positions(),
	m_trades("{}"),
	m_orders("{}") 
{
	m_market_preset = rt::MARKET_PRESET();
}

void Account_rt::initial() {
	reload();
	//如果model不写"SIM",应该是自动实盘
	if ((m_pre_balance == 0) && (m_balance() == 0) && (m_model == "SIM")) {
		log("create new account");
		create_simaccount();
	}
	sync();
}

void Account_rt::reload() {
	//如果能直接返回JsonJob不是省去了来回翻译的步骤
	map<string, string> cond;
	cond["account_cookie"] = m_user_id;
	cond["password"] = m_password;
	string message = m_db.find_json(m_db_coll,cond);
	//下午3点停盘之前
	auto curr_time = hku::Datetime::now();
	if (curr_time.hour() <= 15) {
		//to_iso_extended_string 2020-05-15
		//to_simple_string 2020-May-15
		m_trading_day = hku::bd::to_iso_extended_string(curr_time.date());
	}
	//超过下午3点，只能下一个交易日交易
	else {
		//星期日到四时，下一个交易日为明天
		//星期日需要在if里面，不然在else里8-0，下一个交易日会到下下个星期一
		if (curr_time.dayOfWeek() <= 4 && curr_time.dayOfWeek() >= 0) {
			m_trading_day = hku::bd::to_iso_extended_string((curr_time + hku::TimeDelta(1)).date());
		}
		else {
			m_trading_day = hku::bd::to_iso_extended_string((curr_time + hku::TimeDelta(8 - curr_time.dayOfWeek())).date());
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
			string key = iter->value["instrument_id"].GetString();	
			//m_positions[key] = rt::Position_rt::loadfrommessage(iter->value.GetString());
			m_positions[key] = rt::Position_rt::loadfrommessage(rt::JsonJob(positions).jsonstr());
		}

		for (auto order : open_orders()) {
			//log(fmt::format("try to deal {}", order[""]))
			make_deal(order);
		}

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
vector<rt::JsonJob> Account_rt::open_orders() {
	vector<rt::JsonJob> result;
	
	for (auto iter = m_orders.begin(); iter != m_orders.end(); ++iter) {
		if (iter->second["volume_left"].GetDouble() > 0) {
			result.push_back(iter->second);
		}
	}
	return result;
}

void Account_rt::sync() {
	on_sync();
	map<string, string> cond;
	cond["account_cookie"] = m_user_id;
	cond["password"] = m_password;
	m_db.update_json(m_db_coll, cond, message());
	rt::JsonJob j;
	j.add_string("updatetime", hku::Datetime::now().str());
	j.add_string("account_cookie", m_user_id);
	j.add_string("accounts", account_msg());
	m_db.save_json("hisaccounts",j.jsonstr());
}

void Account_rt::settle() {
	m_pre_balance += (m_deposit - m_withdraw + m_close_profit);
	m_static_balance = m_pre_balance;
	m_close_profit = 0;
	m_deposit = 0;
	m_withdraw = 0;
	m_premium = 0;
	m_money += frozen_margin();
	m_orders.clear();
	m_frozen.clear();
	m_trades.clear();
	m_transfers.clear();
	m_events.clear();
	m_event_id = 0;
	for (auto iter = m_positions.begin(); iter != m_positions.end(); ++iter) {
		iter->second.settle();
	}
}

void Account_rt::ask_deposit(price_t money) {
	m_deposit += money;
	m_money += money;

	rt::JsonJob j;
	j.add_string("datetime", hku::Datetime::now().str()); //转账时间
	j.add_string("currency", "CNY");
	j.add_double("amount", money);
	j.add_double("error_id", 0);
	j.add_string("error_msg", "成功");
	m_transfers.add_document(std::to_string(m_event_id), j.jsonstr());
	m_events[hku::Datetime::now().str()] = fmt::format("转账成功{}", money);
}

void Account_rt::ask_withdraw(price_t money) {
	if (m_withdrawQuota > money) {
		m_withdrawQuota -= money;
		m_withdraw += money;
		rt::JsonJob j;
		j.add_string("datetime", hku::Datetime::now().str()); //转账时间
		j.add_string("currency", "CNY");
		j.add_double("amount", -money);
		j.add_double("error_id", 0);
		j.add_string("error_msg", "成功");
		m_transfers.add_document(std::to_string(m_event_id), j.jsonstr());
		m_events[hku::Datetime::now().str()] = fmt::format("转账成功{}", money);
	}
	else {
		m_events[hku::Datetime::now().str()] = fmt::format("转账失败：余额不足 left: {}, ask: {}", m_withdrawQuota, money);
	}
}

void Account_rt::create_simaccount() {
	m_trading_day = hku::bd::to_iso_extended_string(hku::Datetime::now().date());
	m_wsuri = "ws://www.yutiansut.com:7988"; //暂时用他的这个ws，//TODO,能删掉就删掉
	m_pre_balance = 0;
	m_static_balance = 0;
	m_deposit = 0;
	m_withdraw = 0;
	m_withdrawQuota = 0;
	m_money = 0;
	m_close_profit = 0;
	m_event_id = 0;
	m_transfers.clear();
	m_banks.clear();
	m_events.clear();
	m_positions.clear();
	m_trades.clear();
	m_orders.clear();
	rt::JsonJob bank;
	bank.add_string("id", m_bank_id);
	bank.add_string("name", m_bankname);
	bank.add_string("ban_account", "");
	bank.add_double("fetch_amount", 0.0);
	bank.add_double("qry_count", 0.0);
	m_banks[m_bank_id] = bank;
	ask_deposit(m_init_cash);
}