#pragma once
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
//#include <bsoncxx/json.hpp>
#include <string>

#pragma comment(lib, "mongocxx.lib") // û������᲻���ؾ�̬�⣬��ʹ�����ֶ���lib�ļ�����������
#pragma comment(lib, "bsoncxx.lib")
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using namespace std;
namespace rt {

    class MongoJob {
    public:
        MongoJob(const string& db_name);
        void save_position(const string& collection_name, const string& message);
        ~MongoJob() {}
    private:
        static mongocxx::instance m_inst;
        mongocxx::uri m_uri;
        mongocxx::client m_client;
        mongocxx::database m_db;
    };
}