#include "Market_Preset.h"
//#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <hikyuu/Log.h>
//#include <assert.h>
using namespace std;
namespace rt {

	MARKET_PRESET::MARKET_PRESET() {

		m_table["AG"] = make_shared<rt::Future_Type>("白银", 15, 1.0, 0.06, 0.06, rt::EXCHANGE_ID::SHFE, 5e-05, 0, 5e-05, 0);
		m_table["AL"] = make_shared<rt::Future_Type>("铝", 5, 5.0, 0.07, 0.07, rt::EXCHANGE_ID::SHFE, 0, 3.0, 0, 0.0);
		m_table["AU"] = make_shared<rt::Future_Type>("黄金", 1000, 0.05, 0.05, 0.05, rt::EXCHANGE_ID::SHFE, 0, 10.0, 0, 0.0);
		m_table["BU"] = make_shared<rt::Future_Type>("石油沥青", 10, 2.0, 0.1, 0.1, rt::EXCHANGE_ID::SHFE, 0.0001, 0, 0.0003, 0);
		m_table["CU"] = make_shared<rt::Future_Type>("铜", 5, 10.0, 0.07, 0.07, rt::EXCHANGE_ID::SHFE, 5e-05, 0, 0.0, 0);
		m_table["FU"] = make_shared<rt::Future_Type>("燃料油", 10, 1.0, 0.1, 0.1, rt::EXCHANGE_ID::SHFE, 5e-05, 0, 0.0, 0);
		m_table["HC"] = make_shared<rt::Future_Type>("热轧卷板", 10, 1.0, 0.08, 0.08, rt::EXCHANGE_ID::SHFE, 0.0001, 0, 0.0001, 0);
		m_table["NI"] = make_shared<rt::Future_Type>("镍", 1, 10.0, 0.08, 0.08, rt::EXCHANGE_ID::SHFE, 0, 1.0, 0, 0.0);
		m_table["PB"] = make_shared<rt::Future_Type>("铅", 5, 5.0, 0.08, 0.08, rt::EXCHANGE_ID::SHFE, 4e-05, 0, 0.0, 0);
		m_table["RB"] = make_shared<rt::Future_Type>("螺纹钢", 10, 1.0, 0.09, 0.09, rt::EXCHANGE_ID::SHFE, 0.0001, 0, 0.0001, 0);
		m_table["RU"] = make_shared<rt::Future_Type>("天然橡胶", 10, 5.0, 0.09, 0.09, rt::EXCHANGE_ID::SHFE, 4.5e-05, 0, 4.5e-05, 0);
		m_table["SN"] = make_shared<rt::Future_Type>("锡", 1, 10.0, 0.07, 0.07, rt::EXCHANGE_ID::SHFE, 0, 1.0, 0, 0.0);
		m_table["SP"] = make_shared<rt::Future_Type>("漂针浆", 10, 2.0, 0.07, 0.07, rt::EXCHANGE_ID::SHFE, 5e-05, 0, 0.0, 0);
		m_table["WR"] = make_shared<rt::Future_Type>("线材", 10, 1.0, 0.08, 0.08, rt::EXCHANGE_ID::SHFE, 4e-05, 0, 0.0, 0);
		m_table["ZN"] = make_shared<rt::Future_Type>("锌", 5, 5.0, 0.08, 0.08, rt::EXCHANGE_ID::SHFE, 0, 3.0, 0, 0.0);
		m_table["A"] = make_shared<rt::Future_Type>("黄大豆", 10, 1.0, 0.05, 0.05, rt::EXCHANGE_ID::DCE, 0, 2.0, 0, 2.0);
		m_table["B"] = make_shared<rt::Future_Type>("黄大豆", 10, 1.0, 0.05, 0.05, rt::EXCHANGE_ID::DCE, 0, 1.0, 0, 1.0);
		m_table["BB"] = make_shared<rt::Future_Type>("细木工板", 500, 0.05, 0.2, 0.2, rt::EXCHANGE_ID::DCE, 0.0001, 0, 5e-05, 0);
		m_table["C"] = make_shared<rt::Future_Type>("黄玉米", 10, 1.0, 0.05, 0.05, rt::EXCHANGE_ID::DCE, 0, 1.2, 0, 0.0);
		m_table["CS"] = make_shared<rt::Future_Type>("玉米淀粉", 10, 1.0, 0.05, 0.05, rt::EXCHANGE_ID::DCE, 0, 1.5, 0, 0.0);
		m_table["EG"] = make_shared<rt::Future_Type>("乙二醇", 10, 1.0, 0.06, 0.06, rt::EXCHANGE_ID::DCE, 0, 4.0, 0, 0.0);
		m_table["FB"] = make_shared<rt::Future_Type>("中密度纤维板", 500, 0.05, 0.2, 0.2, rt::EXCHANGE_ID::DCE, 0.0001, 0, 5e-05, 0);
		m_table["I"] = make_shared<rt::Future_Type>("铁矿石", 100, 0.5, 0.08, 0.08, rt::EXCHANGE_ID::DCE, 6e-05, 0, 6e-05, 0);
		m_table["J"] = make_shared<rt::Future_Type>("冶金焦炭", 100, 0.5, 0.08, 0.08, rt::EXCHANGE_ID::DCE, 0.00018, 0, 0.00018, 0);
		m_table["JD"] = make_shared<rt::Future_Type>("鲜鸡蛋", 10, 1.0, 0.07, 0.07, rt::EXCHANGE_ID::DCE, 0.00015, 0, 0.00015, 0);
		m_table["JM"] = make_shared<rt::Future_Type>("焦煤", 60, 0.5, 0.08, 0.08, rt::EXCHANGE_ID::DCE, 0.00018, 0, 0.00018, 0);
		m_table["L"] = make_shared<rt::Future_Type>("线型低密度聚乙烯", 5, 5.0, 0.05, 0.05, rt::EXCHANGE_ID::DCE, 0, 2.0, 0, 0.0);
		m_table["M"] = make_shared<rt::Future_Type>("豆粕", 10, 1.0, 0.05, 0.05, rt::EXCHANGE_ID::DCE, 0, 1.5, 0, 0.0);
		m_table["P"] = make_shared<rt::Future_Type>("棕榈油", 10, 2.0, 0.05, 0.05, rt::EXCHANGE_ID::DCE, 0, 2.5, 0, 0.0);
		m_table["PP"] = make_shared<rt::Future_Type>("聚丙烯", 5, 1.0, 0.05, 0.05, rt::EXCHANGE_ID::DCE, 6e-05, 0, 3e-05, 0);
		m_table["V"] = make_shared<rt::Future_Type>("聚氯乙烯", 5, 5.0, 0.05, 0.05, rt::EXCHANGE_ID::DCE, 0, 2.0, 0, 0.0);
		m_table["Y"] = make_shared<rt::Future_Type>("豆油", 10, 2.0, 0.05, 0.05, rt::EXCHANGE_ID::DCE, 0, 2.5, 0, 0.0);
		m_table["AP"] = make_shared<rt::Future_Type>("鲜苹果", 10, 1.0, 0.08, 0.08, rt::EXCHANGE_ID::CZCE, 0, 5.0, 0, 5.0);
		m_table["CF"] = make_shared<rt::Future_Type>("一号棉花", 5, 5.0, 0.05, 0.05, rt::EXCHANGE_ID::CZCE, 0, 4.3, 0, 0.0);
		m_table["CY"] = make_shared<rt::Future_Type>("棉纱", 5, 5.0, 0.05, 0.05, rt::EXCHANGE_ID::CZCE, 0, 4.0, 0, 0.0);
		m_table["FG"] = make_shared<rt::Future_Type>("玻璃", 20, 1.0, 0.05, 0.05, rt::EXCHANGE_ID::CZCE, 0, 3.0, 0, 6.0);
		m_table["JR"] = make_shared<rt::Future_Type>("粳稻", 20, 1.0, 0.05, 0.05, rt::EXCHANGE_ID::CZCE, 0, 3.0, 0, 3.0);
		m_table["LR"] = make_shared<rt::Future_Type>("晚籼稻", 20, 1.0, 0.05, 0.05, rt::EXCHANGE_ID::CZCE, 0, 3.0, 0, 3.0);
		m_table["MA"] = make_shared<rt::Future_Type>("甲醇MA", 10, 1.0, 0.07, 0.07, rt::EXCHANGE_ID::CZCE, 0, 2.0, 0, 6.0);
		m_table["OI"] = make_shared<rt::Future_Type>("菜籽油", 10, 1.0, 0.05, 0.05, rt::EXCHANGE_ID::CZCE, 0, 2.0, 0, 0.0);
		m_table["PM"] = make_shared<rt::Future_Type>("普通小麦", 50, 1.0, 0.05, 0.05, rt::EXCHANGE_ID::CZCE, 0, 5.0, 0, 5.0);
		m_table["RI"] = make_shared<rt::Future_Type>("早籼", 20, 1.0, 0.05, 0.05, rt::EXCHANGE_ID::CZCE, 0, 2.5, 0, 2.5);
		m_table["RM"] = make_shared<rt::Future_Type>("菜籽粕", 10, 1.0, 0.06, 0.06, rt::EXCHANGE_ID::CZCE, 0, 1.5, 0, 0.0);
		m_table["RS"] = make_shared<rt::Future_Type>("油菜籽", 10, 1.0, 0.2, 0.2, rt::EXCHANGE_ID::CZCE, 0, 2.0, 0, 2.0);
		m_table["SF"] = make_shared<rt::Future_Type>("硅铁", 5, 2.0, 0.07, 0.07, rt::EXCHANGE_ID::CZCE, 0, 3.0, 0, 9.0);
		m_table["SM"] = make_shared<rt::Future_Type>("锰硅", 5, 2.0, 0.07, 0.07, rt::EXCHANGE_ID::CZCE, 0, 3.0, 0, 6.0);
		m_table["SR"] = make_shared<rt::Future_Type>("白砂糖", 10, 1.0, 0.05, 0.05, rt::EXCHANGE_ID::CZCE, 0, 3.0, 0, 0.0);
		m_table["TA"] = make_shared<rt::Future_Type>("精对苯二甲酸", 5, 2.0, 0.06, 0.06, rt::EXCHANGE_ID::CZCE, 0, 3.0, 0, 0.0);
		m_table["WH"] = make_shared<rt::Future_Type>("优质强筋小麦", 20, 1.0, 0.2, 0.2, rt::EXCHANGE_ID::CZCE, 0, 2.5, 0, 0.0);
		m_table["ZC"] = make_shared<rt::Future_Type>("动力煤ZC", 100, 0.2, 0.06, 0.06, rt::EXCHANGE_ID::CZCE, 0, 4.0, 0, 4.0);
		m_table["SC"] = make_shared<rt::Future_Type>("原油", 1000, 0.1, 0.1, 0.1, rt::EXCHANGE_ID::INE, 0, 20.0, 0, 0.0);
		m_table["EB"] = make_shared<rt::Future_Type>("苯乙烯", 5, 1, 0.05, 0.05, rt::EXCHANGE_ID::DCE, 0.0001, 0, 0.0001, 0);
		m_table["RR"] = make_shared<rt::Future_Type>("粳米", 10, 1, 0.05, 0.05, rt::EXCHANGE_ID::DCE, 0.0001, 0, 0.0001, 0);
		m_table["NR"] = make_shared<rt::Future_Type>("20号胶", 10, 5, 0.09, 0.09, rt::EXCHANGE_ID::INE, 0.0001, 0, 0.0001, 0.0);
		m_table["SS"] = make_shared<rt::Future_Type>("不锈钢", 5, 5, 0.08, 0.08, rt::EXCHANGE_ID::SHFE, 0.0001, 0, 0.0001, 0.0);
		m_table["CJ"] = make_shared<rt::Future_Type>("红枣", 5, 5, 0.07, 0.07, rt::EXCHANGE_ID::CZCE, 0, 3, 0, 3);
		m_table["UR"] = make_shared<rt::Future_Type>("尿素", 20, 1, 0.05, 0.05, rt::EXCHANGE_ID::CZCE, 0.0001, 0, 0.0001, 0);
		m_table["IC"] = make_shared<rt::Future_Type>("中证500指数", 200, 0.2, 0.12, 0.12, rt::EXCHANGE_ID::CFFEX, 2.301e-05, 0, 0.00034501, 0);
		m_table["IF"] = make_shared<rt::Future_Type>("沪深300指数", 300, 0.2, 0.1, 0.1, rt::EXCHANGE_ID::CFFEX, 2.301e-05, 0, 0.0001, 0);
		m_table["IH"] = make_shared<rt::Future_Type>("上证50指数", 300, 0.2, 0.05, 0.05, rt::EXCHANGE_ID::CFFEX, 2.301e-05, 0, 0.00034501, 0);
		m_table["TF"] = make_shared<rt::Future_Type>("5年期国债", 10000, 0.005, 0.012, 0.012, rt::EXCHANGE_ID::CFFEX, 0.0001, 0, 0.0001, 0);
		m_table["TS"] = make_shared<rt::Future_Type>("2年期国债", 20000, 0.005, 0.005, 0.005, rt::EXCHANGE_ID::CFFEX, 0.0001, 0, 0.0001, 0);

	}

