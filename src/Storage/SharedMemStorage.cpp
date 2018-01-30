/* 
 * File:   SharedMemStorage.cpp
 * Author: trungthanh
 * 
 * Created on April 9, 2013, 9:44 AM
 */

#include "Storage/SharedMemStorage.h"
#include "Storage/FixedSizeSharedMemTable.h"
#include "Storage/NoHashT.h"

#include "Poco/File.h"
#include "Poco/Types.h"
#include "Poco/Timestamp.h"
#include <algorithm>
#include <netinet/in.h>

namespace openstars { namespace storage{ 

SharedMemStorage::SharedMemStorage(Poco::SharedPtr<FixedSizeSharedMemTable> table)
:_table(table)
{    
    _valueSize = _table->valueSize();
}



SharedMemStorage::~SharedMemStorage()
{
}

void SharedMemStorage::openShm(const std::string& shmName)
{
    if (!_table)
	return;
    _table->open(shmName);
    _table->warmUp();
}

void SharedMemStorage::openFileMapping(const std::string& env, const std::string& dbName)
{
    if (!_table)
	return;
    
    Poco::File aDir(env);
    aDir.createDirectories();
    std::string aPath = env + dbName;
    Poco::File aFile(aPath);
    
    _table->open(aFile);	
    _table->warmUp();
}

int32_t SharedMemStorage::_put(const KType &key, const VType &data)
{
    if (!_table)
	return -1;

    int aSize = _valueSize;
    if (data.length() < aSize)
	aSize = data.length();
    // Nếu kích thước lệch nhau thì khi get ra có thể sẽ sai đó nhé 
    
    NoHashT<size_t> aCaster;
    size_t aIntKey = aCaster(key);
    
    char* aPtr = _table->getAt(aIntKey);
    
    if (aPtr == NULL)
	return -1; 
    
    ::memcpy(aPtr, data.data(), aSize);
    return 0;
    
}

int32_t SharedMemStorage::_put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) 
{
    if (!_table)
	return -1;
    
    int aSize = _valueSize;
    if (datalen < aSize)
	aSize = datalen;
    // Nếu kích thước lệch nhau thì khi get ra có thể sẽ sai đó nhé 
    
    NoHashT<size_t> aCaster;
    size_t aIntKey = aCaster(inKeyData, keyLen);
    
    char* aPtr = _table->getAt(aIntKey);
    
    if (aPtr == NULL)
	return -1; 
    
    ::memcpy(aPtr, inData, aSize);
    return 0;
    
}
// should be overridden

int32_t SharedMemStorage::_get(VType &_return, const KType &key) const
{
    if (!_table)
	return -1;

    NoHashT<size_t> aCaster;
    size_t aIntKey = aCaster(key);
    
    char* aPtr = _table->getAt(aIntKey);

    if (aPtr != NULL)
    {
	_return.assign(aPtr, _valueSize);
	return 0;
    }
    return -1;
}

int32_t SharedMemStorage::_get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const
{
    if (!_table)
	return -1;
    NoHashT<size_t> aCaster;
    size_t aIntKey = aCaster(inKeyData, keyLen);
    
    char* aPtr = _table->getAt(aIntKey);
    
    if (aPtr == NULL)
	return -1; 

    int aSize = datalen > _valueSize? _valueSize : datalen;
    
    ::memcpy(outData, aPtr, aSize);
    return 0;
}

int32_t SharedMemStorage::_multiGet(KVMap &_return, const KList &keys) const
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

int32_t SharedMemStorage::_multiPut(const AbstractKVStorage::KVMap& keyvals)
{
    int32_t result = 0;
    for (AbstractKVStorage::KVMap::const_iterator aIt = keyvals.begin(); aIt != keyvals.end(); aIt++)
    {
	result += this->_put(aIt->first, aIt->second);		
    }
    return result;    
}

int32_t SharedMemStorage::_remove(const KType &key)
{
    NoHashT<size_t> aCaster;
    size_t aIntKey = aCaster(key);
    
    char* aPtr = _table->getAt(aIntKey);
    if (aPtr)
    {
	::memset(aPtr, 0 , _valueSize);
    }
    return 0;
}

//////////////////


inline void nettohost(Poco::UInt64& aI64){
#ifdef ntohll
    aI64 = ntohll(aI64);
#else
    uint32_t* pInt = (uint32_t*)&aI64;
    *pInt = ntohl(*pInt);
    pInt++;
    *pInt = ntohl(*pInt);
    
#endif
}

inline void hosttonet(Poco::UInt64& aI64){
#ifdef htonll
    aI64 = htonll(aI64);
#else
    uint32_t* pInt = (uint32_t*)&aI64;
    *pInt = htonl(*pInt);
    pInt++;
    *pInt = htonl(*pInt);
    
#endif
}

void SmartSharedMemStorage::ShareSyncInfo::convertToHost()
{
    if (this->hostData)
        return;
    hosttonet(this->lastSync);
    hosttonet(this->lastWrite);
    hosttonet(this->readCount);
    hosttonet(this->writeCount);
    hostData = true;
    
}

void SmartSharedMemStorage::ShareSyncInfo::convertToNet()
{
    if (!this->hostData)
        return;
    nettohost(this->lastSync);
    nettohost(this->lastWrite);
    nettohost(this->readCount);
    nettohost(this->writeCount);
    hostData = false;
    
}

SmartSharedMemStorage::SmartSharedMemStorage(Poco::SharedPtr<FixedSizeSharedMemTable> shmtable
            ,Poco::SharedPtr<FixedSizeSharedMemTable> fmtable)
:_shmtable(shmtable)
,_fmtable(fmtable)
{    
    _valueSize = _shmtable->valueSize();
    shmInfo = fmInfo = NULL;
}



SmartSharedMemStorage::~SmartSharedMemStorage()
{
    this->flushFromSHM();
    if (shmInfo)
        shmInfo->convertToNet();
    if (fmInfo)
        fmInfo->convertToNet();    
}

void SmartSharedMemStorage::open(const std::string& shmName, const std::string& env, const std::string& dbName)
{
    this->openShm(shmName);
    this->openFileMapping(env, dbName);
    checkVerAndWarmSHM();
}

void SmartSharedMemStorage::openShm(const std::string& shmName)
{
    if (!_shmtable)
	return;
    _shmtable->open(shmName);
    shmInfo =  (ShareSyncInfo*)_shmtable->getExtra(0);
    shmInfo->convertToHost();
    //_shmtable->warmUp();
}

void SmartSharedMemStorage::openFileMapping(const std::string& env, const std::string& dbName)
{
    if (!_fmtable)
	return;
    
    Poco::File aDir(env);
    aDir.createDirectories();
    std::string aPath = env + dbName;
    Poco::File aFile(aPath);
    
    _fmtable->open(aFile);
    
    fmInfo =  (ShareSyncInfo*)_shmtable->getExtra(0);
    fmInfo->convertToHost();
    
    //_fmtable->warmUp();
}

void SmartSharedMemStorage::checkVerAndWarmSHM()
{
    if (fmInfo->lastSync < fmInfo->lastWrite) // last lost data?
        ;
    if (fmInfo->lastSync < shmInfo->lastWrite)
        return; 
        
    char* start = _fmtable->begin();
    char* end = _fmtable->getExtra(0);
    
    char* destStart = _shmtable->begin();
    std::copy(start, end, destStart);
    
    fmInfo->lastSync = shmInfo->lastSync = Poco::Timestamp().epochTime();
    
}

void SmartSharedMemStorage::flushFromSHM()
{
    if (shmInfo->lastWrite < fmInfo->lastWrite)
        return;
    if (fmInfo->lastSync > shmInfo->lastWrite)
        return;
    
    char* start = _shmtable->begin();
    char* end = _shmtable->getExtra(0);
    
    char* destStart = _fmtable->begin();
    std::copy(start, end, destStart);
    
    fmInfo->lastSync = shmInfo->lastSync = Poco::Timestamp().epochTime();
}


int32_t SmartSharedMemStorage::_put(const KType &key, const VType &data)
{
      if ( (!_shmtable) || (!_fmtable) )
	return -1;
      
    int aSize = _valueSize;
    if (data.length() < aSize)
	aSize = data.length();
    // Nếu kích thước lệch nhau thì khi get ra có thể sẽ sai đó nhé 
    
    NoHashT<size_t> aCaster;
    size_t aIntKey = aCaster(key);
    
    char* aPtr = _shmtable->getAt(aIntKey);
    
    if (aPtr == NULL)
	return -1; 
    
    ::memcpy(aPtr, data.data(), aSize);
    
    shmInfo->lastWrite = fmInfo->lastWrite = Poco::Timestamp().epochTime();
    
    return 0;
}

int32_t SmartSharedMemStorage::_put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen)
{
      if ( (!_shmtable) || (!_fmtable) )
	return -1;
    
    int aSize = _valueSize;
    if (datalen < aSize)
	aSize = datalen;
    // Nếu kích thước lệch nhau thì khi get ra có thể sẽ sai đó nhé 
    
    NoHashT<size_t> aCaster;
    size_t aIntKey = aCaster(inKeyData, keyLen);
    
    char* aPtr = _shmtable->getAt(aIntKey);
    
    if (aPtr == NULL)
	return -1; 
    
    ::memcpy(aPtr, inData, aSize);

    shmInfo->lastWrite = fmInfo->lastWrite = Poco::Timestamp().epochTime();
    
    return 0;    
}
             // should be overridden

