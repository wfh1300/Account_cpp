#pragma once
#include <string>
#include <map>
using namespace std;
namespace rt {
	class EXCHANGE_CODE {
	public:
		EXCHANGE_CODE();
		
		string exchange(const string& instrument_code/*��Լ����*/) const;
	private:
		/*static*/ map<string, string> m_table;
	};
}

