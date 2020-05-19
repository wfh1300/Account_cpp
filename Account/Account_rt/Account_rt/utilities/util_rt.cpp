#include "util_rt.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
namespace rt {
	
	string generate_random_name(const string& topic, size_t lens/* = 8*/) {
		//.h size_t lens = 8; .cpp size_t lens 不能再写8，否则重复定义
		//char buffer[62]; 算了不用这个数据结构了。
		string buffer;
		for (char i = 'A'; i <= 'Z'; ++i) {
			buffer += i;
		}
		for (char i = 'a'; i <= 'z'; ++i) {
			buffer += i;
		}
		for (char i = '0'; i <= '9'; ++i) {
			buffer += i;
		}

		srand((int)time(0));
		string result;
		for (size_t i = 0; i < lens; ++i) {
			result += buffer[rand() % 62];
		}

		return fmt::format("{}_{}", topic, result);
	}

	string generate_uuid_v4() {
		boost::uuids::random_generator uuid_v4;
		return boost::uuids::to_string(uuid_v4());
	}

	string parse_toward2direction(const int& towards) {
		if (towards == 1 || towards == 2 || towards == 3) {
			return "BUY";
		}
		else if (towards == -1 || towards == -2 || towards == -3) {
			return "SELL";
		}
		else {
			throw runtime_error("unknown towars");
		}
	}
	string parse_toward2offset(const int& towards) {
		if (towards == 2 || towards == -2) {
			return "OPEN";
		}
		else if (towards == 3 || towards == -3) {
			return "CLOSE";
		}
		else {
			throw runtime_error("unknown towards");
		}
	}

	//hku::Datetime curr_datetime(const string& interval, const string& interval2) {
	//	string result;
	//	struct tm t;
	//	time_t now;
	//	time(&now);
	//	localtime_s(&t, &now);
	//	//result += to_string(t.tm_year + 1900) + interval + to_string(t.tm_mon + 1)
	//	//	+ interval + to_string(t.tm_mday) + " " + to_string(t.tm_hour) + interval2 + 
	//	//	to_string(t.tm_min) + interval2 + to_string(t.tm_sec);
	//	//now 获取不了毫秒
	//	hku::Datetime(t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, 
	//		t.tm_min, t.tm_sec, 0, 0);
	//}

	int current_year() {
		struct tm t; //存储当前时间的数据结构
		time_t now;  
		time(&now);  //获取当前时间
		localtime_s(&t, &now); //&t out ,&now in
		return t.tm_year + 1900;
	}

	int current_month() {
		struct tm t;
		time_t now;
		time(&now);
		localtime_s(&t, &now);
		return t.tm_mon + 1;
	}

	int current_weekday() {
		struct tm t;
		time_t now;
		time(&now);
		localtime_s(&t, &now);
		return t.tm_wday;
	}

	int current_day() {
		struct tm t;
		time_t now;
		time(&now);
		localtime_s(&t, &now);
		return t.tm_mday; //yday 指的是一天中的第几天，mday指的是月份中的第几天
	}

	int current_hour() {
		struct tm t;
		time_t now;
		time(&now);
		localtime_s(&t, &now);
		return t.tm_hour; 
	}

	int current_min() {
		struct tm t;
		time_t now;
		time(&now);
		localtime_s(&t, &now);
		return t.tm_min;
	}

	int current_sec() {
		struct tm t;
		time_t now;
		time(&now);
		localtime_s(&t, &now);
		return t.tm_sec;
	}
}
