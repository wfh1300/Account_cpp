#include "Order_rt.h"
#include "util_rt.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
namespace rt {
	Order_rt::Order_rt(
		price_t price,
		const string& date,
		const Datetime& datetime,
		const Datetime& sending_time,
		const DatetimeList& trade_time,
		price_t amount,
		const string& market_type,
		const string& frequence,
		int towards,
		const string& code,
		const string& user_cookie,
		const string& account_cookie,
		const string& strategy,
		const string& order_model,
		price_t money,
		const string& amount_model,
		const string& broker,
		const string& order_id,
		const StringList& trades_ids,
		const string& status,
		F_CALLBACK callback,
		price_t commission_coeff,
		price_t tax_coeff,
		const string& exchange_id,
		const string& position_id,
		const Parameter& params)
		:m_price(price), m_date(date), m_datetime(datetime), m_sending_time(sending_time), m_trade_time(trade_time),
		m_amount(amount), m_trade_amount(0), m_cancel_amount(0), m_towards(towards), m_code(code), m_user_cookie(user_cookie),
		m_market_type(market_type), m_frequence(frequence), m_account_cookie(account_cookie), m_strategy(strategy),
		m_type(market_type), m_order_model(order_model), m_amount_model(amount_model),
		m_commission_coeff(commission_coeff), m_tax_coeff(tax_coeff), m_trades_ids(trades_ids),
		m_market_preset(rt::MARKET_PRESET().get_code(code)),
		m_trade_price(0), m_broker(broker), m_callback(callback), m_money(money), m_reason(hku::Null<StringList>()), m_exchange_id(exchange_id),
		m_time_condition("GFD"), m_status(status), m_exchange_code(rt::EXCHANGE_CODE()), m_position_id(position_id),
		m_params(params) {

		if (order_id.empty()) {
			//boost::uuids::random_generator uuid_v4;
			//m_order_id = boost::uuids::to_string(uuid_v4());
			m_order_id = rt::generate_random_name("Order");
			m_realorder_id = m_order_id;
		}
		else {
			m_order_id = order_id;
			m_realorder_id = m_order_id;
		}
		//mainacc �� subacc
		try {
			m_mainacc_id = params.get<string>("mainacc_id");
		}
		catch (...) {
			m_mainacc_id = "";
		}
		try {
			m_subacc_id = params.get<string>("subacc_id");
		}
		catch (...) {
			m_subacc_id = "";
		}

		if (m_towards == rt::ORDER_DIRECTION::BUY || m_towards == rt::ORDER_DIRECTION::BUY_OPEN ||
			m_towards == rt::ORDER_DIRECTION::BUY_CLOSE) {
			m_direction = "BUY";
		}
		else {
			m_direction = "SELL";
		}

		if (m_towards == rt::ORDER_DIRECTION::BUY || m_towards == rt::ORDER_DIRECTION::BUY_OPEN ||
			m_towards == rt::ORDER_DIRECTION::SELL_OPEN) {
			m_offset = "OPEN";
		}
		else {
			m_offset = "CLOSE";
		}

	}

	price_t Order_rt::pending_amount() const {
		return m_amount - m_cancel_amount - m_trade_amount;
	}

	ostream& operator<<(ostream& os, const Order_rt& order) {
		os << "Order_rt " << endl;
		os << "realorder_id: " << order.m_realorder_id << endl;
		os << "datetime: " << order.m_datetime << endl;
		os << "code: " << order.m_code << endl;
		os << "amount: " << order.m_amount << endl;
		os << "price: " << order.m_price << endl;
		os << "towards: " << order.m_towards << endl;
		os << "btype: " << order.m_type << endl;
		os << "order_id: " << order.m_order_id << endl;
		os << "account: " << order.m_account_cookie << endl;
		os << "status: " << order.m_status << endl;
		return os;
	}

	string Order_rt::status() {

		//���¼�����������״̬ ������ "�ⲿ�������µ�"
		if (m_status == rt::ORDER_STATUS::FAILED || m_status == rt::ORDER_STATUS::NEXT ||
			m_status == rt::ORDER_STATUS::SETTLED || m_status == rt::ORDER_STATUS::CANCEL_ALL ||
			m_status == rt::ORDER_STATUS::CANCEL_PART) return m_status;

		price_t _pending_amount = pending_amount();

		if (_pending_amount <= 0) {
			m_status = rt::ORDER_STATUS::SUCCESS_ALL;
			return m_status;
		}
		else if (_pending_amount > 0 && m_trade_amount > 0) {
			m_status = rt::ORDER_STATUS::SUCCESS_PART;
			return m_status;
		}
		else if (std::abs(m_trade_amount) < ZERO_PRICE_T) {
			m_status = rt::ORDER_STATUS::QUEUED;
			return m_status;
		}
	}

