//2020/05/06
//wfh1300

//将所有的amount改为int64类型？
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
	typedef shared_ptr<Order_rt> Order_rt_Ptr;//因为Order_rt没定义operator=
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
			price_t moneypreset = 100000.0, //初始分配资金
			const Str_Price_t& frozen = hku::Null<Str_Price_t>(),
			price_t moneypresetLeft = -1,//负数表示default
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

		//这里被写成函数，不是成员，可能是因为它们会随着一些成员的改变而改变吧。
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

		//检查订单是否符合条件
		bool order_check(/*int64*/price_t amount, price_t price, int towards, const string& order_id);

		//send_order() 返回类型到底是用Parameter还是Order_rt?
		//用Paramter吧，它给的字段不全，不足以构建一个完整的Order_rt
		string send_order(price_t amount, price_t price, int towards);

		//更新仓位
		void update_pos(
			price_t price, 
			price_t amount, //股票：股数，期货：手数
			int towards, 
			price_t& profit_out, 
			price_t& marginValue_out);
		
		//收盘后的结算事件
		void settle();

		
		void current_position();
		void close_available();
		void change_moneypreset(price_t money);

		//应该被废弃吧？
		price_t calc_commission(price_t trade_price, amount_t trade_amount, int trade_towards);

		void save();

		//on_xx系列，可以理解为 当xx的时候，我们的处理方法。
		void on_price_change(price_t price);
		void on_order(/*const */Order_rt& order);
		//void on_transaction
		//void on_bar(), 这个形参没考虑好用json还是用hku::KData;先放着
		//void on_tick(), 同理
		//reload
		//loadfrommessage
		//readdiff
		//以上没有实现，后续考虑实现

	private:
		string m_code;							//品种名称 "AU"
		string m_account_cookie;
		string m_portfolio_cookie;
		string m_username;
		Datetime m_time;						//lastupdatetime这里我没写date
		shared_ptr<rt::Future_Type> m_market_preset;
		string m_position_id;
		price_t m_moneypreset;					//初始给账户分配的资金,pre预先 set设置，一般不对其进行操作
		price_t m_moneypresetLeft;				//账户剩余的资金，买/卖 操作这个变量
		string m_rule;							//"FIFO"
		string m_name;							//"原油"
		string m_market_type;
		string m_exchange_id;

		//cost = price * volume * unit_table; 或者 cost = price * amount
		//volume和cost 成正比啊
		//用volume表示手数? 还是 volume表示持有量 amount表示交易量？
		price_t m_volume_long_his;				//昨仓，多单持仓, 考虑到股票T+1，这里可以判断交易量
		price_t m_volume_long_today;			//今仓，多单持仓
		price_t m_volume_short_his;				//昨仓，空单持仓
		price_t m_volume_short_today;			//今仓，空单持仓

		price_t m_volume_long_frozen_his;		//多单昨日冻结
		price_t m_volume_long_frozen_today;		//多单今日冻结
		price_t m_volume_short_frozen_his;		//空单昨日冻结
		price_t m_volume_short_frozen_today;	//空单今日冻结
		//冻结资金和保证金区别？
		price_t m_margin_long;					//多单保证金 100元买1000元的期货，降价扣掉
		price_t m_margin_short;					//空单保证金 100元卖1000元的期货，涨价扣掉

		//每手
		price_t m_open_price_long;				//多单开仓均价，每手
		price_t m_open_price_short;				//空单开仓均价
		price_t m_position_price_long;			//逐日盯市的前一交易日的结算均价
		price_t m_position_price_short;			//逐日盯市的前一交易日的结算均价

		price_t m_open_cost_long;				//多单开仓成本(指的是保证金冻结) -- 开多仓后 钱包钱减少 这个cost也是绝对值，计算时-cost
		price_t m_open_cost_short;				//空单开仓成本 -- 开空仓后 钱包钱增加，这个cost用的是绝对值，计算时+cost
		price_t m_position_cost_long;			//多单持仓成本(指的是逐日盯市制度下的成本价)
		price_t m_position_cost_short;			//空单持仓成本
		//position price : 昨日结算价，open price：今日开仓价
		//position cost: 按照逐日盯市计算的持仓成本，open cost:按照正常交易的持仓成本
		//position 是以昨天为购买点考虑的
		//open以初始购买点作为考虑

		price_t m_last_price;					//期货每单位价格不是每手价格
		price_t m_commission;
		StringList m_trades;

		string m_orders;
		//Str_Order m_orders;	//用这个试试
		//json字符串，用string表示，要时刻更新(m_orders = new_orders)。
		//rapidjson::Document 无法=赋值，所以只能是string
		//这里没有用rapidjson::Document; 主要考虑到转化为string时需要额外创建writer和StringBuffer,会造成不方便
		//如果用const char *那么就无法改变，
		//如果用char m_orders[]，m_orders不是左值
		Str_Price_t m_frozen;					//一个(order_id : frozen_money)的字典
		string m_spms_id;
		string m_oms_id;
		bool m_allow_exceed;

		//以下成员是我自己添加的，为了支持股票和期货通用
		//quantaxis在获取unit_table时通过self.market_preset.get("unit_table", 1)
		//那么对于无法获取的股票code，它会将unit_table默认设置为1
		//而C++这里因为不支持dict.get()这样的语法糖，如果market_preset为NULL pointer，就会出现异常，
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