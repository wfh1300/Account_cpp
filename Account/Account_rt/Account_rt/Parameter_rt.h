/*
 * Author: wfh1300
 * Data: 2020/04/23
 */

#pragma once
#include <string>
#include <map>
#include "EXCHANGE_CODE.h"
#define ZERO_PRICE_T 1e-8
#ifndef RT_API //RT_API为灰色表示进来了
#define RT_API //RT_API为橙色，表示这里被执行
#endif

// include <hikyuu.h>
using namespace std;
// 引入实盘 新的命名空间 rt: real time
// 类均未定义析构函数
namespace rt {

	class RT_API AMOUNT_MODEL {//对应于hikyuu中 trade_sys/moneymanager/imp
	public:
		static const string BY_MONEY;//按照固定成交总额下单
		static const string BY_AMOUNT;//按照固定数量下单
	private:
		AMOUNT_MODEL() {}
	};

	class RT_API EXCHANGE_ID {
		//用静态成员创建枚举
	public:
		static const string SSE; // 上交所
		static const string SZSE; // 深交所
		static const string SHFE; //上期所
		static const string DCE; // 大商所
		static const string CZCE; //郑商所
		static const string CFFEX; //中金所
		static const string INE; //能源中心
	private:
		EXCHANGE_ID() {}
	};

	class RT_API MARKET_TYPE {
	public:
		static const string STOCK_CN; //中国A股
		static const string STOCK_CN_B; //中国B股
		static const string STOCK_CN_D; //中国D股 沪伦通
		static const string STOCK_HK; //港股
		static const string STOCK_US; //美股
		static const string FUTURE_CN; //国内期货
		static const string OPTION_CN; //国内期权
		static const string STOCKOPTIN_CN; //个股期权
		static const string CRYPTOCURRENCY; //加密货币(衍生货币)
		static const string INDEX_CN; //中国指数
		static const string FUND_CN; //中国基金
		static const string BOND_CN; //中国债券
	private:
		MARKET_TYPE() {}
	};

	
	class RT_API ORDER_MODEL {					//定义订单的买入时机类
	public:
		static const string LIMIT;		//限价
		static const string ANY;		//市价(otg兼容)
		static const string MARKET;		//市价，在回测里是下个bar的开盘价买入，实盘就是五档剩余最优成交价
		static const string CLOSE;		//当前bar的收盘价买入
		static const string NEXT_OPEN;	//下个bar的开盘价买入
		static const string STRICT_;	//严格模式，不推荐（仅限回测测试用）
		static const string BEST;		//中金所 最优成交剩余转限
	private:
		ORDER_MODEL() {}
	};

	class RT_API ORDER_DIRECTION {
		//用int不用string是 为了BUY + SELL = 0吗？
	public:
		static int BUY;				//股票买入
		static int SELL;			//股票卖出
		static int BUY_OPEN;		//期货 多开
		static int BUY_CLOSE;		//期货 空平
		static int SELL_OPEN;		//期货 空开
		static int SELL_CLOSE;		//期货多平
		static int SELL_CLOSETODAY;
		static int BUY_CLOSETODAY;

		static int ASK;				//申购
		static int XDXR;
		static int OTHER;
	private:
		ORDER_DIRECTION() {}
	};
	class RT_API ORDER_STATUS {
		/*
		status1xx 订单待生成
		status3xx 初始化订单  临时扣除资产(可用现金/可卖股份)
		status3xx 订单存活(等待交易)
		status2xx 订单完全交易/未完全交易
		status4xx 主动撤单
		status500 订单死亡(每日结算) 恢复临时资产    

		订单生成(100) -- 进入待成交队列(300) -- 完全成交(200) -- 每日结算(500)-- 死亡
		订单生成(100) -- 进入待成交队列(300) -- 部分成交(203) -- 未成交(300) -- 每日结算(500) -- 死亡
		订单生成(100) -- 进入待成交队列(300) -- 主动撤单(400) -- 每日结算(500) -- 死亡
		*/
	public:
		static const string NEW;
		static const string SUCCESS_ALL;
		static const string SUCCESS_PART;
		static const string QUEUED; //用于表示在order_queue中 实际表达的意思是订单存货 待成交 == ALIVED
		static const string CANCEL_ALL;
		static const string CANCEL_PART;
		static const string SETTLED;
		static const string FAILED;
		static const string NEXT; //当前bar未成交，下一个bar继续等待
	private:
		ORDER_STATUS() {}
	};

	class RT_API TIME_CONDITION {
	public:
		//期权限价申报和市价申报指令：
		//http://doc.shinnytech.com/diff/latest/funcset/trade.html#account
		static const string IOC;//立即完成，否则撤销
		static const string GFS;//本节有效
		static const string GFD;//当日有效
		static const string GTD;//指定日期前有效
		static const string GTC;//撤销前有效
		static const string GFA;//集合竞价有效
	private:
		TIME_CONDITION() {}
	};
	struct RT_API Future_Type {
		/*
		 unit_table 合约乘数
		 price_tick 每跳差价

		 buy_frozen_coeff 多头开仓保证金系数
		 sell_frozen_coeff 空头开仓保证金系数

		 commission_coeff_peramount 按总量计算手续费系数 ->总量：总钱数
		 commission_coeff_pervol 按手数计算的手续费系数
		 commission_coeff_today_peramount 按总量计算的平今手续费系数
		 commission_coeff_today_pervol 按手数计算的平今手续费系数
		*/
		Future_Type();
		Future_Type(const string& name, const double unit_table, const double price_tick, const double buy_frozen_coeff,
			const double sell_frozen_coeff, const string& exchange, const double commission_coeff_peramount,
			const double commission_coeff_pervol, const double commission_coeff_today_peramount, const double commission_coeff_today_pervol);

		Future_Type& operator=(const Future_Type& rhs);
		friend ostream& operator<<(ostream& os, const Future_Type& ft);//重载输出流

		//以下成员不能声明为const，因为要重载赋值运算符
		string name() const;
		double unit_table() const;
		double price_tick() const;
		double buy_frozen_coeff() const;
		double sell_frozen_coeff() const;
		string exchange() const;
		double commission_coeff_peramount() const;
		double commission_coeff_pervol() const;
		double commission_coeff_today_peramount() const;
		double commission_coeff_today_pervol() const;
	private:
		string m_name;
		double m_unit_table;
		double m_price_tick;
		double m_buy_frozen_coeff;
		double m_sell_frozen_coeff;
		string m_exchange;
		double m_commission_coeff_peramount;
		double m_commission_coeff_pervol;
		double m_commission_coeff_today_peramount;
		double m_commission_coeff_today_pervol;
	};
	inline string Future_Type::name() const {
		return m_name;
	}
	inline double Future_Type::unit_table() const {
		return m_unit_table;
	}
	inline double Future_Type::price_tick() const {
		return m_price_tick;
	}
	inline double Future_Type::buy_frozen_coeff() const {
		return m_buy_frozen_coeff;
	}
	inline double Future_Type::sell_frozen_coeff() const {
		return m_sell_frozen_coeff;
	}
	inline string Future_Type::exchange() const {
		return m_exchange;
	}
	inline double Future_Type::commission_coeff_peramount() const {
		return m_commission_coeff_peramount;
	}
	inline double Future_Type::commission_coeff_pervol() const {
		return m_commission_coeff_pervol;
	}
	inline double Future_Type::commission_coeff_today_peramount() const {
		return m_commission_coeff_today_peramount;
	}
	inline double Future_Type::commission_coeff_today_pervol() const {
		return m_commission_coeff_today_pervol;
	}
}