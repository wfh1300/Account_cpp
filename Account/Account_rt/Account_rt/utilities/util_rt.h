#pragma once
#include <fmt/format.h>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <hikyuu/datetime/Datetime.h>

using namespace std;
namespace rt {
	string generate_random_name(const string& topic, size_t lens = 8);

	//Position中使用了uuid
	string generate_uuid_v4();

	//以下函数没多大用处
	//hku::Datetime curr_datetime(const string& interval = "-", const string& interval2 = ":");
	int current_year();
	int current_month();
	int current_weekday(); //星期几
	int current_day();
	int current_hour();
	int current_min();
	int current_sec();
}
