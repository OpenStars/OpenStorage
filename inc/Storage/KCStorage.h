/* 
 * File:   KCStorage.h
 * Author: anhn
 *
 * Created on October 12, 2012, 11:35 AM
 */

#ifndef UP_STORAGE_KCSTORAGE_H
#define	UP_STORAGE_KCSTORAGE_H

#include <string>
#include <iostream>

#include <Storage/SimpleKCStorage.h>
#include <Hashing/DefaultHasher.h>

namespace openstars { namespace storage {
using std::string;
using std::vector;
using Poco::SharedPtr;

class KCStorage : public AbstractKVStorage {
public:
	typedef openstars::hashing::DefaultHasher HasherType;
	class Cursor;
public:
	/**
	 * Hash based partitioned KyotoCabinet PolyDB
	 * 
     * @param dbString Storage config string
	 * @example 
	 * path=/tmp/kc,baseName=test,dbType=.kch,partitions=1,dbOptions=#abc=45#def=3
	 * 
	 * Default param values if omitted: path = /tmp/kyoto, baseName = test, dbType = .kch, numPartitions = 1, dbOptions empty
     */
	KCStorage(const string& dbString);
	virtual ~KCStorage();
	
	virtual void close();
	
	virtual bool open();
	
	/**
	 * Get Cursor to iterate through data
     * @return 
     */
	SharedPtr<AbstractCursor> iterate();
protected:
	virtual SharedPtr<SimpleKCStorage> getStorage(const KType& key) const;
	virtual SharedPtr<SimpleKCStorage> getStorage(const void* kBuf_, int kSize_) const;
protected:
	virtual int32_t _get(VType& _return, const KType& key) const;

	virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const;

	virtual int32_t _put( const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) ;
	
	virtual int32_t _remove( void* aKey, int aKeyLen);

	virtual bool _has(const KType& key);

	virtual int32_t _multiGet(KVMap& _return, const KList& keys) const;
protected:
	bool _isOpen;
	int _numParts;
	string _dbString;
	string _path;
	string _baseName;
	string _dbType;
	string _dbOptions;
	vector<SharedPtr<SimpleKCStorage> > _dbParts;
	size_t _partitionMask;
};
}}	//namespace

#endif	/* KCSTORAGE_H */

