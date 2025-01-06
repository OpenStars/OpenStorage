/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigsetRemoteKV.cpp
 * Author: trungthanh
 * 
 * Created on September 8, 2016, 10:28 AM
 */

#include "Storage/BigsetRemoteKV.h"
#include "RawBigSetKVService.h"
#include "thriftutil/TClient.h"
#include "thriftutil/ClientManagerT.h"
#include <iostream>


using namespace std;
using namespace bskv;
using namespace openstars::storage;

typedef TClient <bskv::RawBigSetKVServiceClient> TClientType;

typedef ClientWrapperT<TClientType> ClientWrapper;


namespace openstars { namespace storage {
    

BigsetRemoteKV::BigsetRemoteKV(const std::string& strServerIP, int nPort, int64_t rawBigsetID)
:_endpointManager( Endpoint(strServerIP, nPort, Endpoint::EThriftBinary ) , Endpoint::EThriftBinary ) 
,bigsetRoot(rawBigsetID)
{
}

void BigsetRemoteKV::changeHostPort(const std::string& strServerIP, int nPort){
    _endpointManager.setDefaultEndpoint( Endpoint(strServerIP, nPort, Endpoint::EThriftBinary ) );
}    

/**
 * Load endpoint host:port from zookeeper
 * @param zkServer
 * @param zkBasePath
 */
void BigsetRemoteKV::loadEndpointsFromZK(const std::string& zkServer, const std::string& zkBasePath)
{
    this->_endpointManager.loadEndpoint(zkServer, zkBasePath);
}


BigsetRemoteKV::~BigsetRemoteKV() {
}

int32_t BigsetRemoteKV::_put(const KType &key, const VType &data)
{

    if (bigsetRoot <= 0)
        return -2; 
           
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;
    
    bskv::TPutItemResult aPutResult;
    bskv::TItem item;
    item.key.swap(const_cast<std::string&>(key) );
    item.value.swap(const_cast<std::string&>(data));
    
    ClientWrapper aClient(dbHost, dbPort);
    try {
        if (!aClient->sureOpen())
            return -1;
        aClient->bsgPutItem(aPutResult,bigsetRoot, item);
        
        item.key.swap(const_cast<std::string&>(key) );
        item.value.swap(const_cast<std::string&>(data));
        
        return aPutResult.ok ? 0: -1;
    } 
    catch (...) {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
            aClient->bsgPutItem(aPutResult,bigsetRoot, item);
            
            item.key.swap(const_cast<std::string&>(key) );
            item.value.swap(const_cast<std::string&>(data));
            return aPutResult.ok ? 0: -1;
        } 
        catch (...) {
        }
    }
    return -1;    
}

int32_t BigsetRemoteKV::_put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) {
    
    if (bigsetRoot <= 0)
        return -2; 
    
    std::string key((const char*) inKeyData, keyLen);
    std::string data((const char*) inData, datalen);
       
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;
    
    bskv::TPutItemResult aPutResult;
    bskv::TItem item;
    item.key.swap(key);
    item.value.swap(data);
    
    ClientWrapper aClient(dbHost, dbPort);
    try {
        if (!aClient->sureOpen())
            return -1;
        aClient->bsgPutItem(aPutResult,bigsetRoot, item);
        return aPutResult.ok ? 0: -1;
    } catch (...) {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
            aClient->bsgPutItem(aPutResult,bigsetRoot, item);
            return aPutResult.ok ? 0: -1;
        } catch (...) {
        }
    }
    return -1;
}

int32_t BigsetRemoteKV::_get(VType &_return, const KType &key) const {
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;

    ClientWrapper aClient(dbHost, dbPort);
    bskv::TItemResult aGetResult;
    try {
        if (!aClient->sureOpen())
            return -1;
        //aClient->get(_return, key);
        aClient->bsgGetItem(aGetResult, this->bigsetRoot, key);
        if (aGetResult.error == bskv::TErrorCode::EGood)
            _return.swap(aGetResult.item.value );
        
    } catch (...) {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
//            aClient->get(_return, key);
            aClient->bsgGetItem(aGetResult, this->bigsetRoot, key);
            if (aGetResult.error == bskv::TErrorCode::EGood)
                _return.swap(aGetResult.item.value );

        } catch (...) {
        }
    }
    if (_return.length() == 0)
        return -1;
    else return 0;

    return -1;
}

