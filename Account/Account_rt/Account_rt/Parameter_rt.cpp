/*
 * Author: wfh1300
 * Data: 2020/04/25
 */
#include "Parameter_rt.h"
#include <iostream>

namespace rt {

	//--------------------------------------------------------------------------------------

	const string AMOUNT_MODEL::BY_MONEY("by_money");//���չ̶��ɽ��ܶ��µ�
	const string AMOUNT_MODEL::BY_AMOUNT("by_amount");//���չ̶������µ�

	//--------------------------------------------------------------------------------------

	//const string EXCHANGE_ID::SSE("sse") �� const string EXCHANGE_ID::SSE = "sse" �ĸ��ã�
	const string EXCHANGE_ID::SSE("SSE"); 
	const string EXCHANGE_ID::SZSE("SZSE");
	const string EXCHANGE_ID::SHFE("SHFE");
	const string EXCHANGE_ID::DCE("DCE");
	const string EXCHANGE_ID::CZCE("CZCE");
	const string EXCHANGE_ID::CFFEX("CFFEX");
	const string EXCHANGE_ID::INE("INE");

	//--------------------------------------------------------------------------------------
	
	const string MARKET_TYPE::STOCK_CN("stock_cn"); //�й�A��
	const string MARKET_TYPE::STOCK_CN_B("stock_cn_b"); //�й�B��
	const string MARKET_TYPE::STOCK_CN_D("stock_cn_d"); //�й�D�� ����ͨ
	const string MARKET_TYPE::STOCK_HK("stock_hk"); //�۹�
	const string MARKET_TYPE::STOCK_US("stock_us"); //����
	const string MARKET_TYPE::FUTURE_CN("future_cn"); //�����ڻ�
	const string MARKET_TYPE::OPTION_CN("option_cn"); //������Ȩ
	const string MARKET_TYPE::STOCKOPTIN_CN("stockoption_cn"); //������Ȩ
	const string MARKET_TYPE::CRYPTOCURRENCY("cryptocurrency"); //���ܻ���(��������)
	const string MARKET_TYPE::INDEX_CN("index_cn"); //�й�ָ��
	const string MARKET_TYPE::FUND_CN("fund_cn"); //�й�����
	const string MARKET_TYPE::BOND_CN("bond_cn"); //�й�ծȯ

	//--------------------------------------------------------------------------------------

	const string ORDER_MODEL::LIMIT("LIMIT");		//�޼�
	const string ORDER_MODEL::ANY("ANY");		//�м�(otg����)
	const string ORDER_MODEL::MARKET("MARKET");		//�мۣ��ڻز������¸�bar�Ŀ��̼����룬ʵ�̾����嵵ʣ�����ųɽ���
	const string ORDER_MODEL::CLOSE("CLOSE");		//��ǰbar�����̼�����
	const string ORDER_MODEL::NEXT_OPEN("NEXT_OPEN");	//�¸�bar�Ŀ��̼�����
	const string ORDER_MODEL::STRICT_("STRICT");	//�ϸ�ģʽ�����Ƽ������޻ز�����ã�
	const string ORDER_MODEL::BEST("BEST");		//�н��� ���ųɽ�ʣ��ת��

	//--------------------------------------------------------------------------------------

	int ORDER_DIRECTION::BUY(1);			//��Ʊ����
	int ORDER_DIRECTION::SELL(-1);			//��Ʊ����
	int ORDER_DIRECTION::BUY_OPEN(2);		//�ڻ� �࿪
	int ORDER_DIRECTION::BUY_CLOSE(3);		//�ڻ� ��ƽ
	int ORDER_DIRECTION::SELL_OPEN(-2);		//�ڻ� �տ�
	int ORDER_DIRECTION::SELL_CLOSE(-3);	//�ڻ���ƽ
	int ORDER_DIRECTION::SELL_CLOSETODAY(-4);
	int ORDER_DIRECTION::BUY_CLOSETODAY(4);

	int ORDER_DIRECTION::ASK(0);			//�깺
	int ORDER_DIRECTION::XDXR(5);
	int ORDER_DIRECTION::OTHER(6);
	
	//--------------------------------------------------------------------------------------

	const string ORDER_STATUS::NEW("new");
	const string ORDER_STATUS::SUCCESS_ALL("success_all");
	const string ORDER_STATUS::SUCCESS_PART("success_part");
	const string ORDER_STATUS::QUEUED("queued"); //���ڱ�ʾ��order_queue�� ʵ�ʱ�����˼�Ƕ������ ���ɽ� == ALIVED
	const string ORDER_STATUS::CANCEL_ALL("cancel_all");
	const string ORDER_STATUS::CANCEL_PART("cancel_part");
	const string ORDER_STATUS::SETTLED("settled");
	const string ORDER_STATUS::FAILED("failed");
	const string ORDER_STATUS::NEXT("next"); //��ǰbarδ�ɽ�����һ��bar�����ȴ�

	//--------------------------------------------------------------------------------------

	const string TIME_CONDITION::IOC("IOC");//������ɣ�������
	const string TIME_CONDITION::GFS("GFS");//������Ч
	const string TIME_CONDITION::GFD("GFD");//������Ч
	const string TIME_CONDITION::GTD("GTD");//ָ������ǰ��Ч
	const string TIME_CONDITION::GTC("GTC");//����ǰ��Ч
	const string TIME_CONDITION::GFA("GFA");//���Ͼ�����Ч

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
		os << "�ڻ�: " << ft.m_name << endl;
		os << "��Լ����: " << ft.m_unit_table << endl;
		os << "ÿ�����: " << ft.m_price_tick << endl;
		os << "��ͷ���ֱ�֤��ϵ��: " << ft.m_buy_frozen_coeff << endl;
		os << "��ͷ���ֱ�֤��ϵ��: " << ft.m_sell_frozen_coeff << endl;
		os << "������ID: " << ft.m_exchange << endl;
		os << "����������������ϵ��: " << ft.m_commission_coeff_peramount << endl;
		os << "�����������������ϵ��: " << ft.m_commission_coeff_pervol << endl;
		os << "�����������ƽ��������ϵ��: " << ft.m_commission_coeff_today_peramount << endl;
		os << "�����������ƽ��������ϵ��: " << ft.m_commission_coeff_today_pervol << endl;
		//...
		return os; //return osֻ�Ǳ�֤����cout << obj1 << obj2 ��ǰ���os<<"name: "<< endlÿ��ϵ
	}
}


