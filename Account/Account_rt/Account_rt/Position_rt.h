//2020/05/06
//wfh1300

//�����е�amount��Ϊint64���ͣ�
#pragma once
#ifndef RT_API
#define RT_API
#endif
#include <hikyuu/datetime/Datetime.h>
#include <hikyuu/DataType.h>
#include <hikyuu/utilities/Parameter.h>
#include <hikyuu/utilities/Null.h>
#include "utilities/Parameter_rt.h"
#include "Order_rt.h"
#include "Map_Any.h"
#include "Market_Preset.h"
#include "type_rt.h"

using namespace hku;
namespace rt {
	typedef shared_ptr<Order_rt> Order_rt_Ptr;//��ΪOrder_rtû����operator=
	typedef map<string, Order_rt_Ptr> Str_Order;

	typedef map<string, ParameterPtr> Str_Params;
	typedef map<string, price_t> Str_Price_t;
	typedef shared_ptr<MapAny> MapAnyPtr;

	class RT_API Position_rt {
	public:
		Position_rt(
			const string& code = "RB",
			const string& account_cookie = "quanth",
			const string& portfolio_cookie = "portfolio",
			const string& username = "quanth",
			price_t moneypreset = 100000.0, //��ʼ�����ʽ�
			const Str_Price_t& frozen = hku::Null<Str_Price_t>(),
			price_t moneypresetLeft = -1,//������ʾdefault
			price_t volume_long_today = 0.0,
			price_t volume_long_his = 0.0,
			price_t volume_short_today = 0.0,
			price_t volume_short_his = 0.0,

			price_t volume_long_frozen_his = 0.0,
			price_t volume_long_frozen_today = 0.0,
			price_t volume_short_frozen_his = 0.0,
			price_t volume_short_frozen_today = 0.0,

			price_t margin_long = 0.0,
			price_t margin_short = 0.0,

			price_t open_price_long = 0.0,
			price_t open_price_short = 0.0,
			price_t position_price_long = 0.0,
			price_t position_price_short = 0.0,

			price_t open_cost_long = 0.0,
			price_t open_cost_short = 0.0,
			price_t position_cost_long = 0.0,
			price_t position_cost_short = 0.0,

			const string& position_id = "",
			const string& market_type = "",
			const string& exchange_id = "",
			const StringList& trades = hku::Null<StringList>(),
			const string& orders = "{}",
			//
			//const Str_Order& orders = hku::Null<Str_Order>(),

			const string& name = "",
			price_t commission = 0.0,
			bool auto_reload = false,
			bool allow_exceed = false,
			const string& spms_id = "",
			const string& oms_id = ""
		);

		//���ﱻд�ɺ��������ǳ�Ա����������Ϊ���ǻ�����һЩ��Ա�ĸı���ı�ɡ�
		price_t m_volume_long();
		price_t m_volume_short();
		price_t m_volume_long_frozen();
		price_t m_volume_short_frozen();
		price_t m_margin();
		price_t m_float_profit_long();
		price_t m_float_profit_short();
		price_t m_float_profit();
		price_t m_position_profit_long();
		price_t m_position_profit_short();
		price_t m_position_profit();

		string static_message();

		//ParameterPtr hold_detail();
		//ParameterPtr realtime_message();

		//��鶩���Ƿ��������
		bool order_check(/*int64*/price_t amount, price_t price, int towards, const string& order_id);

		//send_order() �������͵�������Parameter����Order_rt?
		//��Paramter�ɣ��������ֶβ�ȫ�������Թ���һ��������Order_rt
		string send_order(price_t amount, price_t price, int towards);

		//���²�λ
		void update_pos(
			price_t price, 
			price_t amount, //��Ʊ���������ڻ�������
			int towards, 
			price_t& profit_out, 
			price_t& marginValue_out);
		
		//���̺�Ľ����¼�
		void settle();

		
		void current_position();
		void close_available();
		void change_moneypreset(price_t money);

		//Ӧ�ñ������ɣ�
		price_t calc_commission(price_t trade_price, amount_t trade_amount, int trade_towards);

		void save();

		//on_xxϵ�У��������Ϊ ��xx��ʱ�����ǵĴ�������
		void on_price_change(price_t price);
		void on_order(/*const */Order_rt& order);
		//void on_transaction
		//void on_bar(), ����β�û���Ǻ���json������hku::KData;�ȷ���
		//void on_tick(), ͬ��
		//reload
		//loadfrommessage
		//readdiff
		//����û��ʵ�֣���������ʵ��

