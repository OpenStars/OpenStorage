/* 
 * File:   SharedMemStorage.h
 * Author: trungthanh
 *
 * Created on April 9, 2013, 9:44 AM
 */

#ifndef SHAREDMEMSTORAGE_H
#define	SHAREDMEMSTORAGE_H

#include "Storage/AbstractKVStorage.h"

class FixedSizeSharedMemTable;

namespace openstars { namespace storage{ 
    
class SharedMemStorage:public openstars::storage::AbstractKVStorage
{
public:
    SharedMemStorage(Poco::SharedPtr<FixedSizeSharedMemTable> table);
    virtual ~SharedMemStorage();
public:
    void openShm(const std::string& shmName);
    
    void openFileMapping(const std::string& env, const std::string& dbName);
    
protected:
    virtual int32_t _put(const KType &key, const VType &data);
    
    virtual int32_t _put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) ;
		 // should be overridden

    virtual int32_t _get(VType &_return, const KType &key) const;

    virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const;

    virtual int32_t _multiGet(KVMap &_return, const KList &keys) const;

    int32_t _multiPut(const AbstractKVStorage::KVMap& keyvals);

    int32_t _remove(const KType &key);
	
private:
    SharedMemStorage(const SharedMemStorage& orig);
    
    mutable Poco::SharedPtr<FixedSizeSharedMemTable> _table;
    size_t _valueSize;
    
};

class SmartSharedMemStorage:public openstars::storage::AbstractKVStorage
{
public:
    SmartSharedMemStorage(Poco::SharedPtr<FixedSizeSharedMemTable> shmtable,
            Poco::SharedPtr<FixedSizeSharedMemTable> fmtable);
    virtual ~SmartSharedMemStorage();
public:
    struct ShareSyncInfo{
        Poco::UInt64 lastWrite;
        Poco::UInt64 lastSync;
        Poco::UInt64 readCount;
        Poco::UInt64 writeCount;
        bool hostData; // net to host 
        void convertToHost();
        void convertToNet();
        
    };
public:
    
    void open(const std::string& shmName, const std::string& env, const std::string& dbName);
    
protected:
    void openShm(const std::string& shmName);
    
    void openFileMapping(const std::string& env, const std::string& dbName);
    
private:
    void flushFromSHM();
    void checkVerAndWarmSHM();
    
    
protected:
    virtual int32_t _put(const KType &key, const VType &data);
    
    virtual int32_t _put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) ;
		 // should be overridden

    virtual int32_t _get(VType &_return, const KType &key) const;

    virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const;

    virtual int32_t _multiGet(KVMap &_return, const KList &keys) const;

    int32_t _multiPut(const AbstractKVStorage::KVMap& keyvals);

    int32_t _remove(const KType &key);
	
private:
    SmartSharedMemStorage(const SmartSharedMemStorage& orig);
    
    mutable Poco::SharedPtr<FixedSizeSharedMemTable> _shmtable; // share memory table
    mutable Poco::SharedPtr<FixedSizeSharedMemTable> _fmtable;
    ShareSyncInfo* shmInfo;
    ShareSyncInfo* fmInfo;
    size_t _valueSize;
    
};

} } 

#endif	/* SHAREDMEMSTORAGE_H */

