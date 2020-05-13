/*
 * Author: wfh1300
 * Data: 2020/04/23
 */

#pragma once
#include <string>
#include <map>
#include "EXCHANGE_CODE.h"
#define ZERO_PRICE_T 1e-8
#ifndef RT_API //RT_APIΪ��ɫ��ʾ������
#define RT_API //RT_APIΪ��ɫ����ʾ���ﱻִ��
#endif

// include <hikyuu.h>
using namespace std;
// ����ʵ�� �µ������ռ� rt: real time
// ���δ������������
namespace rt {

	class RT_API AMOUNT_MODEL {//��Ӧ��hikyuu�� trade_sys/moneymanager/imp
	public:
		static const string BY_MONEY;//���չ̶��ɽ��ܶ��µ�
		static const string BY_AMOUNT;//���չ̶������µ�
	private:
		AMOUNT_MODEL() {}
	};

	class RT_API EXCHANGE_ID {
		//�þ�̬��Ա����ö��
	public:
		static const string SSE; // �Ͻ���
		static const string SZSE; // ���
		static const string SHFE; //������
		static const string DCE; // ������
		static const string CZCE; //֣����
		static const string CFFEX; //�н���
		static const string INE; //��Դ����
	private:
		EXCHANGE_ID() {}
	};

	class RT_API MARKET_TYPE {
	public:
		static const string STOCK_CN; //�й�A��
		static const string STOCK_CN_B; //�й�B��
		static const string STOCK_CN_D; //�й�D�� ����ͨ
		static const string STOCK_HK; //�۹�
		static const string STOCK_US; //����
		static const string FUTURE_CN; //�����ڻ�
		static const string OPTION_CN; //������Ȩ
		static const string STOCKOPTIN_CN; //������Ȩ
		static const string CRYPTOCURRENCY; //���ܻ���(��������)
		static const string INDEX_CN; //�й�ָ��
		static const string FUND_CN; //�й�����
		static const string BOND_CN; //�й�ծȯ
	private:
		MARKET_TYPE() {}
	};

	
	class RT_API ORDER_MODEL {					//���嶩��������ʱ����
	public:
		static const string LIMIT;		//�޼�
		static const string ANY;		//�м�(otg����)
		static const string MARKET;		//�мۣ��ڻز������¸�bar�Ŀ��̼����룬ʵ�̾����嵵ʣ�����ųɽ���
		static const string CLOSE;		//��ǰbar�����̼�����
		static const string NEXT_OPEN;	//�¸�bar�Ŀ��̼�����
		static const string STRICT_;	//�ϸ�ģʽ�����Ƽ������޻ز�����ã�
		static const string BEST;		//�н��� ���ųɽ�ʣ��ת��
	private:
		ORDER_MODEL() {}
	};

	class RT_API ORDER_DIRECTION {
		//��int����string�� Ϊ��BUY + SELL = 0��
	public:
		static int BUY;				//��Ʊ����
		static int SELL;			//��Ʊ����
		static int BUY_OPEN;		//�ڻ� �࿪
		static int BUY_CLOSE;		//�ڻ� ��ƽ
		static int SELL_OPEN;		//�ڻ� �տ�
		static int SELL_CLOSE;		//�ڻ���ƽ
		static int SELL_CLOSETODAY;
		static int BUY_CLOSETODAY;

		static int ASK;				//�깺
		static int XDXR;
		static int OTHER;
	private:
		ORDER_DIRECTION() {}
	};
	class RT_API ORDER_STATUS {
		/*
		status1xx ����������
		status3xx ��ʼ������  ��ʱ�۳��ʲ�(�����ֽ�/�����ɷ�)
		status3xx �������(�ȴ�����)
		status2xx ������ȫ����/δ��ȫ����
		status4xx ��������
		status500 ��������(ÿ�ս���) �ָ���ʱ�ʲ�    

		��������(100) -- ������ɽ�����(300) -- ��ȫ�ɽ�(200) -- ÿ�ս���(500)-- ����
		��������(100) -- ������ɽ�����(300) -- ���ֳɽ�(203) -- δ�ɽ�(300) -- ÿ�ս���(500) -- ����
		��������(100) -- ������ɽ�����(300) -- ��������(400) -- ÿ�ս���(500) -- ����
		*/
	public:
		static const string NEW;
		static const string SUCCESS_ALL;
		static const string SUCCESS_PART;
		static const string QUEUED; //���ڱ�ʾ��order_queue�� ʵ�ʱ�����˼�Ƕ������ ���ɽ� == ALIVED
		static const string CANCEL_ALL;
		static const string CANCEL_PART;
		static const string SETTLED;
		static const string FAILED;
		static const string NEXT; //��ǰbarδ�ɽ�����һ��bar�����ȴ�
	private:
		ORDER_STATUS() {}
	};

	class RT_API TIME_CONDITION {
	public:
		//��Ȩ�޼��걨���м��걨ָ�
		//http://doc.shinnytech.com/diff/latest/funcset/trade.html#account
		static const string IOC;//������ɣ�������
		static const string GFS;//������Ч
		static const string GFD;//������Ч
		static const string GTD;//ָ������ǰ��Ч
		static const string GTC;//����ǰ��Ч
		static const string GFA;//���Ͼ�����Ч
	private:
		TIME_CONDITION() {}
	};
	struct RT_API Future_Type {
		/*
		 unit_table ��Լ����
		 price_tick ÿ�����

		 buy_frozen_coeff ��ͷ���ֱ�֤��ϵ��
		 sell_frozen_coeff ��ͷ���ֱ�֤��ϵ��

		 commission_coeff_peramount ����������������ϵ�� ->��������Ǯ��
		 commission_coeff_pervol �����������������ϵ��
		 commission_coeff_today_peramount �����������ƽ��������ϵ��
		 commission_coeff_today_pervol �����������ƽ��������ϵ��
		*/
		Future_Type();
		Future_Type(const string& name, const double unit_table, const double price_tick, const double buy_frozen_coeff,
			const double sell_frozen_coeff, const string& exchange, const double commission_coeff_peramount,
			const double commission_coeff_pervol, const double commission_coeff_today_peramount, const double commission_coeff_today_pervol);

		Future_Type& operator=(const Future_Type& rhs);
		friend ostream& operator<<(ostream& os, const Future_Type& ft);//���������

		//���³�Ա��������Ϊconst����ΪҪ���ظ�ֵ�����
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