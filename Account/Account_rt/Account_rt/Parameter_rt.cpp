/*
 * Author: wfh1300
 * Data: 2020/04/25
 */
#include "Parameter_rt.h"
#include <iostream>

namespace rt {

	//--------------------------------------------------------------------------------------

	const string AMOUNT_MODEL::BY_MONEY("by_money");//按照固定成交总额下单
	const string AMOUNT_MODEL::BY_AMOUNT("by_amount");//按照固定数量下单

	//--------------------------------------------------------------------------------------

	//const string EXCHANGE_ID::SSE("sse") 和 const string EXCHANGE_ID::SSE = "sse" 哪个好？
	const string EXCHANGE_ID::SSE("SSE"); 
	const string EXCHANGE_ID::SZSE("SZSE");
	const string EXCHANGE_ID::SHFE("SHFE");
	const string EXCHANGE_ID::DCE("DCE");
	const string EXCHANGE_ID::CZCE("CZCE");
	const string EXCHANGE_ID::CFFEX("CFFEX");
	const string EXCHANGE_ID::INE("INE");

	//--------------------------------------------------------------------------------------
	
	const string MARKET_TYPE::STOCK_CN("stock_cn"); //中国A股
	const string MARKET_TYPE::STOCK_CN_B("stock_cn_b"); //中国B股
	const string MARKET_TYPE::STOCK_CN_D("stock_cn_d"); //中国D股 沪伦通
	const string MARKET_TYPE::STOCK_HK("stock_hk"); //港股
	const string MARKET_TYPE::STOCK_US("stock_us"); //美股
	const string MARKET_TYPE::FUTURE_CN("future_cn"); //国内期货
	const string MARKET_TYPE::OPTION_CN("option_cn"); //国内期权
	const string MARKET_TYPE::STOCKOPTIN_CN("stockoption_cn"); //个股期权
	const string MARKET_TYPE::CRYPTOCURRENCY("cryptocurrency"); //加密货币(衍生货币)
	const string MARKET_TYPE::INDEX_CN("index_cn"); //中国指数
	const string MARKET_TYPE::FUND_CN("fund_cn"); //中国基金
	const string MARKET_TYPE::BOND_CN("bond_cn"); //中国债券

	//--------------------------------------------------------------------------------------

	const string ORDER_MODEL::LIMIT("LIMIT");		//限价
	const string ORDER_MODEL::ANY("ANY");		//市价(otg兼容)
	const string ORDER_MODEL::MARKET("MARKET");		//市价，在回测里是下个bar的开盘价买入，实盘就是五档剩余最优成交价
	const string ORDER_MODEL::CLOSE("CLOSE");		//当前bar的收盘价买入
	const string ORDER_MODEL::NEXT_OPEN("NEXT_OPEN");	//下个bar的开盘价买入
	const string ORDER_MODEL::STRICT_("STRICT");	//严格模式，不推荐（仅限回测测试用）
	const string ORDER_MODEL::BEST("BEST");		//中金所 最优成交剩余转限

	//--------------------------------------------------------------------------------------

	int ORDER_DIRECTION::BUY(1);			//股票买入
	int ORDER_DIRECTION::SELL(-1);			//股票卖出
	int ORDER_DIRECTION::BUY_OPEN(2);		//期货 多开
	int ORDER_DIRECTION::BUY_CLOSE(3);		//期货 空平
	int ORDER_DIRECTION::SELL_OPEN(-2);		//期货 空开
	int ORDER_DIRECTION::SELL_CLOSE(-3);	//期货多平
	int ORDER_DIRECTION::SELL_CLOSETODAY(-4);
	int ORDER_DIRECTION::BUY_CLOSETODAY(4);

	int ORDER_DIRECTION::ASK(0);			//申购
	int ORDER_DIRECTION::XDXR(5);
	int ORDER_DIRECTION::OTHER(6);
	
	//--------------------------------------------------------------------------------------

