#include "Position_rt.h"
#include <hikyuu/utilities/util.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>

#include "DataBase/MongoJob.h"
namespace rt {
	Position_rt::Position_rt(
		const string& code,
		const string& account_cookie,
		const string& portfolio_cookie,
		const string& username,
		price_t moneypreset, //��ʼ�����ʽ�
		const Str_Price_t& frozen,
		price_t moneypresetLeft,
		price_t volume_long_today,
		price_t volume_long_his,
		price_t volume_short_today,
		price_t volume_short_his,

		price_t volume_long_frozen_his,
		price_t volume_long_frozen_today,
		price_t volume_short_frozen_his,
		price_t volume_short_frozen_today,

		price_t margin_long,
		price_t margin_short,

		price_t open_price_long,
		price_t open_price_short,
		price_t position_price_long,
		price_t position_price_short,

		price_t open_cost_long,
		price_t open_cost_short,
		price_t position_cost_long,
		price_t position_cost_short,

		const string& position_id,
		const string& market_type,
		const string& exchange_id,
		const StringList& trades,
		const string& orders,
		//const Str_Order& orders,

		const string& name,
		price_t commission,
		bool auto_reload,
		bool allow_exceed,
		const string& spms_id,
		const string& oms_id
	):
	m_code(code),
		m_account_cookie(account_cookie),
		m_portfolio_cookie(portfolio_cookie),
		m_username(username),
		m_time(hku::Null<Datetime>()),
		m_market_preset(rt::MARKET_PRESET().get_code(m_code)),
		//m_position_id(position_id),			//str(uuid.uuid4()) if position_id is None else position_id
		m_moneypreset(moneypreset),
		//m_moneypresetLeft(moneypresetLeft),	//self.moneypreset if moneypresetLeft is None else moneypresetLeft
		m_rule("FIFO"),
		m_name(name),
		m_market_type(market_type),
		m_exchange_id(exchange_id),
		m_volume_long_his(volume_long_his),
		m_volume_long_today(volume_long_today),
		m_volume_short_his(volume_short_his),
		m_volume_short_today(volume_short_today),

		m_volume_long_frozen_his(volume_long_frozen_his),
		m_volume_long_frozen_today(volume_long_frozen_today),
		m_volume_short_frozen_his(volume_short_frozen_his),
		m_volume_short_frozen_today(volume_short_frozen_today),