	private:
		string m_code;							//Ʒ������ "AU"
		string m_account_cookie;
		string m_portfolio_cookie;
		string m_username;
		Datetime m_time;						//lastupdatetime������ûдdate
		shared_ptr<rt::Future_Type> m_market_preset;
		string m_position_id;
		price_t m_moneypreset;					//��ʼ���˻�������ʽ�,preԤ�� set���ã�һ�㲻������в���
		price_t m_moneypresetLeft;				//�˻�ʣ����ʽ���/�� �����������
		string m_rule;							//"FIFO"
		string m_name;							//"ԭ��"
		string m_market_type;
		string m_exchange_id;

		//cost = price * volume * unit_table; ���� cost = price * amount
		//volume��cost �����Ȱ�
		//��volume��ʾ����? ���� volume��ʾ������ amount��ʾ��������
		price_t m_volume_long_his;				//��֣��൥�ֲ�, ���ǵ���ƱT+1����������жϽ�����
		price_t m_volume_long_today;			//��֣��൥�ֲ�
		price_t m_volume_short_his;				//��֣��յ��ֲ�
		price_t m_volume_short_today;			//��֣��յ��ֲ�

		price_t m_volume_long_frozen_his;		//�൥���ն���
		price_t m_volume_long_frozen_today;		//�൥���ն���
		price_t m_volume_short_frozen_his;		//�յ����ն���
		price_t m_volume_short_frozen_today;	//�յ����ն���
		//�����ʽ�ͱ�֤������
		price_t m_margin_long;					//�൥��֤�� 100Ԫ��1000Ԫ���ڻ������ۿ۵�
		price_t m_margin_short;					//�յ���֤�� 100Ԫ��1000Ԫ���ڻ����Ǽۿ۵�

		//ÿ��
		price_t m_open_price_long;				//�൥���־��ۣ�ÿ��
		price_t m_open_price_short;				//�յ����־���
		price_t m_position_price_long;			//���ն��е�ǰһ�����յĽ������
		price_t m_position_price_short;			//���ն��е�ǰһ�����յĽ������

		price_t m_open_cost_long;				//�൥���ֳɱ�(ָ���Ǳ�֤�𶳽�) -- ����ֺ� Ǯ��Ǯ���� ���costҲ�Ǿ���ֵ������ʱ-cost
		price_t m_open_cost_short;				//�յ����ֳɱ� -- ���ղֺ� Ǯ��Ǯ���ӣ����cost�õ��Ǿ���ֵ������ʱ+cost
		price_t m_position_cost_long;			//�൥�ֲֳɱ�(ָ�������ն����ƶ��µĳɱ���)
		price_t m_position_cost_short;			//�յ��ֲֳɱ�
		//position price : ���ս���ۣ�open price�����տ��ּ�
		//position cost: �������ն��м���ĳֲֳɱ���open cost:�����������׵ĳֲֳɱ�
		//position ��������Ϊ����㿼�ǵ�
		//open�Գ�ʼ�������Ϊ����

		price_t m_last_price;					//�ڻ�ÿ��λ�۸���ÿ�ּ۸�
		price_t m_commission;
		StringList m_trades;

		string m_orders;
		//Str_Order m_orders;	//���������
		//json�ַ�������string��ʾ��Ҫʱ�̸���(m_orders = new_orders)��
		//rapidjson::Document �޷�=��ֵ������ֻ����string
		//����û����rapidjson::Document; ��Ҫ���ǵ�ת��Ϊstringʱ��Ҫ���ⴴ��writer��StringBuffer,����ɲ�����
		//�����const char *��ô���޷��ı䣬
		//�����char m_orders[]��m_orders������ֵ
		Str_Price_t m_frozen;					//һ��(order_id : frozen_money)���ֵ�
		string m_spms_id;
		string m_oms_id;
		bool m_allow_exceed;

		//���³�Ա�����Լ���ӵģ�Ϊ��֧�ֹ�Ʊ���ڻ�ͨ��
		//quantaxis�ڻ�ȡunit_tableʱͨ��self.market_preset.get("unit_table", 1)
		//��ô�����޷���ȡ�Ĺ�Ʊcode�����Ὣunit_tableĬ������Ϊ1
		//��C++������Ϊ��֧��dict.get()�������﷨�ǣ����market_presetΪNULL pointer���ͻ�����쳣��
		price_t m_unit_table;
		price_t m_buy_frozen_coeff;
		price_t m_sell_frozen_coeff;

		//price_t m_price_tick;
		//string m_exchange;
		//price_t m_commission_coeff_peramount;
		//price_t m_commission_coeff_pervol;
		//price_t m_commission_coeff_today_peramount;
		//price_t m_commission_coeff_today_pervol;
	};

}