int32_t SmartSharedMemStorage::_get(VType &_return, const KType &key) const
{
    if ( (!_shmtable) || (!_fmtable) )
	return -1;
    NoHashT<size_t> aCaster;
    size_t aIntKey = aCaster(key);
    
    char* aPtr = _shmtable->getAt(aIntKey);

    if (aPtr != NULL)
    {
	_return.assign(aPtr, _valueSize);
	return 0;
    }
    return -1;
        
}

int32_t SmartSharedMemStorage::_get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const
{
    if ( (!_shmtable) || (!_fmtable) )
      return -1;    
    NoHashT<size_t> aCaster;
    size_t aIntKey = aCaster(inKeyData, keyLen);
    
    char* aPtr = _shmtable->getAt(aIntKey);
    
    if (aPtr == NULL)
	return -1; 

    int aSize = datalen > _valueSize? _valueSize : datalen;
    
    ::memcpy(outData, aPtr, aSize);   
    return 0;
}

int32_t SmartSharedMemStorage::_multiGet(KVMap &_return, const KList &keys) const
{
    if ( (!_shmtable) || (!_fmtable) )
      return -1;     
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

int32_t SmartSharedMemStorage::_multiPut(const AbstractKVStorage::KVMap& keyvals)
{
    if ( (!_shmtable) || (!_fmtable) )
      return -1;    
    int32_t result = 0;
    for (AbstractKVStorage::KVMap::const_iterator aIt = keyvals.begin(); aIt != keyvals.end(); aIt++)
    {
	result += this->_put(aIt->first, aIt->second);		
    }
    return result;      
}

int32_t SmartSharedMemStorage::_remove(const KType &key)
{
    if ( (!_shmtable) || (!_fmtable) )
      return -1;     
    NoHashT<size_t> aCaster;
    size_t aIntKey = aCaster(key);
    
    char* aPtr = _shmtable->getAt(aIntKey);
    if (aPtr)
    {
	::memset(aPtr, 0 , _valueSize);
    }
    shmInfo->lastWrite = fmInfo->lastWrite = Poco::Timestamp().epochTime();
    return 0;    
}


} }