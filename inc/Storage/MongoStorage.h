/*
 * File:   MongoStorage.h
 * Author: kienpt
 *
 * Created on September 16, 2010, 8:34 AM
 */

#ifndef CMONGOSTORAGE_H
#define CMONGOSTORAGE_H

#include "Storage/AbstractKVStorage.h"
#include <string>
#include "EndpointManager.h"
#include <Poco/MongoDB/Connection.h>

// Todo: Replace with MongoDB-based storage backend.
namespace openstars
{
    namespace storage
    {

        class MongoStorage : public openstars::storage::AbstractKVStorage
        {
        public:
            // MongoStorage();
            MongoStorage(const std::string &strServerIP, int nPort);

        protected:
            virtual int32_t _put(const void *inKeyData, const int &keyLen, const void *inData, const int &datalen);
            // should be overridden

            virtual int32_t _get(VType &_return, const KType &key) const;
            virtual int32_t _get(const void *inKeyData, const int &keyLen, void *outData, const int &datalen) const;
            virtual int32_t _multiGet(KVMap &_return, const KList &keys) const;

            int32_t _multiPut(const AbstractKVStorage::KVMap &keyvals);

            int32_t _remove(const KType &key);

        public:
            virtual ~MongoStorage();

        public:
            int32_t put(const KType &key, const VType &data);

            /*
             * Update the value of an existing key, error if it does not exist.
             */
            virtual int32_t update(const KType &key, const VType &data);

            /*
             * Add a new key-value pair, error if it already exists.
             */
            virtual int32_t add(const KType &key, const VType &data);

        public:
            void changeHostPort(const std::string &strServerIP, int nPort);
            void loadEndpointsFromZK(const std::string &zkServer, const std::string &zkBasePath);

        private:
            MongoStorage(const MongoStorage &orig);

            Poco::MongoDB::Connection _connection;
            EndpointManager _endpointManager;
        };

    }
}

#endif /* CMONGOSTORAGE_H */
