#include "JsonJob.h"
namespace rt {
	
	JsonJob::JsonJob() :
		m_document(make_shared<rapidjson::Document>()),
		m_allocator(m_document->GetAllocator()) {
		m_document->Parse("{}"); //这句话必须得有啊，不然会assert异常哦！！,而且Parse("")也会异常
	}
	JsonJob::JsonJob(const string& json) : 
		m_document(make_shared<rapidjson::Document>()), 
		m_allocator(m_document->GetAllocator()) {
		if (json[0] != '{' && json[json.length() - 1] != '}') {
			throw runtime_error("the input is not in json format!");
		}
		m_document->Parse(json.c_str());
	}

	JsonJob::JsonJob(const rapidjson::Value& value) : 
		m_document(make_shared<rapidjson::Document>()), 
		m_allocator(m_document->GetAllocator()) {
		m_document->CopyFrom(value, m_allocator);
	}

	JsonJob& JsonJob::operator=(const JsonJob& rhs) {
		if (this == &rhs) {
			return *this;
		}
		this->m_document = rhs.m_document;
		return *this;
	}

	rapidjson::Value& JsonJob::operator[](const string& key) {
		const char* key_ = key.c_str();
		if (!m_document->HasMember(key_)) {
			throw runtime_error("read only");
			//添加一个空的Value，并返回，我他吗真是一个天才
			//m_document->AddMember(rapidjson::Value(key_, m_allocator),
				//rapidjson::Value().SetObject(), m_allocator);
		}
		return (*m_document)[key_];
	}

	bool JsonJob::hasMember(const string& key) {
		return m_document->HasMember(key.c_str());
	}
	string JsonJob::jsonstr() {
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		m_document->Accept(writer);
		return buffer.GetString();
	}


	void JsonJob::add_null(const string& key) {
		const char* key_ = key.c_str();
		m_document->AddMember(rapidjson::Value(key_, m_allocator),
			rapidjson::Value(), m_allocator);
	}

	void JsonJob::add_int(const string& key, int value) {
		const char* key_ = key.c_str();
		m_document->AddMember(rapidjson::Value(key_, m_allocator),
			rapidjson::Value(value), m_allocator);
	}
	void JsonJob::add_int64(const string& key, long long value) {
		const char* key_ = key.c_str();
		m_document->AddMember(rapidjson::Value(key_, m_allocator),
			rapidjson::Value(value), m_allocator);
	}
	void JsonJob::add_double(const string& key, double value) {
		const char* key_ = key.c_str();
		m_document->AddMember(rapidjson::Value(key_, m_allocator),
			rapidjson::Value(value), m_allocator); //Value(double, 不能m_allocator吗？)
	}
	void JsonJob::add_bool(const string& key, bool value) {
		const char* key_ = key.c_str();
		m_document->AddMember(rapidjson::Value(key_, m_allocator),
			rapidjson::Value(value), m_allocator);
	}

	void JsonJob::add_string(const string& key, const string& value) {
		//这里的rapidjson::Value(value.c_str(), m_allocator)和上面的不是一个
		const char* key_ = key.c_str();
		m_document->AddMember(rapidjson::Value(key_, m_allocator),
			rapidjson::Value(value.c_str(), m_allocator), m_allocator);
	}

	void JsonJob::add_document(const string& key, const string& value) {
		const char* key_ = key.c_str();
		if (value[0] == '{' && value[value.length() - 1] == '}') {
			rapidjson::Document d;
			d.Parse(value.c_str());
			m_document->AddMember(rapidjson::Value(key_, m_allocator),
				rapidjson::Value(d, m_allocator), m_allocator);
		}
		else {
			throw runtime_error("wrong format of json");
		}
	}

	void JsonJob::add_document(const string& key, rapidjson::Document& value) {
		const char* key_ = key.c_str();
		m_document->AddMember(rapidjson::Value(key_, m_allocator),
			rapidjson::Value(value, m_allocator), m_allocator);
	}

	void JsonJob::add_document(const string& key, const JsonJob& value) {
		const char* key_ = key.c_str();
		m_document->AddMember(rapidjson::Value(key_, m_allocator),
			rapidjson::Value(*value.m_document, m_allocator), m_allocator);
	}

	void JsonJob::add_array(const string& key, rapidjson::Value& arr_value) {
		const char* key_ = key.c_str();
		m_document->AddMember(rapidjson::Value(key_, m_allocator), arr_value, m_allocator);
	}

	rapidjson::Document JsonJob::json2doc(const string& json) {
		if (json[0] != '{' && json[json.length() - 1] != '}') {
			throw runtime_error("the input is not in json format!");
		}
		rapidjson::Document d;
		d.Parse(json.c_str());
		return d;
	}

	//rapidjson::Value get_null_arr() {
	//	rapidjson::Value result(rapidjson::kArrayType);
	//	return result;
	//}

	shared_ptr<rapidjson::Document> JsonJob::get_m_doc() {
		return m_document;
	}

	bool JsonJob::clear() {
		try {
			m_document->RemoveAllMembers();
			return true;
		}
		catch (...) {
			return false;
		}
	}

	rapidjson::Value::MemberIterator JsonJob::begin() {
		return m_document->MemberBegin();
	}

	rapidjson::Value::MemberIterator JsonJob::end() {
		return m_document->MemberEnd();
	}
}