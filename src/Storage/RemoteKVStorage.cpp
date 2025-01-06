/* 
 * File:   RemoteKVStorage.cpp
 * Author: kienpt
 * 
 * Created on September 16, 2010, 8:34 AM
 */

#include "Storage/RemoteKVStorage.h"
#include "KVDataService.h"
#include "thriftutil/TClient.h"
#include "thriftutil/ClientManagerT.h"

using namespace std;
using namespace kv;
typedef TClient <KVDataServiceClient> TClientType;

#include <iostream>
using namespace openstars::storage;

typedef ClientWrapperT<TClientType> ClientWrapper;

RemoteKVStorage::RemoteKVStorage(const std::string& strServerIP, int nPort)
:_endpointManager( Endpoint(strServerIP, nPort, Endpoint::EThriftBinary ) , Endpoint::EThriftBinary ) {
}

void RemoteKVStorage::changeHostPort(const std::string& strServerIP, int nPort){
    _endpointManager.setDefaultEndpoint( Endpoint(strServerIP, nPort, Endpoint::EThriftBinary ) );
}


int32_t RemoteKVStorage::_put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) {
    std::string key((const char*) inKeyData, keyLen);
    std::string data((const char*) inData, datalen);

    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;
    
    ClientWrapper aClient(dbHost, dbPort);
    try {
        if (!aClient->sureOpen())
            return -1;
        return aClient->put(key, data);
    } catch (...) {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
            return aClient->put(key, data);
        } catch (...) {
        }
    }
    return -1;
}

int32_t RemoteKVStorage::_get(VType &_return, const KType &key) const {
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;

    ClientWrapper aClient(dbHost, dbPort);
    try {
        if (!aClient->sureOpen())
            return -1;
        aClient->get(_return, key);
    } catch (...) {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
            aClient->get(_return, key);

        } catch (...) {
        }
    }
    if (_return.length() == 0)
        return -1;
    else return 0;

    return -1;
}

int32_t RemoteKVStorage::_get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const {
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;

    ClientWrapper aClient(dbHost, dbPort);

    string _returnValue, key;

    key = std::string((const char*) inKeyData, keyLen);

    try {
        if (!aClient->sureOpen())
            return -1;
        aClient->get(_returnValue, key);
    } catch (...) {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
            aClient->get(_returnValue, key);

        } catch (...) {
        }
    }
    if (_returnValue.length() == 0)
        return -1;
    else if (_returnValue.length() > datalen) {
        _returnValue = _returnValue.substr(0, datalen);
    }
    //outData = &_returnValue;
    memcpy(outData, _returnValue.data(), _returnValue.length());

    return 0;
}

int32_t RemoteKVStorage::_multiGet(KVMap &_return, const KList &keys) const {
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;

    ClientWrapper aClient(dbHost, dbPort);

    try {
        if (!aClient->sureOpen())
            return -1;
        aClient->multiGetM(_return, keys);
        return 0;
    } catch (...) {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
            aClient->multiGetM(_return, keys);
            return 0;

        } catch (...) {
            return -1;
        }
    }

    return 0;
}

int32_t RemoteKVStorage::_multiPut(const AbstractKVStorage::KVMap& keyvals)
{
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;

    ClientWrapper aClient(dbHost, dbPort);

    try {
        if (!aClient->sureOpen())
            return -1;
        return aClient->multiPutM(keyvals);
    } catch (...) {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
            return aClient->multiPutM(keyvals);

        } catch (...) {
            return -1;
        }
    }

    return 0;
}// should override for some remote KVStorage
//

int32_t RemoteKVStorage::_remove(const KType &key) 
{
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;

    ClientWrapper aClient(dbHost, dbPort);

    try {
        if (!aClient->sureOpen())
            return -1;
        return aClient->remove(key);
    }
    catch (...) 
    {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
		
	    return aClient->remove(key);

        } catch (...) {
            return -1;
        }
    }
    
    return 0;
}


RemoteKVStorage::~RemoteKVStorage() 
{
}

/**
 * Load endpoint host:port from zookeeper
 * @param zkServer
 * @param zkBasePath
 */
void RemoteKVStorage::loadEndpointsFromZK(const std::string& zkServer, const std::string& zkBasePath)
{
    this->_endpointManager.loadEndpoint(zkServer, zkBasePath);
}

/*
 * of date value of existing key, error if it is not existed
 */
int32_t RemoteKVStorage::update(const KType &key, const VType &data)
{
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;

    ClientWrapper aClient(dbHost, dbPort);

    try {
        if (!aClient->sureOpen())
            return -1;
        return aClient->update(key, data);
    }
    catch (...) 
    {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
		
	    return aClient->update(key, data);

        } catch (...) {
            return -1;
        }
    }
    
    return 0;
    
}

/*
 * add new key-value pair, error if it is already existed
 */
int32_t RemoteKVStorage::add(const KType &key, const VType &data)
{
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;

    ClientWrapper aClient(dbHost, dbPort);

    try {
        if (!aClient->sureOpen())
            return -1;
        return aClient->add(key, data);
    }
    catch (...) 
    {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
		
	    return aClient->add(key,data);

        } catch (...) {
            return -1;
        }
    }
    
    return 0;
    
}

int32_t RemoteKVStorage::put(const KType &key, const VType &data)
{
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;

    ClientWrapper aClient(dbHost, dbPort);

    try {
        if (!aClient->sureOpen())
            return -1;
        return aClient->put(key, data);
    }
    catch (...) 
    {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
		
	    return aClient->put(key,data);

        } catch (...) {
            return -1;
        }
    }
    
    return 0;    
}
