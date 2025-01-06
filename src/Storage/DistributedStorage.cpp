/* 
 * File:   DistributedStorage.cpp
 * Author: trungthanh
 * 
 * Created on March 26, 2013, 11:14 PM
 */

#include "Storage/DistributedStorage.h"
#include <iostream>
#include "KVDataService.h"
#include "thriftutil/TClient.h"
#include "thriftutil/ClientManagerT.h"

using namespace std;
using namespace kv;

using namespace openstars::distributed;

typedef TClient <KVDataServiceClient> TClientType;

typedef ClientWrapperT<TClientType> ClientWrapper;



namespace openstars { namespace storage{

DistributedStorage::DistributedStorage(openstars::distributed::BackendManager* backendMngr)
:_backendMngr(backendMngr)
{
}

//DistributedStorage::DistributedStorage(const DistributedStorage& orig)
//{
//}

DistributedStorage::~DistributedStorage()
{
}

/////////////////////
class DistributedStorageHelper
{
public:
    static int32_t put(const BackendInfo& aBackend, const KType &key, const VType &data)
    {
	const std::string& dbHost = aBackend.getHost();
	int dbPort = aBackend.getPort();
	if (dbPort <= 0)
	    return -1;

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
    
    static int32_t put(const BackendInfo& aBackend, const void* inKeyData
	, const int& keyLen
	, const void* inData, const int& datalen )
    {

	std::string key((const char*) inKeyData, keyLen);
	std::string data((const char*) inData, datalen);
	
	return put(aBackend, key,data);
    }
    
    static int32_t get(const BackendInfo& aBackend, AbstractKVStorage::VType &_return,
	const AbstractKVStorage::KType &key)
    {
	const std::string& dbHost = aBackend.getHost();
	int dbPort = aBackend.getPort();
	if (dbPort <= 0)
	    return -1;
	
	ClientWrapper aClient(dbHost, dbPort);
	try {
	    if (!aClient->sureOpen())
		return -1;
	    aClient->get(_return, key);
	    
	    if (_return.length() > 0)
		return 0;
	    return -1;
	} 
	catch (...) 
	{
	    try 
	    {
		aClient->close();
		if (!aClient->sureOpen())
		    return -1;
		
		aClient->get(_return, key);
		if (_return.length() > 0)
		    return 0;
		return -1;
		
	    }
	    catch (...) 
	    {
	    }
	}
	return -1;
	
    }

    static int32_t remove(const BackendInfo& aBackend, const std::string& key)
    {
	const std::string& dbHost = aBackend.getHost();
	int dbPort = aBackend.getPort();
	if (dbPort <= 0)
	    return -1;
	
	ClientWrapper aClient(dbHost, dbPort);
	try {
	    if (!aClient->sureOpen())
		return -1;
	    return aClient->remove( key);
	} 
	catch (...) 
	{
	    try 
	    {
		aClient->close();
		if (!aClient->sureOpen())
		    return -1;
		
		return aClient->remove(key);
	    }
	    catch (...) 
	    {
	    }
	}
	return -1;
	
    }

    static int32_t update(const BackendInfo& aBackend, const KType &key, const VType &data)
    {
	const std::string& dbHost = aBackend.getHost();
	int dbPort = aBackend.getPort();
	if (dbPort <= 0)
	    return -1;

	ClientWrapper aClient(dbHost, dbPort);
	try {
	    if (!aClient->sureOpen())
		return -1;
	    return aClient->update(key, data);
	} catch (...) {
	    try {
		aClient->close();
		if (!aClient->sureOpen())
		    return -1;
		return aClient->update(key, data);
	    } catch (...) {
	    }
	}
	return -1;
	
    }
    
    static int32_t add(const BackendInfo& aBackend, const KType &key, const VType &data)
    {
	const std::string& dbHost = aBackend.getHost();
	int dbPort = aBackend.getPort();
	if (dbPort <= 0)
	    return -1;

	ClientWrapper aClient(dbHost, dbPort);
	try {
	    if (!aClient->sureOpen())
		return -1;
	    return aClient->add(key, data);
	} catch (...) {
	    try {
		aClient->close();
		if (!aClient->sureOpen())
		    return -1;
		return aClient->add(key, data);
	    } catch (...) {
	    }
	}
	return -1;
	
    }
    
    
};
//////////////////////////

int32_t DistributedStorage::_put(const KType &key, const VType &data)
{
    int32_t result = 0;
    if (this->_backendMngr)
    {
	std::vector<BackendInfo> aBackendList;
	_backendMngr->getBackendW(aBackendList, key);
	for (int aIndex = 0; aIndex < aBackendList.size() ; aIndex++ )
	{
	    result += DistributedStorageHelper::put(aBackendList[aIndex], key, data);
	}
    }
    else
	return -1;
    return result;
    
}

int32_t DistributedStorage::_put(const void* inKeyData
	, const int& keyLen
	, const void* inData, const int& datalen) 
{
    int32_t result = 0;
    if (this->_backendMngr)
    {
	std::vector<BackendInfo> aBackendList;
	_backendMngr->getBackendW(aBackendList, inKeyData, keyLen);
	cout<<"backend for writes: "<<aBackendList.size()<<endl;
	for (int aIndex = 0; aIndex < aBackendList.size() ; aIndex++ )
	{
	    result += DistributedStorageHelper::put(aBackendList[aIndex],
		    inKeyData, keyLen, inData, datalen);
	}
    }
    else
	return -1;
    return result;
}

int32_t DistributedStorage::_get(VType &_return, const KType &key) const
{
    int32_t result = 0;
    if (this->_backendMngr)
    {
	std::vector<BackendInfo> aBackendList;
	_backendMngr->getListBackendR(aBackendList, key);
	for (int aIndex = 0; aIndex < aBackendList.size() ; aIndex++ )
	{
	    result = DistributedStorageHelper::get(aBackendList[aIndex], _return, key);
	    if (result == 0)
		return 0;
	}
    } 
    else
	return -1;
    return result;
	
}

int32_t DistributedStorage::_get(const void* inKeyData, 
	const int& keyLen, 
	void* outData, 
	const int& datalen) const
{
    string _returnValue, key;

    key = std::string((const char*) inKeyData, keyLen);
    int32_t result = this->_get(_returnValue , key);
    
    if (result != 0)
	return result;
    
    if (_returnValue.length() == 0)
        return -1;
    else if (_returnValue.length() > datalen) 
    {
        _returnValue = _returnValue.substr(0, datalen);
    }
    //outData = &_returnValue;
    memcpy(outData, _returnValue.data(), _returnValue.length());

    return result;
    
}

int32_t DistributedStorage::_multiGet(KVMap &_return, const KList &keys) const
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

int32_t DistributedStorage::_multiPut(const AbstractKVStorage::KVMap& keyvals)
{
    int32_t result = 0;
    for (AbstractKVStorage::KVMap::const_iterator aIt = keyvals.begin(); aIt != keyvals.end(); aIt++)
    {
	result += this->_put(aIt->first, aIt->second);		
    }
    return result;
}

int32_t DistributedStorage::_remove(const KType &key) 
{
    int32_t result = 0;
    if (this->_backendMngr)
    {
	std::vector<BackendInfo> aBackendList;
	_backendMngr->getBackendW(aBackendList, key);
	for (int aIndex = 0; aIndex < aBackendList.size() ; aIndex++ )
	{
	    result += DistributedStorageHelper::remove(aBackendList[aIndex],key);
	}
    }
    else
	return -1;
    return result;
    
}

    /*
     * of date value of existing key, error if it is not existed
     */
int32_t DistributedStorage::update(const KType &key, const VType &data)
{
    int32_t result = 0;
    if (this->_backendMngr)
    {
	std::vector<BackendInfo> aBackendList;
	_backendMngr->getBackendW(aBackendList, key);
	for (int aIndex = 0; aIndex < aBackendList.size() ; aIndex++ )
	{
	    result += DistributedStorageHelper::update(aBackendList[aIndex],key, data);
	}
    }
    else
	return -1;
    return result;
    
}

    /*
     * add new key-value pair, error if it is already existed
     */
int32_t DistributedStorage::add(const KType &key, const VType &data)
{
    int32_t result = 0;
    if (this->_backendMngr)
    {
	std::vector<BackendInfo> aBackendList;
	_backendMngr->getBackendW(aBackendList, key);
	for (int aIndex = 0; aIndex < aBackendList.size() ; aIndex++ )
	{
	    result += DistributedStorageHelper::add(aBackendList[aIndex],key ,data);
	}
    }
    else
	return -1;
    return result;
    
}



} }