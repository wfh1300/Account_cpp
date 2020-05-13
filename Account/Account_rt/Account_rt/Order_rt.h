#pragma once
#ifndef RT_API
#define RT_API
#endif

#include <hikyuu/datetime/Datetime.h>
#include <hikyuu/DataType.h>
#include <hikyuu/utilities/Parameter.h>
#include <hikyuu/utilities/Null.h>

#include "utilities/Parameter_rt.h"
#include "Market_Preset.h"
using namespace hku;
namespace rt {
	inline int null_callback(const string&, const string&, const string&, const string&, price_t, price_t, int, const Datetime&) {
		return 0;
	}
	//�ú���ָ��ɣ����ú��������ˣ��������Ը�ֵNULL��������bool�ж�
	using F_CALLBACK = int(*)(const string&, const string&, const string&, const string&, price_t, price_t, int, const Datetime&);
	
	//����ö�����������棬��Ȼ.cpp�ĺ�������ֵ������
	typedef shared_ptr<Parameter> ParameterPtr;

	class RT_API Order_rt {
		//TODO operator=, Order_rt(const Order_rt&)
		//ȥ��Parameter
		PARAMETER_SUPPORT
	public:
		Order_rt(
			price_t price = 0.0,
			const string& date = "",
			const Datetime& datetime = hku::Null<Datetime>(),
			const Datetime& sending_time = hku::Null<Datetime>(),
			const DatetimeList& trade_time = hku::Null<DatetimeList>(),
			price_t amount = 0.0,
			const string& market_type = "",
			const string& frequence = "",
			int towards = rt::ORDER_DIRECTION::OTHER,
			const string& code = "",
			const string& user_cookie = "",
			const string& account_cookie = "",
			const string& strategy = "",
			const string& order_model = "",
			price_t money = 0.0,
			const string& amount_model = "",
			const string& broker = "",
			const string& order_id = "",
			const StringList& trades_ids = hku::Null<StringList>(),
			const string& status = rt::ORDER_STATUS::NEW,
			F_CALLBACK callback = null_callback,
			price_t commission_coeff = 0.00025,
			price_t tax_coeff = 0.001,
			const string& exchange_id = "",
			const string& position_id = "",
			const Parameter& params = hku::Null<Parameter>());

		//���������ί������
		price_t pending_amount() const;

		friend ostream& operator<<(ostream& os, const Order_rt& order);
		//transform_dt(Datetime datetime) -- ���ܣ��ı����ڸ�ʽ, �����������������datetime��obj�����������ȥ

		string status();

		//�Ժ���ͳһ�ڻ�/��Ʊ�ĵ�λ
		price_t calc_commission(
			price_t trade_price,	//�ڻ���ÿ�ּ۸�	��Ʊ��ÿ�ɼ۸�
			price_t trade_amount);	//�ڻ���������		��Ʊ������


		string get_exchange(const string& instrument_code) const;

		//��������
		void create();

		//����
		//�������� = m_amount - m_trade_amount;
		void cancel();

		//ʧ�ܶ���
		//��������ʧ��(��ϵ�/����ϵ�/�۸������ͣ��/�۸���ڵ�ͣ��/ͨѶʧ��)
		void failed(const string& reason);

		void queued(const string& realorder_id);

		void settle();

		//���map<string, boost::any>������Ϣ
		//��json��д
		ParameterPtr trade_message(
			const string& trade_id,
			price_t trade_price,
			price_t trade_amount,
			const string& trade_time);

		//����״̬, ��ǰ����ֵΪbool����������Ҫ����trade_message,����ͳһ��ΪParameterPtr, ��ParameterPtrΪNull��ȼ���false
		//�����trade_time��string���ͣ���ΪParameter��֧��Datetime
		//���Ƿ���ָ�����ʽ����ӵı��bool
		ParameterPtr trade(const string& trade_id, price_t trade_price, price_t trade_amount, const Datetime& trade_time);

		string order_id() const;
		//price_t volume() const;
		price_t amount() const;
		price_t price() const;
		int towards() const;
		//TODO д����settle�����������ˣ������to_dict,from_dict ��ûʵ��

	private:
		//hikyuu��Ƶ�ʱ��û��const����market, code, name��
		// ����δ֪������ͳһ��string����
		//����List֮����ÿ����Listptr��Ϊ�������ͣ�����Ϊ��Ϊ��Ա���������ptr�����޷�ָ��һ���ڴ棬��Ϊ��Ա������ԭʼ���ڴ档
		price_t m_price;						//ί�м۸�(�޼۵���)
		// date ί������(һ�����߼���ز���)
		string m_date;
		Datetime m_datetime;					//��ǰʱ��
		Datetime m_sending_time;				//ί��ʱ��
		DatetimeList m_trade_time;				//�ɽ�ʱ�� (����/����/ʵ��ʱ�ã�һ�ʶ�����γɽ��᲻��append��ȥ)

		price_t	m_amount;						//ί������
		price_t m_trade_amount;					//�ɽ�����
		price_t m_cancel_amount;				//��������
		// frequence �ز���
		string m_frequence;
		int m_towards;							//�������� rt::ORDER_DIRECTION
		string m_code;							//ί��֤ȯ����, �ڻ���"AU", ��Ʊ:"000001"

		string m_user_cookie;					//����������
		string m_account_cookie;				//���������˻��ı�ʶ

		string m_market_type;					//rt::MARKET_TYPE
		string m_type;							//rt::MARKET_TYPE

		string m_strategy;						//���Ժ�

		string m_order_model;					//ί�з�ʽ(�޼�/�м�/��һ��bar)  rt::ORDER_MODEL
		string m_amount_model;					//ί����ģʽ(����ί��/���ܳɽ���ί��)  rt::AMOUNT_MODEL

		string m_order_id;						//ί�е�id
		string m_realorder_id;
		StringList m_trades_ids;				//�ɽ���id bool����?

		price_t m_commission_coeff;				//������ϵ��
		price_t m_tax_coeff;					//ӡ��˰ϵ��

		shared_ptr<rt::Future_Type> m_market_preset;
		price_t m_trade_price;

		string m_broker;						//����δ֪������ͳһ��string����
		F_CALLBACK m_callback;					//ί�гɹ���callback
		price_t m_money;						//�������

		StringList m_reason;					//����ʧ��ԭ��
		string m_exchange_id;					//rt::EXCHANGE_ID

		string m_time_condition;				//rt::TIME_CONDITION
		string m_status;						//������rt::ORDER_STATUS����������, ��Ϊ���캯������private��
		rt::EXCHANGE_CODE m_exchange_code;		//�ڻ���Լ����"sn1901"

		string m_position_id;
		string m_mainacc_id;
		string m_subacc_id;

		string m_direction;						//ֻ��buy/sell��towards ��int������buy, buy_open, buy_close,sell��...
		string m_offset;						//��ƽ��ʶ��open/close
		string m_volume_condition;
		string m_message;
	};
}