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
}
