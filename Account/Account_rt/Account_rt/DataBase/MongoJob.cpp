#include "MongoJob.h"
#include "../Position_rt.h"
#include "../utilities/JsonJob.h"
namespace rt {

    mongocxx::instance MongoJob::m_inst{};

    MongoJob::MongoJob(const string& db_name) {
        m_uri = mongocxx::uri("mongodb://localhost:27017");
        m_client = mongocxx::client{ m_uri };
        m_db = m_client[db_name];
        //m_coll = m_db["test"];

    }

    void MongoJob::save_json(const string& collection_name, const string& message) {
        mongocxx::collection coll = m_db[collection_name];
        bsoncxx::document::value doc_value = bsoncxx::from_json(message);
        //��������
        coll.insert_one(doc_value.view());//return type: bsoncxx::stdx::optional<mongocxx::result::insert_one>
    //}
    }

    string MongoJob::find_json(const string& collection, const map<string, string>& condition) {
        mongocxx::collection coll = m_db[collection];
        //������Ҫ��auto
        auto tmp = document{};
        //���ﲻ�ֿܷ�д��
        //tmp << iter->first;
        //tmp << iter->second;
        //��������д tmp << iter->first << iter->second;
        for (auto iter = condition.begin(); iter != condition.end(); ++iter) {
            tmp << iter->first << iter->second;
        }
        bsoncxx::document::view_or_value cond = tmp << finalize;

        bsoncxx::stdx::optional<bsoncxx::document::value> result = coll.find_one(cond);
        if (result) {
            return bsoncxx::to_json(*result);
        }
        else {
            //HKU_WARN("Account not found!");
            return "";
        }
    }

    void MongoJob::update_json(const string& collection, const map<string, string>& condition,
        const string& message) {
        mongocxx::collection coll = m_db[collection];

        //"$set" << open_document��ʡ����
        auto tmp = document{};
        for (auto iter = condition.begin(); iter != condition.end(); ++iter) {
            tmp << iter->first << iter->second;
        }
        bsoncxx::document::view_or_value cond = tmp << finalize;
        //���document{} << "$set" << bsoncxx::from_json(message) << finalize
        //Ҳ��bsoncxx::document::view_or_value���͵�
        coll.update_one(cond, document{} << "$set" << bsoncxx::from_json(message) << finalize);

    }
    /*
    void MongoJob::save_position(const string& collection_name, const string& message) {
        mongocxx::collection coll = m_db[collection_name];
        //auto isExist = coll.find_one(document{} << "position_id" << message->get<string>("position_id") << finalize);
        //if (isExist) {
        //}
        //else {
        //TODO ��ֵ�ж��Լ�update
            bsoncxx::document::value doc_value = bsoncxx::from_json(message);
            //��������
            coll.insert_one(doc_value.view());//return type: bsoncxx::stdx::optional<mongocxx::result::insert_one>
        //}
    }

    string MongoJob::find_account(const string& collection, const string& account_cookie, const string& password) {
        mongocxx::collection coll = m_db[collection];
        //������Ҫ��auto
        bsoncxx::stdx::optional<bsoncxx::document::value> result = coll.find_one(document{} <<
            "account_cookie" << account_cookie <<
            "password" << password << finalize);
        if (result) {
            return bsoncxx::to_json(*result);
        }
        else {
            HKU_WARN("Account not found!");
            return "";
        }
    }

    void MongoJob::update_account(const string& collection, const string& account_cookie, const string& password,
        const string& message) {
        mongocxx::collection coll = m_db[collection];

        //"$set" << open_document��ʡ����
        coll.update_one(document{} <<
            "account_cookie" << account_cookie <<
            "password" << password << finalize,
            document{} << "$set" << bsoncxx::from_json(message)
            << finalize);
        
    }
    */

}