	str_list MARKET_PRESET::code_list() {
		str_list buffer;
		if (m_table.empty()) {
			return buffer;
		}

		for (auto& iter : m_table) {
			buffer.push_back(iter.first);
		}
		return buffer;
	}


	str_list MARKET_PRESET::exchange_list() {
		str_list result;
		if (m_table.empty()) {
			return result;
		}

		unordered_map<string, int> buffer;
		for (auto& iter : m_table) {
			const string tmp = iter.second->exchange();
			if (!buffer.count(tmp)) {
				buffer[tmp] = 1;
				result.push_back(tmp);
			}
		}
		return result;
	}

	str_list MARKET_PRESET::get_exchangecode(const string& exchange) {
		str_list result;
		// 不用判断exchange的正确性，不对自然返回空vector

		for (auto& iter : m_table) {
			if (iter.second->exchange() == exchange) {
				result.push_back(iter.first);
			}
		}
		return result;
	}

	//有个问题，这里能不能返回shared_ptr<rt::Future_Type>
	//这样方便赋值，不然就操作了 &MARKET_PRESET().get_code(code), 这里额外的取地址
	shared_ptr<rt::Future_Type> MARKET_PRESET::get_code(string code) {
		shared_ptr<rt::Future_Type> result;
		std::transform(code.begin(), code.end(), code.begin(), [](unsigned char c) { return std::toupper(c); });

		//assert(m_table.count(code));
		//当code 为股票代码时，会出现 NULL -> unit_table()错误
		if (m_table.count(code)) {
			result = m_table.find(code)->second;
		}
		else {
			HKU_ERROR("code does not exist!");
		}
		return result;
	}