int32_t BigsetRemoteKV::_get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const {
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;

    ClientWrapper aClient(dbHost, dbPort);

    string key((const char*) inKeyData, keyLen);

    bskv::TItem item;
    bskv::TItemResult aGetResult;
    
    try {
        if (!aClient->sureOpen())
            return -1;
        aClient->bsgGetItem(aGetResult, this->bigsetRoot, key);
        
//        aClient->get(_returnValue, key);
        
    } catch (...) {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
            aClient->bsgGetItem(aGetResult, this->bigsetRoot, key);

        } catch (...) {
        }
    }
    if (aGetResult.item.value.length() == 0 
            || aGetResult.error != bskv::TErrorCode::EGood )
        return -1;
    else if (datalen >= 0 && aGetResult.item.value.length() > (size_t)datalen) {
        aGetResult.item.value = aGetResult.item.value.substr(0, datalen);
    }
    //outData = &_returnValue;
    memcpy(outData, aGetResult.item.value.data(), aGetResult.item.value.length());

    return 0;
}

int32_t BigsetRemoteKV::_multiGet(KVMap &_return, const KList &keys) const
{
    size_t aSize  = keys.size();
    // cái này làm đơn giản thôi. 
    for (size_t aIndex = 0; aIndex < aSize; aIndex++)
    {
	VType aValue;
	if (this->_get(aValue, keys[aIndex] ) == 0)
	{
	    if (aValue.length() > 0 )
		_return[keys [aIndex] ] = aValue;
	}
    }
    return (_return.size() == keys.size() ? 0: -1);
}

int32_t BigsetRemoteKV::_multiPut(const AbstractKVStorage::KVMap& keyvals)
{
    if (keyvals.size() == 0)
        return 0;
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;

    ClientWrapper aClient(dbHost, dbPort);

    bskv::TMultiPutItemResult multiPutResult;
    bskv::TItemSet multiItems;
    multiItems.items.resize(keyvals.size() );
    size_t index = 0;
    for (AbstractKVStorage::KVMap::const_iterator aIt = keyvals.begin();
            aIt != keyvals.end(); aIt++)
    {
        
        multiItems.items[index].key = aIt->first;
        multiItems.items[index].value = aIt->second;
    }
    
    try {
        if (!aClient->sureOpen())
            return -1;
        aClient->bsgMultiPut(multiPutResult, this->bigsetRoot
                , multiItems, false, false);
        //return aClient->multiPutM(keyvals);
        
    } catch (...) {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
            aClient->bsgMultiPut(multiPutResult, this->bigsetRoot
                , multiItems, false, false);

        } catch (...) {
            return -1;
        }
    }

    return multiPutResult.error == bskv::TErrorCode::EGood ? 0 : -1 ;
}// should override for some remote KVStorage
//

int32_t BigsetRemoteKV::_remove(const KType &key) 
{
    Endpoint aEndpoint;
    _endpointManager.getEndpoint(aEndpoint);
    const std::string& dbHost = aEndpoint.host;
    int dbPort = aEndpoint.port;

    ClientWrapper aClient(dbHost, dbPort);

    try {
        if (!aClient->sureOpen())
            return -1;
        return aClient->bsgRemoveItem(this->bigsetRoot, key) ? 0 : -1;
    }
    catch (...) 
    {
        try {
            aClient->close();
            if (!aClient->sureOpen())
                return -1;
		
	    return aClient->bsgRemoveItem(this->bigsetRoot, key) ? 0 : -1;

        } catch (...) {
            return -1;
        }
    }
    
    return 0;
}


}}