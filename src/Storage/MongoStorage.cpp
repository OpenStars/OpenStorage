#include "Storage/MongoStorage.h"
#include <Poco/MongoDB/Database.h>
#include <Poco/MongoDB/Document.h>
#include <Poco/Exception.h>
#include <iostream>

namespace openstars
{
    namespace storage
    {

        MongoStorage::MongoStorage(const std::string &strServerIP, int nPort)
            : _connection(strServerIP, nPort) {}

        MongoStorage::~MongoStorage() {}

        int32_t MongoStorage::_put(const void *inKeyData, const int &keyLen, const void *inData, const int &datalen)
        {
            try
            {
                Poco::MongoDB::Database db("storage_db");
                auto insertRequest = db.createInsertRequest("keyValueCollection");

                Poco::MongoDB::Document::Ptr doc = new Poco::MongoDB::Document();

                std::string key(static_cast<const char *>(inKeyData), keyLen);
                std::string value(static_cast<const char *>(inData), datalen);

                doc->add("key", key);
                doc->add("value", value);
                insertRequest->documents().push_back(doc);
                _connection.sendRequest(*insertRequest);
                return 0;
            }
            catch (const Poco::Exception &ex)
            {
                std::cerr << "Error in _put: " << ex.displayText() << std::endl;
                return -1;
            }
        }

        int32_t MongoStorage::_get(VType &_return, const KType &key) const
        {
            try
            {
                Poco::MongoDB::Database db("storage_db");
                auto queryRequest = db.createQueryRequest("keyValueCollection");

                Poco::MongoDB::Document::Ptr selector = new Poco::MongoDB::Document();
                selector->add("key", key);

                queryRequest->selector() = *selector;

                Poco::MongoDB::ResponseMessage response;

                // Ensure the connection object is non-const
                const_cast<Poco::MongoDB::Connection &>(_connection).sendRequest(*queryRequest, response);

                if (!response.documents().empty())
                {
                    auto result = response.documents()[0];
                    _return = result->get<std::string>("value");
                    return 0;
                }
                return -1; // Key not found
            }
            catch (const Poco::Exception &ex)
            {
                std::cerr << "Error in _get: " << ex.displayText() << std::endl;
                return -1;
            }
        }

        int32_t MongoStorage::_get(const void *inKeyData, const int &keyLen, void *outData, const int &datalen) const
        {
            try
            {
                VType value;
                KType key(static_cast<const char *>(inKeyData), keyLen);
                if (_get(value, key) == 0)
                {
                    std::memcpy(outData, value.data(), std::min(static_cast<int>(value.size()), datalen));
                    return 0;
                }
                return -1; // Key not found
            }
            catch (const Poco::Exception &ex)
            {
                std::cerr << "Error in _get: " << ex.displayText() << std::endl;
                return -1;
            }
        }

        int32_t MongoStorage::_multiGet(KVMap &_return, const KList &keys) const
        {
            try
            {
                Poco::MongoDB::Database db("storage_db");
                auto queryRequest = db.createQueryRequest("keyValueCollection");

                // Construct a query to match multiple keys using the $in operator
                Poco::MongoDB::Document::Ptr selector = new Poco::MongoDB::Document();
                Poco::MongoDB::Document::Ptr keyArray = new Poco::MongoDB::Document();

                // Populate the array with keys as a BSON document
                int index = 0;
                for (const auto &key : keys)
                {
                    keyArray->add(std::to_string(index++), key);
                }

                // Add the $in operator to the selector
                selector->add("$in", keyArray);
                queryRequest->selector().add("key", *selector);

                Poco::MongoDB::ResponseMessage response;

                // Send the query request
                const_cast<Poco::MongoDB::Connection &>(_connection).sendRequest(*queryRequest, response);

                // Process the response
                for (const auto &doc : response.documents())
                {
                    std::string key = doc->get<std::string>("key");
                    std::string value = doc->get<std::string>("value");
                    _return[key] = value;
                }
                return 0;
            }
            catch (const Poco::Exception &ex)
            {
                std::cerr << "Error in _multiGet: " << ex.displayText() << std::endl;
                return -1;
            }
        }

        int32_t MongoStorage::_multiPut(const AbstractKVStorage::KVMap &keyvals)
        {
            try
            {
                Poco::MongoDB::Database db("storage_db");
                auto insertRequest = db.createInsertRequest("keyValueCollection");

                for (const auto &[key, value] : keyvals)
                {
                    Poco::MongoDB::Document::Ptr doc = new Poco::MongoDB::Document();
                    doc->add("key", key);
                    doc->add("value", value);
                    insertRequest->documents().push_back(doc);
                }

                // Use _connection to send the insert request
                _connection.sendRequest(*insertRequest);

                return 0;
            }
            catch (const Poco::Exception &ex)
            {
                std::cerr << "Error in _multiPut: " << ex.displayText() << std::endl;
                return -1;
            }
        }

        int32_t MongoStorage::_remove(const KType &key)
        {
            try
            {
                Poco::MongoDB::Database db("storage_db");
                auto deleteRequest = db.createDeleteRequest("keyValueCollection");

                // Construct the query to match the key
                Poco::MongoDB::Document::Ptr query = new Poco::MongoDB::Document();
                query->add("key", key);

                deleteRequest->selector() = *query;

                // Use _connection to send the delete request
                _connection.sendRequest(*deleteRequest);

                return 0;
            }
            catch (const Poco::Exception &ex)
            {
                std::cerr << "Error in _remove: " << ex.displayText() << std::endl;
                return -1;
            }
        }

        void MongoStorage::changeHostPort(const std::string &strServerIP, int nPort)
        {
            _connection.connect(strServerIP, nPort);
        }

        void MongoStorage::loadEndpointsFromZK(const std::string &zkServer, const std::string &zkBasePath)
        {
            // Placeholder for Zookeeper integration
        }

        int32_t MongoStorage::put(const KType &key, const VType &data)
        {
            return _put(key.data(), key.size(), data.data(), data.size());
        }

        int32_t MongoStorage::update(const KType &key, const VType &data)
        {
            return _put(key.data(), key.size(), data.data(), data.size());
        }

        int32_t MongoStorage::add(const KType &key, const VType &data)
        {
            VType existing;
            if (_get(existing, key) == 0)
            {
                return -1; // Key already exists
            }
            return _put(key.data(), key.size(), data.data(), data.size());
        }

    }
}