	price_t Order_rt::calc_commission(price_t trade_price, price_t trade_amount) {
		//�ڻ�������������������ϵ�� * �ɽ��ܽ�� + ����������������ϵ�� * ����
		//��Ʊ��ÿ�ɼ۸� * ���� * ������ϵ��

		price_t commission_fee = 0.0;
		if (m_market_type == rt::MARKET_TYPE::FUTURE_CN) {
			price_t value = trade_price * trade_amount * m_market_preset->unit_table();

			if (m_towards == rt::ORDER_DIRECTION::BUY_OPEN || m_towards == rt::ORDER_DIRECTION::BUY_CLOSE ||
				m_towards == rt::ORDER_DIRECTION::SELL_CLOSE || m_towards == rt::ORDER_DIRECTION::SELL_OPEN) {
				commission_fee = m_market_preset->commission_coeff_pervol() * trade_amount +
					m_market_preset->commission_coeff_peramount() * std::abs(value);
			}
			else if (m_towards == rt::ORDER_DIRECTION::BUY_CLOSETODAY || m_towards == rt::ORDER_DIRECTION::SELL_CLOSETODAY) {
				commission_fee = m_market_preset->commission_coeff_today_pervol() * trade_amount +
					m_market_preset->commission_coeff_today_peramount() * std::abs(value);
			}
			return commission_fee;
		}
		else if (m_market_type == rt::MARKET_TYPE::STOCK_CN) {
			commission_fee = trade_price * trade_amount * m_commission_coeff;
			return commission_fee > 5 ? commission_fee : 5;
		}
	}

	string Order_rt::get_exchange(const string& instrument_code) const {
		return m_exchange_code.exchange(instrument_code);
	}

	void Order_rt::create() {
		//����һ�ʶ���(δ����ί�ж��� -- �ڴ�����ʱ�����)
		m_status = rt::ORDER_STATUS::NEW;
	}

	void Order_rt::cancel() {
		m_cancel_amount = m_amount - m_trade_amount;
		if (std::abs(m_trade_amount) < ZERO_PRICE_T)
			//δ���ף�����ȫ��
			m_status = rt::ORDER_STATUS::CANCEL_ALL;
		else
			//���ֽ��ף�ʣ�ඩ��ȫ��
			m_status = rt::ORDER_STATUS::CANCEL_PART;
	}

	void Order_rt::failed(const string& reason) {
		m_status = rt::ORDER_STATUS::FAILED;
		m_reason.push_back(reason);
	}

	ParameterPtr Order_rt::trade(const string& trade_id, price_t trade_price, price_t trade_amount, const Datetime& trade_time) {
		if (m_status == rt::ORDER_STATUS::SUCCESS_PART || m_status == rt::ORDER_STATUS::QUEUED) {
			trade_amount = static_cast<int64>(trade_amount); //python -> int(trade_amount)
			if (trade_amount < 1) {
				// ���������С��1
				m_status = rt::ORDER_STATUS::NEXT;
				return NULL;
			}
			else {
				if (!std::count(m_trades_ids.begin(), m_trades_ids.end(), trade_id)) {
					//trade_time -> to_str
					m_trades_ids.push_back(trade_id);
					m_trade_price = (m_trade_price * m_trade_amount + trade_price * trade_amount)
						/ (m_trade_amount + trade_amount);
					m_trade_amount += trade_amount;
					m_trade_time.push_back(trade_time);
					int res = m_callback(m_code, trade_id, m_order_id, m_realorder_id, trade_price,
						trade_amount, m_towards, trade_time);
					if (res == 0)
						return trade_message(trade_id, trade_price, trade_amount, trade_time.str());
					else return NULL;
				}
				else return NULL;
			}
		}
		else {
			HKU_ERROR(fmt::format("order status is {} cannot trade", m_status));
			return NULL;
		}
	}

	ParameterPtr Order_rt::trade_message(
		const string& trade_id,
		price_t trade_price,
		price_t trade_amount,
		const string& trade_time) {
		ParameterPtr ptr_result = make_shared<Parameter>();
		ptr_result->set<string>("user_id", m_account_cookie);//�û�ID
		ptr_result->set<string>("order_id", m_order_id);//����������
		ptr_result->set<string>("trade_id", trade_id);//ί�е�ID������һ��user��trade_id����Զ���ظ���
		ptr_result->set<string>("exchange_id", m_exchange_id);//������
		ptr_result->set<string>("instrument_id", m_code);//�������еĺ�Լ����
		ptr_result->set<string>("exchange_trade_id", trade_id);//����������
		ptr_result->set<string>("direction", m_direction);//�µ�����
		ptr_result->set<string>("offset", m_offset);//��ƽ��ʶ
		ptr_result->set<price_t>("volume", trade_amount);//�ɽ�����
		ptr_result->set<price_t>("price", trade_price);//�ɽ��۸�
		ptr_result->set<string>("trade_date_time", trade_time);//�ɽ�ʱ��
		ptr_result->set<price_t>("commission", calc_commission(trade_price, trade_amount));//������
		ptr_result->set<string>("seqno", "");
		return ptr_result;
	}

	void Order_rt::queued(const string& realorder_id) {
		m_realorder_id = realorder_id;
		m_status = rt::ORDER_STATUS::QUEUED;
	}

	void Order_rt::settle() {
		m_status = rt::ORDER_STATUS::SETTLED;
	}

	string Order_rt::order_id() const {
		return m_order_id;
	}
	price_t Order_rt::amount() const {
		return m_amount;
	}

	price_t Order_rt::price() const {
		return m_price;
	}

	int Order_rt::towards() const {
		return m_towards;
	}
}