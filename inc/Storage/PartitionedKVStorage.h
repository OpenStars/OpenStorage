/* 
 * File:   PartitionedKVStorage.h
 * Author: anhn
 *
 * Created on October 15, 2012, 10:50 AM
 */

#ifndef PARTITIONEDKVSTORAGE_H
#define	PARTITIONEDKVSTORAGE_H

#include <Poco/NumberFormatter.h>
#include <Hashing/DefaultHasher.h>
#include <Poco/NumberParser.h>
#include <Poco/StringTokenizer.h>
#include <Poco/String.h>
#include <Poco/SharedPtr.h>
#include <Storage/AbstractKVStorage.h>


namespace Up { namespace Storage {
using std::string;
using std::vector;
using Poco::SharedPtr;
/**
 * Partition storage using default hash based load balancing method
 */
template<class _TStorage>
class PartitionedStorage : public _TStorage {
public:
	typedef ::Up::Hashing::DefaultHasher HasherType;
	typedef _TStorage TStorage;
	typedef typename TStorage::KType KType;
	typedef typename TStorage::VType VType;
	typedef typename TStorage::KVMap KVMap;
	typedef typename TStorage::KList KList;
public:
	//path=/tmp/kyoto;baseName=test;dbType=.kch;numPartition=1
	PartitionedStorage(string dbString);
	~PartitionedStorage();
	
	virtual void close();
	
	virtual bool open();
	
	SharedPtr<AbstractCursor> iterate();
protected:
	virtual SharedPtr<TStorage> getStorage(const KType& key) const;
	virtual SharedPtr<TStorage> getStorage(const void* kBuf_, int kSize_) const;
protected:
	virtual int32_t _get(VType& _return, const KType& key) const;

	virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const;

	virtual int32_t _put(const Poco::SharedPtr<AbstractTransaction>& trans, const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) ;
	
	virtual int32_t _remove(const Poco::SharedPtr<AbstractTransaction>& trans, void* aKey, int aKeyLen);

	virtual bool _has(const KType& key);

	virtual int32_t _multiGet(KVMap& _return, const KList& keys) const;
protected:
	int _numParts;
	string _dbString;
	string _path;
	string _baseName;
	string _dbType;
	string _dbOptions;
	vector<SharedPtr<TStorage> > _dbParts;
	size_t _partitionMask;
};

/////////////////////////////
template<class _TStorage>
PartitionedStorage<_TStorage>::PartitionedStorage(string dbString)
: _dbString(dbString)
{
	using Poco::StringTokenizer;
	//Default parameters
	_path= "/tmp/storage";
	_baseName = "test";
	_dbType = "";
	_numParts = 1;
	_dbOptions = "";

	StringTokenizer tkn(_dbString, ",", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
	StringTokenizer::Iterator it;
	for (it = tkn.begin(); it != tkn.end(); ++it) {
		size_t index = (*it).find('=');
		if (index == std::string::npos)
			continue;
		string name = (*it).substr(0, index);
		Poco::trimInPlace(name);
		string value = "";
		if (index < it->length() - 1)
			value = (*it).substr(index + 1);
		Poco::trimInPlace(value);
		
		if (name == "path") {
			_path = value;
		} else if (name == "baseName") {
			_baseName = value;
		} else if (name == "dbType") {
			_dbType = value;
		} else if (name == "partitions") {
			_numParts = Poco::NumberParser::parse(value);
		} else if (name == "dbOptions") {
			_dbOptions = value;
		}
	}
	cout << "Using path : " << _path << endl
		<< "Using base name : " << _baseName << endl
		<< "Using dbType : " << _dbType << endl
		<< "Using " << _numParts << " partitions" << endl
		<< "Using options: " << _dbOptions << endl << endl;
	
	//Adjust numParts in form of 2^n, mask = 2^n - 1
	size_t hash_mask = 1;
	while (hash_mask < this->_numParts) hash_mask <<= 1;
    --hash_mask;
    _partitionMask = hash_mask;
	_numParts = hash_mask + 1;
	
	_dbParts.resize(_numParts);	
	
}

template<class _TStorage>
PartitionedStorage<_TStorage>::~PartitionedStorage() {
	for (int i = 0; i < _numParts; ++i) {
		if (_dbParts[i].get() != NULL) {
			_dbParts[i]->close();
		}
	}
}

template<class _TStorage>
void PartitionedStorage<_TStorage>::close() {
	for (int i = 0; i < _numParts; ++i) {
		if (_dbParts[i].get() != NULL) {
			_dbParts[i]->close();
			_dbParts[i] = NULL;
		}
	}
}

template<class _TStorage>
bool PartitionedStorage<_TStorage>::open() {
	bool ret = true;
	for (int i = 0; i < _numParts; ++i) {
		ret = ret && _dbParts[i]->open();
	}
	return ret;
}

template<class _TStorage>
SharedPtr<AbstractCursor> PartitionedStorage<_TStorage>::iterate() {
	return NULL;
}

template<class _TStorage>
SharedPtr<_TStorage> PartitionedStorage<_TStorage>::getStorage(const KType& key) const {
	size_t aHash = HasherType::hashdata(key.data(), key.size());
    return _dbParts[ aHash & this->_partitionMask ];
}
template<class _TStorage>
SharedPtr<_TStorage> PartitionedStorage<_TStorage>::getStorage(const void* kBuf_, int kSize_) const {
	size_t aHash = HasherType::hashdata(kBuf_, kSize_);
    return _dbParts[ aHash & this->_partitionMask ];
}

////////////////////////////////

template<class _TStorage>
int32_t PartitionedStorage<_TStorage>::_get(VType& _return, const KType& key) const {
	SharedPtr<TStorage> storage = getStorage(key);
	if (storage)
		return storage->_get(_return, key);
	return -1;
}

template<class _TStorage>
int32_t PartitionedStorage<_TStorage>::_get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const {
	SharedPtr<TStorage> storage = getStorage(inKeyData, keyLen);
	if (storage)
		return storage->_get(inKeyData, keyLen, outData, datalen);
	return -1;
}

template<class _TStorage>
int32_t PartitionedStorage<_TStorage>::_put(const Poco::SharedPtr<AbstractTransaction>& trans, const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) {
	SharedPtr<TStorage> storage = getStorage(inKeyData, keyLen);
	if (storage)
		return storage->_put(trans, inKeyData, keyLen, inData, datalen);
	return -1;
}

template<class _TStorage>
int32_t PartitionedStorage<_TStorage>::_remove(const Poco::SharedPtr<AbstractTransaction>& trans, void* aKey, int aKeyLen) {
	SharedPtr<TStorage> storage = getStorage(aKey, aKeyLen);
	if (storage)
		return storage->_remove(trans, aKey, aKeyLen);
	return -1;
}

template<class _TStorage>
bool PartitionedStorage<_TStorage>::_has(const KType& key) {
	SharedPtr<TStorage> storage = getStorage(key);
	if (storage)
		return storage->_has(key);
	return false;
}

template<class _TStorage>
int32_t PartitionedStorage<_TStorage>::_multiGet(KVMap& _return, const KList& keys) const {
	typename KList::const_iterator it = keys.begin();
	for (it = keys.begin(); it != keys.end(); ++it) {
		VType val;
		int32_t r = _get(val, *it);
		if (r == 0)
			_return[*it] = val;
	}
}


}}	//namespace

#endif	/* PARTITIONEDKVSTORAGE_H */

