//2020/05/13
//wfh1300
#pragma once
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
namespace rt {

	class JsonJob {
	public:
		JsonJob();
		JsonJob(const string& json);
		JsonJob(const rapidjson::Value& value);

		JsonJob& operator=(const JsonJob& rhs);
		rapidjson::Value& operator[](const string& x); //这个可以返回引用是因为引用的是m_document持久化的

		bool hasMember(const string& key);

		//用模板实现过下列add_xx(),不太好用
		//template<typename ValueType>
		//void set(const string& key, const ValueType& value);
		void add_null(const string& key);
		void add_int(const string& key, int value);
		void add_int64(const string& key, long long value);
		void add_double(const string& key, double value);
		void add_bool(const string& key, bool value);//都命名为add时，bool会吞噬int/double等类型的重载，
		void add_string(const string& key, const string& value);
		void add_document(const string& key, const string& value);
		void add_document(const string& key, rapidjson::Document& value);

		void add_array(const string& key, rapidjson::Value& arr_value);

		//template<typename ValueType>
		//void add_array(const string& key, vector<ValueType>& value);
		//rapidjson::Value get_null_arr();
		shared_ptr<rapidjson::Document> get_m_doc();
		/*在外部创建array
		 *格式：
		 *rapidjson::Value arr(rapidjson::kArrayType);
		 *arr.PushBack(xxx, obj.get_m_doc()->GetAllocator());
		*/
		//后续add(const string& key, const Order_rt& value);
		//后续add(const string& key, const Position_rt& value);

		//这个返回值不能用引用！！，因为是栈上的值
		//一般情况下不要用
		static rapidjson::Document json2doc(const string& json);
		string jsonstr();
	private:
		//改为shared_ptr类型，可以拷贝，和导出了
		shared_ptr<rapidjson::Document> m_document;
		rapidjson::Document::AllocatorType& m_allocator;
	};

	//template<typename ValueType>
	//void JsonJob::add_array(const string& key, vector<ValueType>& value) {
	//	const char* key_ = key.c_str();
	//	rapidjson::Value arr(rapidjson::kArrayType);
	//	if (typeid(ValueType) == typeid(string)) {
	//		for (auto i: value) {
	//			cout << i << endl;
	//			//arr.PushBack(rapidjson::Value(static_cast<string>(i).c_str(), m_document->GetAllocator()), m_document->GetAllocator());
	//		}
	//	}
	//	else {
	//		for (auto i : value) {
	//			arr.PushBack(i, m_document->GetAllocator());
	//		}
	//	}
	//	m_document->AddMember(rapidjson::Value(key_, m_document->GetAllocator()), arr, m_document->GetAllocator());
	//}
}