/*
 * File:   MongoKVStorage.cpp
 * Author: OpenAI
 *
 * Created on January 15, 2025
 */

#include "Storage/MongoKVStorage.h"
#include <Poco/MongoDB/Database.h>
#include <Poco/MongoDB/Document.h>
#include <Poco/MongoDB/Cursor.h>
#include <Poco/MongoDB/Connection.h>
#include <Poco/Exception.h>
#include <sstream>

using namespace openstars::storage;

MongoKVStorage::MongoKVStorage(const std::string &host, int port, const std::string &dbName, const std::string &collectionName)
    : _dbName(dbName), _collectionName(collectionName)
{
    Poco::MongoDB::Connection conn(host, port);
    _connection = conn;
}

MongoKVStorage::~MongoKVStorage()
{
}

int32_t MongoKVStorage::_put(const void *inKeyData, const int &keyLen, const void *inData, const int &dataLen)
{
    try
    {
        std::string key((const char *)inKeyData, keyLen);
        std::string value((const char *)inData, dataLen);
        Poco::MongoDB::Database db(_dbName);
        Poco::MongoDB::Document::Ptr doc = new Poco::MongoDB::Document();
        doc->add("_id", key);
        doc->add("value", value);
        insertDocument(_connection, db, doc);
        return 0;
    }
    catch (Poco::Exception &ex)
    {
        return -1;
    }
}

int32_t MongoKVStorage::_get(VType &_return, const KType &key) const
{
    Poco::MongoDB::Database db(_dbName);
    std::string ikey;
    std::string ivalue;
    getDocumentByKey(_connection, db, ikey, ivalue);
}

int32_t MongoKVStorage::_get(const void *inKeyData, const int &keyLen, void *outData, const int &dataLen) const
{

    Poco::MongoDB::Database db(_dbName);
    std::string ikey;
    std::string ivalue;
    getDocumentByKey(_connection, db, ikey, ivalue);
}

int32_t MongoKVStorage::_multiGet(KVMap &_return, const KList &keys) const
{
    Poco::MongoDB::Database db(_dbName);
    for (auto key : keys)
    {
        std::string value;
        getDocumentByKey(_connection, db,key, value);
        _return[key] = value;
    }
    return 0;
}

int32_t MongoKVStorage::_remove(const KType &key)
{
    Poco::MongoDB::Database db(_dbName);
    deleteDocumentByKey(_connection, db, "_id", key);
    return 0;
}

void MongoKVStorage::changeCollection(const std::string &collectionName)
{
    _collectionName = collectionName;
}

int insertDocument(Poco::MongoDB::Connection connection, Poco::MongoDB::Database db, Poco::MongoDB::Document::Ptr doc)
{
    auto insertRequest = db.createInsertRequest("kvcollection");
    insertRequest->documents().push_back(doc);
    connection.sendRequest(*insertRequest);
    return 0;
}

int updateDocument(Poco::MongoDB::Connection connection, Poco::MongoDB::Database db, Poco::MongoDB::Document::Ptr doc)
{
    auto updateRequest = db.createUpdateRequest("kvcollection");
    updateRequest->selector().add("name", "John Doe");
    updateRequest->update().add("$set", doc);
    connection.sendRequest(*updateRequest);
    return 0;
}

Poco::MongoDB::Document::Ptr getDocumentByKey(Poco::MongoDB::Connection connection, Poco::MongoDB::Database db, const std::string &key, const std::string &value)
{
    auto queryRequest = db.createQueryRequest("kvcollection");
    queryRequest->selector().add(key, value);

    Poco::MongoDB::ResponseMessage response;
    connection.sendRequest(*queryRequest, response);

    if (!response.documents().empty())
    {
        return response.documents().front();
    }

    return nullptr; // Trả về nullptr nếu không tìm thấy tài liệu
}

int deleteDocumentByKey(Poco::MongoDB::Connection connection, Poco::MongoDB::Database db, const std::string &key, const std::string &value)
{
    auto deleteRequest = db.createDeleteRequest("kvcollection");
    deleteRequest->selector().add(key, value);
    connection.sendRequest(*deleteRequest);
    return 0;
}