		m_margin_long(margin_long),
		m_margin_short(margin_short),
		m_open_price_long(open_price_long),
		m_open_price_short(open_price_short),
		m_commission(commission),
		m_last_price(0),
		m_trades(trades),
		m_orders(orders),
		m_frozen(frozen),
		m_spms_id(spms_id),
		m_oms_id(oms_id),
		m_allow_exceed(allow_exceed)
	{

		//��code�����ڻ���Լ(������ǹ�Ʊ����)����m_market_presetΪ��ָ��
		if (m_market_preset) {
			m_unit_table = m_market_preset->unit_table();
			m_buy_frozen_coeff = m_market_preset->buy_frozen_coeff();
			m_sell_frozen_coeff = m_market_preset->sell_frozen_coeff();

			/*m_price_tick = m_market_preset->price_tick();
			m_exchange = m_market_preset->exchange();
			m_commission_coeff_peramount = m_market_preset->commission_coeff_peramount();
			m_commission_coeff_pervol = m_market_preset->commission_coeff_pervol();
			m_commission_coeff_today_peramount = m_market_preset->commission_coeff_today_peramount();
			m_commission_coeff_today_pervol = m_market_preset->commission_coeff_today_pervol();*/
		}
		else {
			m_unit_table = 1;
			m_buy_frozen_coeff = 1;
			m_sell_frozen_coeff = 1;

			/*m_price_tick = 1;
			m_exchange = 1;
			m_commission_coeff_peramount = 1;
			m_commission_coeff_pervol = 1;
			m_commission_coeff_today_peramount = 1;
			m_commission_coeff_today_pervol = 1;*/
		}

		boost::uuids::random_generator  uuid_v4;
		m_position_id = position_id.empty() ? boost::uuids::to_string(uuid_v4()) : position_id;
		m_moneypresetLeft = moneypreset >= 0 ? moneypreset : moneypresetLeft;
		m_position_price_long = std::abs(position_price_long) < ZERO_PRICE_T ? open_price_long : position_price_long;
		m_position_price_short = std::abs(position_price_short) < ZERO_PRICE_T ? open_price_short : position_price_short;
		m_open_cost_long = std::abs(open_cost_long) < ZERO_PRICE_T ? (open_price_long * m_volume_long() * m_unit_table) : open_cost_long;
		m_open_cost_short = std::abs(open_cost_short) < ZERO_PRICE_T ? (open_price_short * m_volume_short() * m_unit_table) : open_cost_short;
		m_position_cost_long = std::abs(position_cost_long) < ZERO_PRICE_T ? (m_position_price_long * m_volume_long() * m_unit_table) : position_cost_long;
		m_position_cost_short = std::abs(position_cost_short) < ZERO_PRICE_T ? (m_position_price_short * m_volume_short() * m_unit_table) : position_cost_short;

		/*
		if auto_reload:
			self.reload();
				def reload(self):
			res = DATABASE.positions.find_one({
				'account_cookie': self.account_cookie,
				'portfolio_cookie': self.portfolio_cookie,
				'username': self.username,
				'position_id': self.position_id
			})
			if res is None:
				self.save()
			else:
				self.loadfrommessage(res)
		*/
	}


	price_t Position_rt::m_volume_long() {
		return m_volume_long_today + m_volume_long_his + m_volume_long_frozen();
	}
	//�������ᵥ�Ŀյ��ֲ֣���Ϊ���ᵥ�п��ܽ��׳ɹ�Ҳ�п���ʧ�ܣ������������������е�
	price_t Position_rt::m_volume_short() {
		return m_volume_short_his + m_volume_short_today + m_volume_short_frozen();
	}
	price_t Position_rt::m_volume_long_frozen() {
		return m_volume_long_frozen_his + m_volume_long_frozen_today;
	}
	price_t Position_rt::m_volume_short_frozen() {
		return m_volume_short_frozen_his + m_volume_short_frozen_today;
	}
	price_t Position_rt::m_margin() {
		return m_margin_long + m_margin_short;
	}
	price_t Position_rt::m_float_profit_long() {
		if (m_market_preset) {
			return m_last_price * m_volume_long() * m_market_preset->unit_table() - m_open_cost_long;
		}
		else {
			HKU_WARN("market preset doesn't exist");
			return 0.0;
		}
	}
	price_t Position_rt::m_float_profit_short() {
		if (m_market_preset) {
			return m_open_cost_short - m_last_price * m_volume_short() * m_market_preset->unit_table();
		}
		else {
			HKU_WARN("market preset doesn't exist");
			return 0.0;
		}
	}
	price_t Position_rt::m_float_profit() {
		return m_float_profit_long() + m_float_profit_short();
	}
	price_t Position_rt::m_position_profit_long() {
		if (m_market_preset) {
			return m_last_price * m_volume_long() * m_market_preset->unit_table() - m_position_cost_long;
		}
		else {
			HKU_WARN("market preset doesn't exist");
			return 0.0;
		}
	}
	price_t Position_rt::m_position_profit_short() {
		if (m_market_preset) {
			return m_position_cost_short - m_last_price * m_volume_short() * m_market_preset->unit_table();
		}
		else {
			HKU_WARN("market preset doesn't exist");
			return 0.0;
		}
	}
	price_t Position_rt::m_position_profit() {
		return m_position_profit_long() + m_position_profit_short();
	}

