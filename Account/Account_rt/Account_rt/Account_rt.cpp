#include "Account_rt.h"
namespace rt {

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
			HKU_INFO("create new account");
			create_simaccount();
		}
		sync();
	}

	void Account_rt::reload() {
		//如果能直接返回JsonJob不是省去了来回翻译的步骤
		map<string, string> cond;
		cond["account_cookie"] = m_user_id;
		cond["password"] = m_password;
		string message = m_db.find_json(m_db_coll, cond);
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


	void Account_rt::sync() {
		on_sync();
		map<string, string> cond;
		cond["account_cookie"] = m_user_id;
		cond["password"] = m_password;
		m_db.update_json(m_db_coll, cond, message().jsonstr());
		rt::JsonJob j;
		j.add_string("updatetime", hku::Datetime::now().str());
		j.add_string("account_cookie", m_user_id);
		j.add_document("accounts", account_msg());
		m_db.save_json("hisaccounts", j.jsonstr());
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
		bank.add_string("bank_account", "");
		bank.add_double("fetch_amount", 0.0);
		bank.add_double("qry_count", 0.0);
		m_banks[m_bank_id] = bank;
		ask_deposit(m_init_cash);
	}

	bool Account_rt::add_position(rt::Position_rt position) {
		if (!m_positions.count(position.code())) {
			m_positions[position.code()] = position;
			//QA这里return的是false，被我给改了，使用时注意。
			return true;
		}
		else {
			return false;
		}
	}

	vector<rt::JsonJob> Account_rt::open_orders() {
		vector<rt::JsonJob> result;

		for (auto iter = m_orders.begin(); iter != m_orders.end(); ++iter) {
			rt::JsonJob tmp(iter->value);
			if (tmp["volume_left"].GetDouble() > 0) {
				result.push_back(tmp);
			}
		}
		return result;
	}

	rt::JsonJob Account_rt::message() {
		rt::JsonJob res;
		res.add_string("account_cookie", m_user_id);
		res.add_string("password", m_password);
		res.add_string("databaseip", m_trade_host);
		res.add_string("model", m_model);
		res.add_double("ping_gap", 5);				//?这是啥？
		res.add_string("portfolio", m_portfolio);
		res.add_string("broker_name", m_broker_name); //期货公司
		res.add_string("capital_password", m_capital_password);//资金密码（实盘用）
		res.add_string("bank_password", m_bank_password);//资金密码（实盘用）
		res.add_string("bankid", m_bank_id);//资金密码（实盘用）
		res.add_string("investor_name", m_investor_name);
		res.add_double("money", m_money);
		res.add_string("pub_host", m_pub_host);
		res.add_string("trade_host", m_trade_host);
		res.add_string("taskid", m_task_id);
		res.add_string("sourceid", m_source_id);
		res.add_string("updatetime", m_last_updatetime);
		res.add_string("wsuri", m_wsuri);
		res.add_string("bankname", m_bankname);
		res.add_string("trading_day", m_trading_day);
		res.add_string("status", m_status);
		res.add_document("accounts", account_msg());
		res.add_document("trades", m_trades);
		res.add_document("positions", position_msg());
		res.add_document("orders", m_orders);
		res.add_document("event", m_events);
		res.add_document("transfers", m_transfers);
		res.add_document("banks", m_banks);
		res.add_document("frozen", m_frozen);
		res.add_document("settlement", "{}");
		return res;
	}

	rt::JsonJob Account_rt::account_msg() {
		rt::JsonJob res;
		res.add_string("user_id", m_user_id);
		res.add_string("currency", "CNY");
		res.add_double("pre_balance", m_pre_balance);
		res.add_double("deposit", m_deposit);
		res.add_double("withdraw", m_withdraw);
		res.add_double("withdrawQuota", m_withdrawQuota);
		res.add_double("close_profit", m_close_profit);
		res.add_double("commission", m_commission());
		res.add_double("premium", m_premium);
		res.add_double("static_balance", m_static_balance);
		res.add_double("position_profit", position_profit());
		res.add_double("float_profit", float_profit());
		res.add_double("balance", m_balance());
		res.add_double("margin", m_margin());
		res.add_double("frozen_margin", frozen_margin());
		res.add_double("frozen_commission", 0.0);
		res.add_double("frozen_premium", 0.0);
		res.add_double("available", m_available());
		res.add_double("risk_ratio", (1 - m_available() / m_balance()));
		return res;
	}

	rt::JsonJob Account_rt::position_msg() {
		rt::JsonJob res;
		for (auto iter = m_positions.begin(); iter != m_positions.end(); ++iter) {
			res.add_document(iter->first, iter->second.message());
		}
		return res;
	}

	price_t Account_rt::position_profit() {
		price_t result = 0;
		for (auto iter = m_positions.begin(); iter != m_positions.end(); ++iter) {
			result += iter->second.m_position_profit();
		}
		return result;
	}

	price_t Account_rt::float_profit() {
		price_t result = 0;
		for (auto iter = m_positions.begin(); iter != m_positions.end(); ++iter) {
			result += iter->second.m_float_profit();
		}
		return result;
	}

	price_t Account_rt::frozen_margin() {
		price_t result = 0;
		for (auto iter = m_frozen.begin(); iter != m_frozen.end(); ++iter) {
			result += iter->value["money"].GetDouble();
		}
		return result;
	}

	string Account_rt::transform_dt(const hku::Datetime& dt) {
		return dt.str();
	}

	price_t Account_rt::m_available() {
		return m_money;
	}

	price_t Account_rt::m_margin() {
		price_t result = 0;
		for (auto iter = m_positions.begin(); iter != m_positions.end(); ++iter) {
			result += iter->second.m_margin();
		}
		return result;
	}

	price_t Account_rt::m_commission() {
		price_t result = 0;
		for (auto iter = m_positions.begin(); iter != m_positions.end(); ++iter) {
			result += iter->second.commission();
		}
		return result;
	}

	price_t Account_rt::m_balance() {
		//动态权益
		return m_static_balance + m_deposit - m_withdraw + float_profit() + m_close_profit;
	}

	bool Account_rt::order_check(const string& code, amount_t amount, price_t price, int towards, const string& order_id) {
		bool res = false;
		rt::Position_rt& pos = get_position(code);
		pos.current_position();
		pos.close_available();
		//开看钱， 平看仓
		if (towards == rt::ORDER_DIRECTION::BUY_CLOSE) {
			if ((pos.m_volume_short() - pos.m_volume_short_frozen()) >= amount) {
				pos.m_volume_short_frozen_today += amount;
				pos.m_volume_short_today -= amount;
				res = true;
			}
			else {
				HKU_WARN("BUYCLOSE 仓位不足");
			}
		}
		else if (towards == rt::ORDER_DIRECTION::BUY_CLOSETODAY) {
			if ((pos.m_volume_short_today - pos.m_volume_short_frozen_today) >= amount) {
				pos.m_volume_short_frozen_today += amount;
				pos.m_volume_short_today -= amount;
				res = true;
			}
			else {
				HKU_WARN("BUYCLOSETODAY 今日仓位不足");
			}
		}
		else if (towards == rt::ORDER_DIRECTION::SELL_CLOSE || towards == rt::ORDER_DIRECTION::SELL) {
			if ((pos.m_volume_long() - pos.m_volume_long_frozen()) >= amount) {
				pos.m_volume_long_frozen_today += amount;
				pos.m_volume_long_today -= amount;
				res = true;
			}
			else {
				HKU_WARN("SELLCLOSE 仓位不足");
			}
		}
		else if (towards == rt::ORDER_DIRECTION::SELL_CLOSETODAY) {
			if ((pos.m_volume_long_today - pos.m_volume_long_frozen_today) >= amount) {
				pos.m_volume_long_frozen_today += amount;
				pos.m_volume_long_today -= amount;
			}
			else {
				HKU_WARN("SELLCLOSETODAY 今日仓位不足");
			}
		}
		else if (towards == rt::ORDER_DIRECTION::BUY_OPEN || towards == rt::ORDER_DIRECTION::SELL_OPEN ||
			towards == rt::ORDER_DIRECTION::BUY) {
			//冻结的保证金
			price_t unit_table = 0;
			price_t buy_frozen_coeff = 0;
			if (m_market_preset.get_code(code)) {
				unit_table = m_market_preset.get_code(code)->unit_table();
				buy_frozen_coeff = m_market_preset.get_code(code)->buy_frozen_coeff();
			}
			else {
				unit_table = 1;
				buy_frozen_coeff = 1;
			}
			//coeff 不是 commission,不是手续费
			price_t coeff = price * unit_table * buy_frozen_coeff;
			price_t moneyneed = coeff * amount;
			if (m_available() > moneyneed) {
				m_money -= moneyneed;
				JsonJob j;
				j.add_double("amount", amount);
				j.add_double("coeff", coeff);
				j.add_double("money", moneyneed);
				m_frozen[order_id] = j;
				res = true;
			}
			else {
				HKU_WARN(fmt::format("开仓保证金不足 TOWARD{} NEED{} HAVE{}", towards, moneyneed, m_available()));
			}
		}
		return res;
	}

	rt::JsonJob Account_rt::send_order(const string& code, amount_t amount, price_t price, int towards, const string& order_id) {
		order_id = order_id.empty ? rt::generate_uuid_v4() : order_id;
		if (order_check(code, amount, price, towards, order_id)) {
			HKU_INFO("order check success");
			string direction = rt::parse_toward2direction(towards);
			string offset = rt::parse_toward2offset(towards);
			m_event_id += 1;
			JsonJob order;
			order.add_string("account_cookie", m_user_id);
			order.add_string("user_id", m_user_id);
			order.add_string("instrument_id", code);
			order.add_int("towards", towards);
			order.add_string("exchange_id", m_market_preset.get_exchange(code));
			order.add_string("order_time", hku::Datetime::now().str());
			order.add_int64("volume", boost::numeric_cast<long long>(amount));
			order.add_double("price", price);
			order.add_int("seqno", m_event_id); // seq no: sequence number
			order.add_string("direction", direction);
			order.add_string("offset", offset);
			order.add_int64("volume_origin", boost::numeric_cast<long long>(amount));
			order.add_string("price_type", "LIMIT");
			order.add_double("limit_price", price);
			order.add_string("time_condition", "GFD");
			order.add_string("volume_condition", "ANY");
			order.add_string("insert_date_time", hku::Datetime::now().str());
			order.add_string("exchange_order_id", rt::generate_uuid_v4());
			order.add_string("status", "ALIVE");
			order.add_int64("volume_left", boost::numeric_cast<long long>(amount));
			order.add_string("last_msg", "已报");
			m_orders.add_document(order_id, order);
			HKU_INFO(fmt::format("下单成功 {}", order_id));
			//sync()是同步数据库的所有数据，当然包括m_orders
			sync();
			on_ordersent(order);
			return order;
		}
		else {
			throw runtime_error(fmt::format("Order check false: {}", code));
		}
	}

	void Account_rt::cancel_order(const string& order_id) {
		// 撤单，释放冻结
		rapidjson::Value& order = m_orders[order_id];
		order["last_mag"].SetString("已撤单");
		order["status"].SetString("CANCEL");
		order["volume_left"].SetDouble(0.0);
		if (order["offset"].GetString() == "CLOSE" || order["offset"].GetString() == "CLOSETODAY") {
			rt::Position_rt pos = m_positions[order["instrument_id"].GetString()];
			if (order["direction"].GetString() == "BUY") {
				pos.m_volume_short_frozen_today += order["volume_left"].GetDouble();
			}
			else {
				pos.m_volume_long_frozen_today += order["volume_left"].GetDouble();
			}
		}
		else {
			rapidjson::Value& frozen = m_frozen[order_id];
			m_money += frozen["money"].GetDouble();
			frozen["amount"].SetDouble(0.0);
			frozen["money"].SetDouble(0.0);
			//m_frozen[order_id] = frozen不应该有这句话了，因为上面的是直接改的。
		}
		//m_orders[order_id] = order;同理，也不应该有这句话，因为引用调用直接改的。
		HKU_INFO(fmt::format("撤单成功 {}", order_id));
	}

	void Account_rt::make_deal(rt::JsonJob& order) {
		if (order.jsonstr() == "{}") {
			throw runtime_error("order is null");
		}
		receive_deal(
			order["instrument_id"].GetString(),
			order["limit_price"].GetDouble(),
			order["volume_left"].GetInt64(),
			order["towards"].GetInt(),
			hku::Datetime::now().str(),
			order["order_id"].GetString(),
			rt::generate_uuid_v4());
	}
	void Account_rt::receive_deal(
		const string& code,
		price_t trade_price,
		amount_t trade_amount,
		int trade_towards,
		const string& trade_time,
		const string& order_id,
		const string& trade_id) {
		if (m_orders.hasMember(order_id)) {
			//update order
			rapidjson::Value& order = m_orders[order_id];
			rapidjson::Value& frozen = m_frozen[order_id];//假设冻结订单有这个order_id,QA的默认frozen有问题，这边不采用
			/*
			 *rapidjson::Value v;
			 *v.SetObect()
			 *v.AddMember("key","value")
			 *rapidjson::Document d;
			 *d.AddMember("key",v);无法直接AddMember() Object类型的value
			*/

			price_t vl = order.HasMember("volume_left") ? order["volume_left"].GetDouble() : 0;
			if ((trade_amount - vl) < ZERO_PRICE_T) {
				m_money += frozen["money"].GetDouble();
				frozen["amount"].SetDouble(0);
				frozen["money"].SetDouble(0);
				order["last_msg"].SetString("全部成交");
				order["status"].SetString("Finished");
				HKU_INFO(fmt::format("全部成交 {}", order_id));
			}
			else if (trade_amount < vl) {
				frozen["amount"].SetDouble(vl - trade_amount);
				price_t release_money = trade_amount * frozen["coeff"].GetDouble();
				m_money -= release_money;
				order["last_msg"].SetString("部分成交");
				order["status"].SetString("ALIVE");// 和QUEUED一样，之后版本我会重新整理
				HKU_INFO(fmt::format("部分成交 {}", order_id));
			}
			//volume_left：剩余未成交的仓位，对于开仓就是还没有买到的仓位，对于平仓就是还没有卖出的仓位
			order["volume_left"].SetDouble(order["volume_left"].GetDouble() - trade_amount);
			//json格式一下两步不需要
			//m_orders[order_id] = order;
			//m_frozen[order_id] = frozen;
			
			//update trade
			m_event_id += 1;

			//默认trade_id不为空
			//trade_id = trade_id.empty() ? rt::generate_uuid_v4() : trade_id;
			rt::JsonJob j;
			j.add_int("seqno", m_event_id);
			j.add_string("user_id", m_user_id);
			j.add_string("trade_id", trade_id);
			j.add_string("exchange_id", order["exchange_id"].GetString());
			j.add_string("instrument_id", order["instrument_id"].GetString());
			j.add_string("order_id", order_id);
			j.add_string("exchange_trade_id", trade_id);
			j.add_string("direction", order["direction"].GetString());
			j.add_string("offset", order["offset"].GetString());
			j.add_double("volume", trade_amount);
			j.add_double("price", trade_price);
			j.add_string("trade_time", trade_time);
			j.add_double("commission", 0);
			j.add_string("trade_date_time", trade_time);//和trade_time重复
			m_trades.add_document(trade_id, j);

			price_t close_profit, margin;
			get_position(code).update_pos(trade_price, trade_amount, trade_towards, close_profit, margin);

			m_money -= (margin - close_profit);
			m_close_profit += close_profit;
			sync();
		}
	}


	rt::Position_rt& Account_rt::get_position(const string& code) {
		if (!m_positions.count(code)) {
			m_positions[code] = rt::Position_rt(code);
		}
		return m_positions[code];
	}
	void Account_rt::on_price_change(const string& code, price_t price) {
		if (m_positions.count(code)) {
			try {
				rt::Position_rt& pos = get_position(code);
				if (std::abs(pos.m_last_price - price) > ZERO_PRICE_T) {
					pos.m_last_price = price;
					sync();
				}
			}
			catch (...) {
				HKU_ERROR("未处理");
			}
		}
	}
}

