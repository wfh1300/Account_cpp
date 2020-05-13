#pragma once
#include <fmt/format.h>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;
namespace rt {
	string generate_random_name(const string& topic, size_t lens = 8);

	//Position中使用了uuid
	string generate_uuid_v4();
}