	const string ORDER_STATUS::NEW("new");
	const string ORDER_STATUS::SUCCESS_ALL("success_all");
	const string ORDER_STATUS::SUCCESS_PART("success_part");
	const string ORDER_STATUS::QUEUED("queued"); //用于表示在order_queue中 实际表达的意思是订单存货 待成交 == ALIVED
	const string ORDER_STATUS::CANCEL_ALL("cancel_all");
	const string ORDER_STATUS::CANCEL_PART("cancel_part");
	const string ORDER_STATUS::SETTLED("settled");
	const string ORDER_STATUS::FAILED("failed");
	const string ORDER_STATUS::NEXT("next"); //当前bar未成交，下一个bar继续等待

	//--------------------------------------------------------------------------------------

	const string TIME_CONDITION::IOC("IOC");//立即完成，否则撤销
	const string TIME_CONDITION::GFS("GFS");//本节有效
	const string TIME_CONDITION::GFD("GFD");//当日有效
	const string TIME_CONDITION::GTD("GTD");//指定日期前有效
	const string TIME_CONDITION::GTC("GTC");//撤销前有效
	const string TIME_CONDITION::GFA("GFA");//集合竞价有效

	//--------------------------------------------------------------------------------------
	// struct Future_Type
	Future_Type::Future_Type() :
		m_name(""), m_unit_table(0), m_price_tick(0), m_buy_frozen_coeff(0), m_sell_frozen_coeff(0), m_exchange(""),
		m_commission_coeff_peramount(0), m_commission_coeff_pervol(0),
		m_commission_coeff_today_peramount(0), m_commission_coeff_today_pervol(0) {}

	Future_Type::Future_Type(const string& name, const double unit_table, const double price_tick, const double buy_frozen_coeff,
		const double sell_frozen_coeff, const string& exchange, const double commission_coeff_peramount,
		const double commission_coeff_pervol, const double commission_coeff_today_peramount, const double commission_coeff_today_pervol) :
		m_name(name), m_unit_table(unit_table), m_price_tick(price_tick), m_buy_frozen_coeff(buy_frozen_coeff),
		m_sell_frozen_coeff(sell_frozen_coeff), m_exchange(exchange),
		m_commission_coeff_peramount(commission_coeff_peramount), m_commission_coeff_pervol(commission_coeff_pervol),
		m_commission_coeff_today_peramount(commission_coeff_today_peramount),
		m_commission_coeff_today_pervol(commission_coeff_today_pervol) {}
	
	Future_Type& Future_Type::operator=(const Future_Type& rhs) {
		if (this == &rhs) {
			return *this;
		}

		this->m_name = rhs.m_name;
		this->m_unit_table = rhs.m_unit_table;
		this->m_price_tick = rhs.m_price_tick;
		this->m_buy_frozen_coeff = rhs.m_buy_frozen_coeff;
		this->m_sell_frozen_coeff = rhs.m_sell_frozen_coeff;
		this->m_exchange = rhs.m_exchange;
		this->m_commission_coeff_peramount = rhs.m_commission_coeff_peramount;
		this->m_commission_coeff_pervol = rhs.m_commission_coeff_pervol;
		this->m_commission_coeff_today_peramount = rhs.m_commission_coeff_today_peramount;
		this->m_commission_coeff_today_pervol = rhs.m_commission_coeff_today_pervol;
		return *this;
	}

	ostream& operator<<(ostream& os, const Future_Type& ft) {
		os << "期货: " << ft.m_name << endl;
		os << "合约乘数: " << ft.m_unit_table << endl;
		os << "每跳差价: " << ft.m_price_tick << endl;
		os << "多头开仓保证金系数: " << ft.m_buy_frozen_coeff << endl;
		os << "空头开仓保证金系数: " << ft.m_sell_frozen_coeff << endl;
		os << "交易所ID: " << ft.m_exchange << endl;
		os << "按总量计算手续费系数: " << ft.m_commission_coeff_peramount << endl;
		os << "按手数计算的手续费系数: " << ft.m_commission_coeff_pervol << endl;
		os << "按总量计算的平今手续费系数: " << ft.m_commission_coeff_today_peramount << endl;
		os << "按手数计算的平今手续费系数: " << ft.m_commission_coeff_today_pervol << endl;
		//...
		return os; //return os只是保证可以cout << obj1 << obj2 和前面的os<<"name: "<< endl每关系
	}
}


