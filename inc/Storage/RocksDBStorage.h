/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RocksDBStorage.h
 * Author: trungthanh
 *
 * Created on March 7, 2018, 1:09 AM
 */

#ifndef ROCKSDBSTORAGE_H
#define ROCKSDBSTORAGE_H

#include <Storage/AbstractKVStorage.h>

#include "rocksdb/db.h"

namespace openstars { namespace storage{
    

class RocksDBStorage: public AbstractKVStorage {
public:
    
/**
 * 
 * @param dbString 
 * Storage config string
 * @example 
 * "path=/tmp/rocksdb,compression=snappy,use_fsync=false,allow_mmap_reads=false"
 *      ",allow_mmap_writes=false,write_buffer_size=640000000"
 * 
 * supported compression:
 * kNoCompression = 0x0, => nc, nocompression    
 * kSnappyCompression = 0x1, => snappy
 * kZlibCompression = 0x2, => zlib
 * kBZip2Compression = 0x3, => bz2
 * kLZ4Compression = 0x4, => lz4
 * kLZ4HCCompression = 0x5, => lz4hcc
 * kXpressCompression = 0x6, => xpress
 * kZSTD = 0x7, => zstd
 * 
 * other fields
 * 
 */
    RocksDBStorage(const std::string& dbParams);

    virtual ~RocksDBStorage();
public:    
    virtual bool open();

    virtual void close();

    Poco::SharedPtr<AbstractCursor> iterate();

protected:
    virtual int32_t _get(VType& _return, const KType& key) const;

    virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const;

    virtual int32_t _put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen);

    virtual int32_t _remove( void* aKey, int aKeyLen);

    virtual bool _has(const KType& key);

    virtual int32_t _multiGet(KVMap& _return, const KList& keys) const;
    
    
private:
    RocksDBStorage(const RocksDBStorage& orig);

    mutable rocksdb::DB* _db;
    std::string _dbParams;
    
};

} } //openstars::storage 

#endif /* ROCKSDBSTORAGE_H */

