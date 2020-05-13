//2020/05/06
//wfh1300
//能用hku::Paramter就不要用MapAny;

#pragma once
#include <hikyuu/utilities/Null.h>
#include <string>
#include <map>
#include <boost/any.hpp>
using namespace std;

class MapAny {
public:
	MapAny() {}
	MapAny(const MapAny&);
	MapAny& operator=(const MapAny&);

	//如果想要value时boost::any,就不能实现下面的功能,因为boost::any any;any.type() == typeid(xx)需要太多判断
	//friend ostream& operator<<(ostream& os, const MapAny& ma);

	/** 是否存在指定名称的参数 */
	//头文件定义函数，编译器自动认为是inline, 
	//noexcept标记，该关键字告诉编译器，函数中不会发生异常,这有利于编译器对程序做更多的优化。
	bool have(const string& name) const noexcept {
		return m_params.count(name) == 0 ? false : true;
	}


	template<typename ValueType>
	void set(const string& key, const ValueType& value);

	template<typename ValueType>
	ValueType get(const string& key) const;

private:
	map<string, boost::any> m_params;
};

template<typename ValueType>
void MapAny::set(const string& key, const ValueType& value) {
	if (!have(key)) {
		m_params[key] = value;
		return;
	}
	
	// 若原来的key已经有value，且 新的value和老的value类型一致，则更新该key
	if (m_params[key].type() != typeid(ValueType)) {
		throw logic_error("Mismatching type!" + key);
	}
	m_params[key] = value;
}

template<typename ValueType>
ValueType MapAny::get(const string& key) const {
	auto iter = m_params.find(key);
	if (iter == m_params.end()) {
		//throw out_of_range("out_of_range in Map_Any::get : " + key);
		return hku::Null<ValueType>();
	}
	return boost::any_cast<ValueType>(iter->second);
}