/* 
 * File:   SimpleLevelStorage.h
 * Author: anhn
 *
 * Created on October 12, 2012, 5:32 PM
 */

#include <string>
#include <iostream>
#include <Poco/SharedPtr.h>
#include <Storage/AbstractKVStorage.h>

#ifndef SIMPLELEVELSTORAGE_H
#define	SIMPLELEVELSTORAGE_H

namespace leveldb {
class DB;
}
namespace openstars { namespace storage {
using Poco::SharedPtr;

/**
 * Thin wrapper over LevelDB
 * @param path
 */
class SimpleLevelStorage : public AbstractKVStorage {
	friend class LevelStorage;

public:

	SimpleLevelStorage() {
	}
	SimpleLevelStorage(const std::string& path);
	virtual ~SimpleLevelStorage();
	virtual bool open();
	virtual void close();

	void setOption(const std::string opt) {
		_dbOption = opt;
	}
public:
	class Cursor;
	class Transaction;
public:
	SharedPtr<AbstractCursor> iterate();
	//SharedPtr<AbstractTransaction> CreateTransaction();
protected:
	virtual int32_t _get(VType& _return, const KType& key) const;

	virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const;

	virtual int32_t _put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen);

	virtual int32_t _remove( void* aKey, int aKeyLen);

	virtual bool _has(const KType& key);

	virtual int32_t _multiGet(KVMap& _return, const KList& keys) const;
protected:
	std::string _path;
	mutable leveldb::DB* _db;
	bool _isOpen;
	std::string _dbOption;
};

}} //namespace

#endif	/* SIMPLELEVELSTORAGE_H */

