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
	//用函数指针吧，不用函数引用了，这样可以赋值NULL用来当作bool判断
	using F_CALLBACK = int(*)(const string&, const string&, const string&, const string&, price_t, price_t, int, const Datetime&);
	
	//这个得定义在类的外面，不然.cpp的函数返回值看不见
	typedef shared_ptr<Parameter> ParameterPtr;

	class RT_API Order_rt {
		//TODO operator=, Order_rt(const Order_rt&)
		//去掉Parameter
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

		//计算待处理订委托数量
		price_t pending_amount() const;

		friend ostream& operator<<(ostream& os, const Order_rt& order);
		//transform_dt(Datetime datetime) -- 功能：改变日期格式, 但是由于我们这里的datetime是obj，这个功能舍去

		string status();

		//以后考虑统一期货/股票的单位
		price_t calc_commission(
			price_t trade_price,	//期货：每手价格，	股票：每股价格
			price_t trade_amount);	//期货：手数，		股票：股数


		string get_exchange(const string& instrument_code) const;

		//创建订单
		void create();

		//撤单
		//撤单数量 = m_amount - m_trade_amount;
		void cancel();

		//失败订单
		//订单创建失败(如废单/场外废单/价格高于涨停价/价格低于跌停价/通讯失败)
		void failed(const string& reason);

		void queued(const string& realorder_id);

		void settle();

		//输出map<string, boost::any>交易信息
		//用json重写
		ParameterPtr trade_message(
			const string& trade_id,
			price_t trade_price,
			price_t trade_amount,
			const string& trade_time);

		//交易状态, 以前返回值为bool，但是这里要返回trade_message,所以统一改为ParameterPtr, 若ParameterPtr为Null则等价于false
		//这里的trade_time用string类型，因为Parameter不支持Datetime
		//考虑返回指针的形式来间接的表达bool
		ParameterPtr trade(const string& trade_id, price_t trade_price, price_t trade_amount, const Datetime& trade_time);

		string order_id() const;
		//price_t volume() const;
		price_t amount() const;
		price_t price() const;
		int towards() const;
		//TODO 写到了settle基本功能有了，下面的to_dict,from_dict 还没实现

	private:
		//hikyuu设计的时候没用const包括market, code, name等
		// 对于未知类型先统一用string代替
		//以下List之所以每采用Listptr作为变量类型，是因为作为成员如果类型是ptr它们无法指向一块内存，因为成员就是最原始的内存。
		price_t m_price;						//委托价格(限价单用)
		// date 委托日期(一般日线级别回测用)
		string m_date;
		Datetime m_datetime;					//当前时间
		Datetime m_sending_time;				//委托时间
		DatetimeList m_trade_time;				//成交时间 (分钟/日线/实盘时用，一笔订单多次成交会不断append进去)

		price_t	m_amount;						//委托数量
		price_t m_trade_amount;					//成交手数
		price_t m_cancel_amount;				//撤单数量
		// frequence 回测用
		string m_frequence;
		int m_towards;							//买卖方向 rt::ORDER_DIRECTION
		string m_code;							//委托证券代码, 期货："AU", 股票:"000001"

		string m_user_cookie;					//订单发起者
		string m_account_cookie;				//订单发起账户的标识

		string m_market_type;					//rt::MARKET_TYPE
		string m_type;							//rt::MARKET_TYPE

		string m_strategy;						//策略号

		string m_order_model;					//委托方式(限价/市价/下一个bar)  rt::ORDER_MODEL
		string m_amount_model;					//委托量模式(按量委托/按总成交额委托)  rt::AMOUNT_MODEL

		string m_order_id;						//委托单id
		string m_realorder_id;
		StringList m_trades_ids;				//成交单id bool类型?

		price_t m_commission_coeff;				//手续费系数
		price_t m_tax_coeff;					//印花税系数

		shared_ptr<rt::Future_Type> m_market_preset;
		price_t m_trade_price;

		string m_broker;						//对于未知类型先统一用string代替
		F_CALLBACK m_callback;					//委托成功的callback
		price_t m_money;						//订单金额

		StringList m_reason;					//订单失败原因
		string m_exchange_id;					//rt::EXCHANGE_ID

		string m_time_condition;				//rt::TIME_CONDITION
		string m_status;						//不能用rt::ORDER_STATUS来声明变量, 因为构造函数被我private了
		rt::EXCHANGE_CODE m_exchange_code;		//期货合约代码"sn1901"

		string m_position_id;
		string m_mainacc_id;
		string m_subacc_id;

		string m_direction;						//只有buy/sell，towards 是int包括了buy, buy_open, buy_close,sell等...
		string m_offset;						//开平标识，open/close
		string m_volume_condition;
		string m_message;
	};
}