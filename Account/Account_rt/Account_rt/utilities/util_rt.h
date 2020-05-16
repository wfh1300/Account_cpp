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

	//Position��ʹ����uuid
	string generate_uuid_v4();

	//���º���û����ô�
	//hku::Datetime curr_datetime(const string& interval = "-", const string& interval2 = ":");
	int current_year();
	int current_month();
	int current_weekday(); //���ڼ�
	int current_day();
	int current_hour();
	int current_min();
	int current_sec();
}
