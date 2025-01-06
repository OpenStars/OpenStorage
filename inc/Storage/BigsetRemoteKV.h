/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigsetRemoteKV.h
 * Author: trungthanh
 *
 * Created on September 8, 2016, 10:28 AM
 */

#ifndef BIGSETREMOTEKV_H
#define BIGSETREMOTEKV_H
#include "Storage/AbstractKVStorage.h"
#include "EndpointManager.h"

namespace openstars {
    namespace storage {

        class BigsetRemoteKV : public AbstractKVStorage {
        public:
            BigsetRemoteKV(const std::string& strServerIP, int nPort, int64_t rawBigsetID);
            virtual ~BigsetRemoteKV();

        protected:
            virtual int32_t _put( const KType &key, const VType &data);
            virtual int32_t _put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen);

            virtual int32_t _get(VType &_return, const KType &key) const;
            virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const;

            int32_t _multiGet(KVMap &_return, const KList &keys) const;
            int32_t _multiPut(const AbstractKVStorage::KVMap& keyvals);

            int32_t _remove(const KType &key);


        public:
            void changeHostPort(const std::string& strServerIP, int nPort);
            void loadEndpointsFromZK(const std::string& zkServer, const std::string& zkBasePath);
        private:
            BigsetRemoteKV(const BigsetRemoteKV& orig);

            EndpointManager _endpointManager;
            int64_t bigsetRoot; // big set rawID - fastest/most lightweight
            //std::string tableName; //big set name - using String BS

        };

    }
} //Up::Storage

#endif /* BIGSETREMOTEKV_H */