	string Position_rt::static_message() {
		rapidjson::StringBuffer s;
		rapidjson::Writer<rapidjson::StringBuffer> writer(s);
		writer.StartObject();
		//�����ֶ�
		writer.Key("code");
		writer.String(m_code.c_str());
		writer.Key("instrument_id");
		writer.String(m_code.c_str());
		writer.Key("user_id");
		writer.String(m_account_cookie.c_str());
		writer.Key("portfolio_cookie");
		writer.String(m_portfolio_cookie.c_str());
		writer.Key("username");
		writer.String(m_username.c_str());
		writer.Key("position_id");
		writer.String(m_position_id.c_str());
		writer.Key("account_cookie");
		writer.String(m_account_cookie.c_str());
		writer.Key("frozen");
		//writer.Str_Params(hku::Null<Str_Params>());
		if (m_frozen.empty()) {
			writer.Null();
		}
		else {
			writer.StartObject();
			for (auto iter = m_frozen.begin(); iter != m_frozen.end(); ++iter) {
				writer.Key(iter->first.c_str());
				writer.Double(iter->second);
			}
			writer.EndObject();
		}
		writer.Key("name");
		writer.String(m_name.c_str());
		writer.Key("spms_id");
		writer.String(m_spms_id.c_str());
		writer.Key("oms_id");
		writer.String(m_oms_id.c_str());
		writer.Key("market_type");
		writer.String(m_market_type.c_str());
		writer.Key("exchange_id");
		writer.String(m_exchange_id.c_str());
		writer.Key("moneypreset");
		writer.Double(m_moneypreset);
		writer.Key("moneypresetLeft");
		writer.Double(m_moneypresetLeft);
		writer.Key("lastupdatetime");
		writer.String(m_time.str().c_str());
		//�ֲ���
		//�������ȡ���ˣ����������Ƿ���Ҫ
		writer.Key("volume_long_today");
		writer.Double(hku::roundDown(m_volume_long_today));
		writer.Key("volume_long_his");
		writer.Double(hku::roundDown(m_volume_long_his));
		writer.Key("volume_long");
		writer.Double(hku::roundDown(m_volume_long()));
		writer.Key("volume_long_yd");
		writer.Double(0);
		writer.Key("volume_short_yd");
		writer.Double(0);
		writer.Key("volume_short_today");
		writer.Double(hku::roundDown(m_volume_short_today));
		writer.Key("volume_short_his");
		writer.Double(hku::roundDown(m_volume_short_his));
		writer.Key("volume_short");
		writer.Double(hku::roundDown(m_volume_short()));
		writer.Key("pos_long_his");
		writer.Double(hku::roundDown(m_volume_long_his));
		writer.Key("pos_long_today");
		writer.Double(hku::roundDown(m_volume_long_today));
		writer.Key("pos_short_his");
		writer.Double(hku::roundDown(m_volume_short_his));
		writer.Key("pos_short_today");
		writer.Double(hku::roundDown(m_volume_short_today));
		//ƽ��ί�ж���(δ�ɽ�)
		writer.Key("volume_long_frozen_today");
		writer.Double(hku::roundDown(m_volume_long_frozen_today));
		writer.Key("volume_long_frozen_his");
		writer.Double(hku::roundDown(m_volume_long_frozen_his));
		writer.Key("volume_long_frozen");
		writer.Double(hku::roundDown(m_volume_long_frozen()));
		writer.Key("volume_short_frozen_today");
		writer.Double(hku::roundDown(m_volume_short_frozen_today));
		writer.Key("volume_short_frozen_his");
		writer.Double(hku::roundDown(m_volume_short_frozen_his));
		writer.Key("volume_short_frozen");
		writer.Double(hku::roundDown(m_volume_short_frozen()));
		//��֤��
		writer.Key("margin_long");
		writer.Double(m_margin_long);
		writer.Key("margin_short");
		writer.Double(m_margin_short);
		writer.Key("margin");
		writer.Double(m_margin());

		//�ֲ��ֶ� - ���ն���
		writer.Key("position_price_long");
		writer.Double(m_position_price_long);
		writer.Key("position_cost_long");
		writer.Double(m_position_cost_long);//��ͷ�ܳɱ�(����ֵ);
		writer.Key("position_price_short");
		writer.Double(m_position_price_short);
		writer.Key("position_cost_short");
		writer.Double(m_position_cost_short);
		//ƽ���ֶ�
		writer.Key("open_price_long");
		writer.Double(m_open_price_long);//��ͷ��);
		writer.Key("open_cost_long");
		writer.Double(m_open_cost_long);//��ͷ����);
		writer.Key("open_price_short");
		writer.Double(m_open_price_short);//��ͷ��);
		writer.Key("open_cost_short");
		writer.Double(m_open_cost_short);//��ͷ��);
		//��ʷ�ֶ�
		writer.Key("trades");
		writer.StartArray();
		if (m_trades.empty()) {
			writer.Null();
		}
		else {
			for (auto iter = m_trades.begin(); iter != m_trades.end(); ++iter) {
				writer.String(iter->c_str());
			}
		}
		writer.EndArray();
		//TODO Order���л�
		writer.Key("orders");
		writer.String(m_orders.c_str());
		writer.EndObject();
		return s.GetString();
	}

