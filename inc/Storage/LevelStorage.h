/* 
 * File:   LevelStorage.h
 * Author: anhn
 *
 * Created on October 16, 2012, 11:30 PM
 */

#ifndef LEVELSTORAGE_H
#define	LEVELSTORAGE_H

#include <string>
#include <Storage/SimpleLevelStorage.h>
#include <Hashing/DefaultHasher.h>

namespace openstars { namespace storage {

//partitioned leveldb storage 
    
class LevelStorage : public AbstractKVStorage {
public:
	typedef openstars::hashing::DefaultHasher HasherType;
	class Cursor;
public:
/**
 * Hash based partitioned LevelDb
 * 
 * @param dbString Storage config string
 * @example 
 * path=/tmp/leveldb,baseName=test,partitions=1
 * 
 * Default param values if omitted: path = /tmp/leveldb, baseName = test, dbType empty, partitions = 1, dbOptions empty
 */
	LevelStorage(const std::string& dbString);
	virtual ~LevelStorage();
	
	virtual bool open();
	
	virtual void close();
	
	/**
	 * Get Cursor to iterate through data
     * @return 
     */
	SharedPtr<AbstractCursor> iterate();
protected:
	virtual SharedPtr<SimpleLevelStorage> getStorage(const KType& key) const;
	virtual SharedPtr<SimpleLevelStorage> getStorage(const void* kBuf_, int kSize_) const;
protected:
	virtual int32_t _get(VType& _return, const KType& key) const;

	virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const;

	virtual int32_t _put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) ;
	
	virtual int32_t _remove(void* aKey, int aKeyLen);

	virtual bool _has(const KType& key);

	virtual int32_t _multiGet(KVMap& _return, const KList& keys) const;
protected:
	bool _isOpen;
	size_t _numParts;
	std::string _dbString;
	std::string _path;
	std::string _baseName;
	std::string _dbType;
	std::string _dbOptions;
	std::vector<SharedPtr<SimpleLevelStorage> > _dbParts;
	size_t _partitionMask;
};

typedef LevelStorage LevelDBStorage;

}}	//namespace

#endif	/* LEVELSTORAGE_H */

