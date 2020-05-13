#pragma once
#include "Parameter_rt.h"
#include <map>
#include <string>
#include <memory>
#include <vector>
using namespace std;
typedef vector<string> str_list;
namespace rt {

	class RT_API MARKET_PRESET {//使用MARKET_PRESET没必要再shared_ptr<MARKET_PRESET>，因为成员已经是指针了。
	public:
		MARKET_PRESET();
		str_list code_list();
		str_list exchange_list(); //看看有没有更好的实现方法？
		//TODO: 补充MARKET_PRESET的其它方法

		str_list get_exchangecode(const string& exchange);
		shared_ptr<rt::Future_Type> get_code(string code);

		string get_exchange(string code);

		double get_commission_coeff(string code);
		double get_commission_today_coeff(string code);


	private:
		typedef shared_ptr<rt::Future_Type> pFuture_Type;
		map<string, pFuture_Type> m_table;
	};

}