	bool Position_rt::order_check(price_t amount, price_t price, int towards, const string& order_id) {
		bool res = false;
		//ƽ��֮ǰҪ���ֲ������Ƿ���
		//frozen�Ͳ�frozen��volume�����������෴�Ĳ�����
		if (towards == rt::ORDER_DIRECTION::BUY_CLOSE) {
			//˵��ǰ����� ���������ϵ��ǿյ�
			//ǰ�����volume_short()��ʱ����Ǽ��ϵ�volume_short_frozen,��������Ҫ��ȥ
			//Ҳ����������ƽ��amount��Ҫ��������ʵ�ʳ��еĿյ�
			if ((m_volume_short() - m_volume_short_frozen()) >= amount) {
				//������ǳֲ֣�����Ǯ?
				m_volume_short_frozen_today += amount;
				res = true;
			}
			else {
				HKU_WARN("BUYCLOSE ��λ����");
			}
		}
		else if (towards == rt::ORDER_DIRECTION::BUY_CLOSETODAY) {
			if ((m_volume_short_today - m_volume_short_frozen_today) >= amount) {
				m_volume_short_frozen_today += amount;
				res = true;
			}
			else {
				HKU_WARN("BUYCLOSETODAY ���ղ�λ����");
			}
		}
		else if (towards == rt::ORDER_DIRECTION::SELL_CLOSE) {
			if ((m_volume_long() - m_volume_long_frozen()) >= amount) {
				m_volume_long_frozen_today += amount;
				res = true;
			}
			else {
				HKU_WARN("SELLCLOSE ��λ����");
			}
		}
		else if (towards == rt::ORDER_DIRECTION::SELL_CLOSETODAY) {
			//TODO 	����Ĵ������������,QA��self.volume_long_today - self.volume_short_forzen_today
			if ((m_volume_long_today - m_volume_long_frozen_today) >= amount) {
				m_volume_long_frozen_today += amount;
				return true;
			}
			else {
				HKU_WARN("SELLCLOSETODAY ���ղ�λ����");
			}
		}
		else if (towards == rt::ORDER_DIRECTION::BUY_OPEN || towards == rt::ORDER_DIRECTION::SELL_OPEN ||
			towards == rt::ORDER_DIRECTION::BUY) {
			price_t moneyneed = amount * price * m_unit_table * m_buy_frozen_coeff;
			if (m_moneypresetLeft > moneyneed || m_allow_exceed) {
				//���ﲻӦ����m_moneypresetLeft -= moneyneed��
				m_moneypresetLeft -= moneyneed;
				m_frozen[order_id] = moneyneed;
				res = true;
			}
			else {
				HKU_WARN(fmt::format("���ֱ�֤���� TOWARDS{} Need{} Have{}", towards, moneyneed, m_moneypresetLeft));
			}
		}
		return res;
	}

