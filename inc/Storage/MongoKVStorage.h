/* 
 * File:   MongoKVStorage.h
 * Author: OpenAI
 *
 * Created on January 15, 2025
 */

#ifndef MONGOKVSTORAGE_H
#define MONGOKVSTORAGE_H

#include "Storage/AbstractKVStorage.h"
#include <Poco/MongoDB/Database.h>
#include <Poco/MongoDB/Document.h>
#include <Poco/MongoDB/Connection.h>
#include <string>
#include <memory>

int insertDocument(Poco::MongoDB::Connection connection, Poco::MongoDB::Database db, Poco::MongoDB::Document::Ptr doc);
int updateDocument(Poco::MongoDB::Connection connection, Poco::MongoDB::Database db, Poco::MongoDB::Document::Ptr doc);
Poco::MongoDB::Document::Ptr getDocumentByKey(Poco::MongoDB::Connection connection, Poco::MongoDB::Database db, const std::string &key, const std::string &value);
int deleteDocumentByKey(Poco::MongoDB::Connection connection, Poco::MongoDB::Database db, const std::string &key, const std::string &value);


namespace openstars { namespace storage {

class MongoKVStorage : public openstars::storage::AbstractKVStorage {
public:
    MongoKVStorage(const std::string& host, int port, const std::string& dbName, const std::string& collectionName);

    virtual ~MongoKVStorage();

protected:
    virtual int32_t _put(const void* inKeyData, const int& keyLen, const void* inData, const int& dataLen) override;
    virtual int32_t _get(VType &_return, const KType &key) const override;
    virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& dataLen) const override;
    virtual int32_t _multiGet(KVMap &_return, const KList &keys) const override;
    virtual int32_t _remove(const KType &key) override;

public:
    void changeCollection(const std::string& collectionName);

private:
    Poco::MongoDB::Connection _connection;
    std::string _dbName;
    std::string _collectionName;
};

} }

#endif /* MONGOKVSTORAGE_H */
