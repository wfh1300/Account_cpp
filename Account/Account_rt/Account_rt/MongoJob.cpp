#include "MongoJob.h"
#include "Position_rt.h"
namespace rt {

    mongocxx::instance MongoJob::m_inst{};

    MongoJob::MongoJob(const string& db_name) {
        m_uri = mongocxx::uri("mongodb://localhost:27017");
        m_client = mongocxx::client{ m_uri };
        m_db = m_client[db_name];
        //m_coll = m_db["test"];

    }

    void MongoJob::save_position(const string& collection_name, const string& message) {
        mongocxx::collection coll = m_db[collection_name];
        //auto isExist = coll.find_one(document{} << "position_id" << message->get<string>("position_id") << finalize);
        //if (isExist) {
        //}
        //else {
        //TODO 空值判断以及update
            bsoncxx::document::value doc_value = bsoncxx::from_json(message);
            //插入数据
            coll.insert_one(doc_value.view());//return type: bsoncxx::stdx::optional<mongocxx::result::insert_one>
        //}
    }
}