	string Position_rt::send_order(price_t amount, price_t price, int towards) {
		rapidjson::Document d_orders;
		d_orders.Parse(m_orders.c_str());

		boost::uuids::random_generator uuid_v4;
		string order_id = boost::uuids::to_string(uuid_v4());

		if (order_check(amount, price, towards, order_id)) {
			//����json
			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			writer.StartObject();
			writer.Key("position_id");
			writer.String(m_position_id.c_str());
			writer.Key("account_cookie");
			writer.String(m_account_cookie.c_str());
			writer.Key("instrument_id");
			writer.String(m_code.c_str());
			writer.Key("towards");
			writer.Int(towards);
			writer.Key("exchange_id");
			writer.String(m_exchange_id.c_str());
			writer.Key("order_time");
			writer.String(m_time.str().c_str());
			writer.Key("volume");
			writer.Double(amount);
			writer.Key("price");
			writer.Double(price);
			writer.Key("order_id");
			writer.String(order_id.c_str());
			writer.Key("status");
			writer.String(rt::ORDER_STATUS::NEW.c_str());
			writer.EndObject();

			//���������ɵ�json��ֵ��m_orders[order_id]
			rapidjson::Document d_value;
			d_value.Parse(buffer.GetString());
			if (d_orders.HasMember(order_id.c_str())) {
				d_orders[order_id.c_str()] = rapidjson::Value(d_value, d_orders.GetAllocator());
			}
			else {
				d_orders.AddMember(rapidjson::Value(order_id.c_str(), d_orders.GetAllocator()), d_value, d_orders.GetAllocator());
			}
			rapidjson::StringBuffer buffer_orders;
			rapidjson::Writer<rapidjson::StringBuffer> writer_orders(buffer_orders);
			d_orders.Accept(writer_orders);
			m_orders = buffer_orders.GetString();


			//�������ɵ�json
			return buffer.GetString();
		}
		else {
			throw runtime_error(fmt::format("ORDER CHECK FALSE:{}", m_code));
			return "";
		}
	}


