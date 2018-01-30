/* 
 * File:   SimpleKCStorage.h
 * Author: anhn
 *
 * Created on October 15, 2012, 4:51 PM
 */

#ifndef SIMPLEKCSTORAGE_H
#define	SIMPLEKCSTORAGE_H

#include <string>
#include <iostream>
#include <Poco/SharedPtr.h>
#include <Storage/AbstractKVStorage.h>

namespace kyotocabinet {
	class BasicDB;
}

namespace openstars { namespace storage {
    
using std::string;
using namespace kyotocabinet;
using Poco::SharedPtr;

template <class T>
class PartitionedStorage;

/**
 * Simple KyotoCabinet PolyDB wrapper implementing AbstractKVStorage
 */
class SimpleKCStorage : public AbstractKVStorage {
	friend class PartitionedStorage<SimpleKCStorage>;
	friend class KCStorage;
public:
	SimpleKCStorage();
	SimpleKCStorage(const string& path);
	virtual ~SimpleKCStorage();
	virtual void initialize(const string& path);
	bool open();
	void close();
public:
	class Cursor;
public:
	SharedPtr<AbstractCursor> iterate();
protected:
	virtual int32_t _get(VType& _return, const KType& key) const;

	virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const;

	virtual int32_t _put( const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) ;
	
	virtual int32_t _remove(void* aKey, int aKeyLen);

	virtual bool _has(const KType& key);

	virtual int32_t _multiGet(KVMap& _return, const KList& keys) const;
protected:
	string _path;
	mutable SharedPtr<BasicDB> _db;
};

}}

#endif	/* SIMPLEKCSTORAGE_H */

