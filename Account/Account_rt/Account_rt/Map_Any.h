//2020/05/06
//wfh1300
//����hku::Paramter�Ͳ�Ҫ��MapAny;

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

	//�����Ҫvalueʱboost::any,�Ͳ���ʵ������Ĺ���,��Ϊboost::any any;any.type() == typeid(xx)��Ҫ̫���ж�
	//friend ostream& operator<<(ostream& os, const MapAny& ma);

	/** �Ƿ����ָ�����ƵĲ��� */
	//ͷ�ļ����庯�����������Զ���Ϊ��inline, 
	//noexcept��ǣ��ùؼ��ָ��߱������������в��ᷢ���쳣,�������ڱ������Գ�����������Ż���
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
	
	// ��ԭ����key�Ѿ���value���� �µ�value���ϵ�value����һ�£�����¸�key
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