	void Position_rt::update_pos(price_t price, price_t amount, int towards, price_t& profit, price_t& marginValue) {
		on_price_change(price);
		price_t temp_cost = amount * price * m_unit_table;
		//price_t profit = 0;
		//price_t marginValue = 0;
		if (towards == rt::ORDER_DIRECTION::BUY) {
			//��Ʊ����ģʽ
			marginValue = temp_cost;
			m_margin_long += marginValue;
			//���㿪�־���
			m_open_price_long = (m_open_price_long * m_volume_long() + amount * price) / (amount + m_volume_long());
			//����ֲ־���
			m_position_price_long = (m_position_price_long * m_volume_long() + amount * price) / (amount + m_volume_long());
			//���ӽ������ -> ���Զ�����m_volume_long
			m_volume_long_today += amount;
			m_open_cost_long += temp_cost;
			m_position_cost_long += temp_cost;
			m_moneypresetLeft -= marginValue;//���marginValue�б�Ҫ?,ֱ��temp_cost�ͺ��˰�
		}
		else if (towards == rt::ORDER_DIRECTION::SELL) {
			//��Ʊ����ģʽ
			//���������λ��������
			if (m_volume_long_his >= amount) {
				//Ϊʲô��ô���㣿
				m_position_cost_long = m_position_cost_long * (m_volume_long() - amount) / m_volume_long();
				//��m_position_cost_long �����ܵĳֲֳɱ���m_position_cost_long/m_volume_long()����ÿ�ݳֲ�ռ�ݵ�cost
				//�����ܶ������amount��������ʣ��ĳɱ�����m_position_cost_long/m_volume_long() * (m_volume_long()-amount)
				//��Ϊcost����price��cost Լ���� price*amount
				m_open_cost_long = m_open_cost_long * (m_volume_long() - amount) / m_volume_long();
				m_volume_long_his -= amount;
				marginValue = -1 * (m_position_price_long * amount);
				m_margin_long += marginValue;
				profit = (price - m_position_price_long) * amount;
				m_moneypresetLeft += (-marginValue + profit);
			}
			else {
				throw runtime_error(fmt::format("amount: {} exceed volume: {}", amount, m_volume_long_his));
			}
		}
		else if (towards == rt::ORDER_DIRECTION::BUY_OPEN) {
			//���ӱ�֤��
			marginValue = temp_cost * m_buy_frozen_coeff;
			m_margin_long += marginValue;
			//���㿪�־���
			m_open_price_long = (m_open_price_long * m_volume_long() + amount * price) / (amount + m_volume_long());
			//����ֲ־���
			m_position_price_long = (m_position_price_long * m_volume_long() + amount * price) / (amount + m_volume_long());
			m_volume_long_today += amount;
			m_open_cost_long += temp_cost;
			m_position_cost_long += temp_cost;
			m_moneypresetLeft -= marginValue;
		}
		else if (towards == rt::ORDER_DIRECTION::SELL_OPEN) {
			/*
			1.�������ձ�֤��
			2.���¼��� ���ֳɱ�
			3.���¼��� �ֲֳɱ�
			4.���ӿ���cost
			5.���ӳֲ�cost
			6.���ӿյ���λ*/
			marginValue = temp_cost * m_sell_frozen_coeff;
			m_margin_short += marginValue;
			m_open_price_short = (m_open_price_short * m_volume_short() + amount * price) / (amount + m_volume_short());
			m_position_price_short = (m_position_price_short * m_volume_short() + amount * price) / (amount + m_volume_short());
			m_open_cost_short += temp_cost;
			m_position_cost_short += temp_cost;
			m_volume_short_today += amount;
			m_moneypresetLeft -= marginValue;
		}
		else if (towards == rt::ORDER_DIRECTION::BUY_CLOSETODAY) {
			if (m_volume_short_today > amount) {
				m_position_cost_short = m_position_cost_short * (m_volume_short() - amount) / m_volume_short();
				m_open_cost_short = m_open_cost_short * (m_volume_short() - amount) / m_volume_short();
				m_volume_short_frozen_today += amount;
				marginValue = -1 * m_position_price_short * amount * m_unit_table * m_sell_frozen_coeff;
				m_margin_short += marginValue;
				profit = (m_position_price_short - price) * amount * m_unit_table;
				m_moneypresetLeft += (-marginValue + profit);
				//�ͷű�֤��
				//TODO
				//m_margin_short
				//m_open_cost_short = price*amount;
			}
		}
		else if (towards == rt::ORDER_DIRECTION::SELL_CLOSETODAY) {
			if (m_volume_long_today > amount) {
				m_position_cost_long = m_position_cost_long * (m_volume_long() - amount) / m_volume_long();
				m_open_cost_long = m_open_cost_long * (m_volume_long() - amount) / m_volume_long();
				m_volume_long_frozen_today += amount;
				marginValue = -1 * m_position_price_long * amount * m_unit_table * m_buy_frozen_coeff;
				m_margin_long += marginValue;
				profit = (price - m_position_price_long) * amount * m_unit_table;
				m_moneypresetLeft += (-marginValue + profit);
			}
		}
		else if (towards == rt::ORDER_DIRECTION::BUY_CLOSE) {
			//�������ƽ���
			m_position_cost_short = m_position_cost_short * (m_volume_short() - amount) / m_volume_short();
			m_open_cost_short = m_open_cost_short * (m_volume_short() - amount) / m_volume_short();
			m_volume_short_frozen_today -= amount;
			marginValue = -1 * m_position_price_short * amount * m_unit_table * m_sell_frozen_coeff;
			profit = (m_position_price_short - price) * amount * m_unit_table;
			m_margin_short += marginValue;
			m_moneypresetLeft += (-marginValue + profit);
		}
		else if (towards == rt::ORDER_DIRECTION::SELL_CLOSE) {
			m_position_cost_long = m_position_cost_long * (m_volume_long() - amount) / m_volume_long();
			m_open_cost_long = m_open_cost_long * (m_volume_long() - amount) / m_volume_long();
			m_volume_long_frozen_today -= amount;
			marginValue = -1 * m_position_price_long * amount * m_unit_table * m_buy_frozen_coeff;
			profit = (price - m_position_price_long) * amount * m_unit_table;
			m_margin_long += marginValue;
			m_moneypresetLeft += (-marginValue + profit);
		}
	}