	string MARKET_PRESET::get_exchange(string code) {
		string result;
		transform(code.begin(), code.end(), code.begin(), [](unsigned char c) {return std::toupper(c); });
		if (m_table.count(code)) {
			result = m_table.find(code)->second->exchange();
		}
		else {
			HKU_ERROR("code does not exist!");
		}
		return result;
	}

	double MARKET_PRESET::get_commission_coeff(string code) {
		double result = -1; //必须初始化，不然cout会报错
		transform(code.begin(), code.end(), code.begin(), [](unsigned char c) {return std::toupper(c); });
		if (m_table.count(code)) {
			double tmp1 = m_table.find(code)->second->commission_coeff_peramount();
			double tmp2 = m_table.find(code)->second->commission_coeff_pervol();
			result = tmp1 > tmp2 ? tmp1 : tmp2;
		}
		else {
			HKU_ERROR("code does not exist!");
		}
		return result;
	}

	double MARKET_PRESET::get_commission_today_coeff(string code) {
		double result = -1;
		transform(code.begin(), code.end(), code.begin(), [](unsigned char c) {return toupper(c); });
		if (m_table.count(code)) {
			double tmp1 = m_table.find(code)->second->commission_coeff_today_peramount();
			double tmp2 = m_table.find(code)->second->commission_coeff_today_pervol();
			result = tmp1 > tmp2 ? tmp1 : tmp2;
		}
		else {
			HKU_ERROR("code does not exist!");
		}
		return result;
	}
}