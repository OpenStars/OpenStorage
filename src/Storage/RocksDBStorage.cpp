/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RocksDBStorage.cpp
 * Author: trungthanh
 * 
 * Created on March 7, 2018, 1:09 AM
 */

#include "Storage/RocksDBStorage.h"
#include "Poco/StringTokenizer.h"
#include "Poco/NumberParser.h"

namespace openstars { namespace storage{

RocksDBStorage::RocksDBStorage(const std::string& dbParams):_db(nullptr), _dbParams(dbParams) {
}


RocksDBStorage::~RocksDBStorage() {
}

/**
 * 
 * @param dbString 
 * Storage config string
 * @example 
 * path=/tmp/rocksdb,dboption=#compression:nc
 * path=/tmp/rocksdb,dboption=#compression:snappy
 * 
 * supported compression:
 * kNoCompression = 0x0, => nc, nocompression
 *      
 * kSnappyCompression = 0x1, => snappy
 * kZlibCompression = 0x2, => zlib
 * kBZip2Compression = 0x3, => bz2
 * kLZ4Compression = 0x4, => lz4
 * kLZ4HCCompression = 0x5, => lz4hcc
 * kXpressCompression = 0x6, => xpress
 * kZSTD = 0x7, => zstd
 * 
 */
bool RocksDBStorage::open(){
    if (_db != nullptr)
        return false;
    rocksdb::Options rdbopts;
    rdbopts.create_if_missing = true;
    Poco::StringTokenizer stk(_dbParams, ",", Poco::StringTokenizer::TOK_IGNORE_EMPTY| Poco::StringTokenizer::TOK_TRIM);
    std::string aPath = "/tmp/rocksdb";
    
    for (size_t i = 0; i < stk.count(); i++ )
    {
        Poco::StringTokenizer aParamParser(stk[i], "="
            , Poco::StringTokenizer::TOK_IGNORE_EMPTY| Poco::StringTokenizer::TOK_TRIM);
        if (aParamParser.count() >= 2)
        {
            try {
                std::string aName = aParamParser[0];
                std::string aValue = aParamParser[1];
                if (aName == "path")
                    aPath = aValue;
                if (aName == ("compression") )
                {
                    if (aValue =="nc") rdbopts.compression = rocksdb::kNoCompression;
                    if (aValue =="snappy") rdbopts.compression = rocksdb::kSnappyCompression;
                    if (aValue =="zlib") rdbopts.compression = rocksdb::kZlibCompression;
                    if (aValue =="bz2") rdbopts.compression = rocksdb::kBZip2Compression;
                    if (aValue =="lz4") rdbopts.compression = rocksdb::kLZ4Compression;
                    if (aValue =="lz4hcc") rdbopts.compression = rocksdb::kLZ4HCCompression;
                    if (aValue =="xpress") rdbopts.compression = rocksdb::kXpressCompression;
                    if (aValue =="zstd") rdbopts.compression = rocksdb::kZSTD;                
                }
                if (aName =="use_fsync")
                    rdbopts.use_fsync = Poco::NumberParser::parseBool(aValue);
                if (aName =="allow_mmap_reads")
                    rdbopts.allow_mmap_reads = Poco::NumberParser::parseBool(aValue);
                if (aName =="allow_mmap_writes")
                    rdbopts.allow_mmap_writes = Poco::NumberParser::parseBool(aValue);
                if (aName == "write_buffer_size")
                    rdbopts.write_buffer_size = Poco::NumberParser::parseUnsigned64(aValue);
                
            } 
            catch (...) {}
        }
        
    }
    auto aStatus = rocksdb::DB::Open(rdbopts, aPath, &_db);
    if ( !aStatus.ok() )
        _db = nullptr;
    return aStatus.ok();   
    
    
}

void RocksDBStorage::close()
{
    if (_db == nullptr)
        return;
    
    delete _db;
    _db = nullptr;
    
}

//Todo: implement this
Poco::SharedPtr<AbstractCursor> RocksDBStorage::iterate()
{
    return Poco::SharedPtr<AbstractCursor>();
}

int32_t RocksDBStorage::_get(VType& _return, const KType& key) const{
    if (_db != nullptr)
    {
        _db->Get(rocksdb::ReadOptions(), rocksdb::Slice(key), &_return);
        return 0;
    }
    return -1;
}

int32_t RocksDBStorage::_get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const
{
    rocksdb::Slice slKey((const char*)inKeyData, keyLen);
    std::string value;
    rocksdb::Status s = _db->Get(rocksdb::ReadOptions(), slKey, &value);
    if (s.ok()) {
            size_t outLen = value.length();
            int copyLen = datalen > outLen ? outLen : datalen;
            ::memcpy(outData, value.data(), copyLen);
            return 0;
    }
    return -1;

}

int32_t RocksDBStorage::_put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen)
{
	rocksdb::Slice key((const char*)inKeyData, keyLen);
	rocksdb::Slice value((const char*)inData, datalen);
	rocksdb::Status s = _db->Put(rocksdb::WriteOptions(), key, value);

	if (s.ok()) {
		return 0;
	}
	return -1;    
}

int32_t RocksDBStorage::_remove( void* aKey, int aKeyLen)
{
	rocksdb::Slice key((const char*)aKey, aKeyLen);
	rocksdb::Status s;
        s = _db->Delete(rocksdb::WriteOptions(), key);

	if (s.ok()) {
		return 0;
	}
	return -1;   
}

bool RocksDBStorage::_has(const KType& key)
{
    rocksdb::Slice slKey(key.data(), key.length());
    std::string value;
    rocksdb::Status s = _db->Get(rocksdb::ReadOptions(), slKey, &value);
    return s.ok();    
}

int32_t RocksDBStorage::_multiGet(KVMap& _return, const KList& keys) const
{
    if (keys.size() == 0)
        return 0;
    std::vector<std::string> vList;
    std::vector<rocksdb::Slice> kList;
    kList.reserve(keys.size() );
    for (auto k: keys){
        kList.push_back(rocksdb::Slice(k) );
    }
    auto statuses = _db->MultiGet(rocksdb::ReadOptions(), kList, &vList);
    if ( vList.size() != kList.size() )
        return -1;
    int i = 0;
    for (auto k: keys)
    {
        if (statuses[i].ok())
            _return[k] = vList[i++];
    }
    
}


} }