	void Position_rt::settle() {
		m_volume_long_his += m_volume_long_today;
		m_volume_long_today = 0;
		m_volume_long_frozen_today = 0;

		m_volume_short_his += m_volume_short_today;
		m_volume_short_today = 0;
		m_volume_short_frozen_today = 0;
	}


	void Position_rt::on_price_change(price_t price) {
		m_last_price = price;
	}

	void Position_rt::current_position() {
		cout << "volume_long: " << m_volume_long();
		cout << "volume_short: " << m_volume_short();
		cout << "volume_long_frozen: " << m_volume_long_frozen();
		cout << "volume_short_frozen: " << m_volume_short_frozen();
	}
	void Position_rt::close_available() {
		cout << "volume_long: " << m_volume_long() - m_volume_long_frozen();
		cout << "volume_short: " << m_volume_short() - m_volume_short_frozen();
	}
	void Position_rt::change_moneypreset(price_t money) {
		m_moneypreset = money;
	}

	void Position_rt::save() {
		rt::MongoJob mongo(m_account_cookie);
		mongo.save_position("position", static_message());
	}

	price_t Position_rt::calc_commission(price_t trade_price, amount_t trade_amount, int trade_towards) {
		//Order_rt��Ҳ��һ��cal_commission�ĺ���
		//�����Ƿ��ظ���
		throw runtime_error("should this function be called?");
		if (m_market_type == rt::MARKET_TYPE::FUTURE_CN) {
			price_t commission_fee = 0;
			assert(!m_market_preset);//���m_market_presetΪNULL�����޷���������Ĳ���
			//�ڻ�����˰
			//˫�������ѣ�Ҳû����С����������
			price_t value = trade_price * trade_amount * m_unit_table;
			//m_market_preset -> commission_fee_preset
			if (trade_towards == rt::ORDER_DIRECTION::BUY_OPEN || trade_towards == rt::ORDER_DIRECTION::BUY_CLOSE ||
				trade_towards == rt::ORDER_DIRECTION::SELL_CLOSE || trade_towards == rt::ORDER_DIRECTION::SELL_OPEN) {
				commission_fee = m_market_preset->commission_coeff_pervol() * trade_amount +
					m_market_preset->commission_coeff_peramount() * abs(value);
			}
			else if (trade_towards == rt::ORDER_DIRECTION::BUY_CLOSETODAY || trade_towards == rt::ORDER_DIRECTION::SELL_CLOSETODAY) {
				commission_fee = m_market_preset->commission_coeff_today_pervol() * trade_amount + 
					m_market_preset->commission_coeff_today_peramount() * abs(value);
			}
			return commission_fee;
		}
	}

	void Position_rt::on_order(/*const*/Order_rt& order) {
		//���׹����е��ⲿ�ֶ�����
		//���״̬�µļ���ⲿ����
		//order_id �ⲿ��
		//trade_id ��һ������

		//TODO������ʵ�ֵ���Щ���⡣
		throw runtime_error("Position_rt::on_order implemented by myself has some problems��");
		if (!m_frozen.count(order.order_id())) {
			cout << "OUTSIDE ORDER" << endl;
			//�طŶ���/ע�������ϵͳ
			string order_json = send_order(order.amount(), order.price(), order.towards());
		}
	}
}

