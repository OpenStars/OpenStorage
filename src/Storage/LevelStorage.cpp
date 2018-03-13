#include <Storage/LevelStorage.h>

#include <Poco/StringTokenizer.h>
#include <Poco/String.h>
#include <Poco/File.h>
#include <Poco/NumberParser.h>
#include <Poco/NumberFormatter.h>


namespace openstars { namespace storage {

/**
 * Hash based partitioned LevelDb
 * 
 * @param dbString Storage config string
 * @example 
 * path=/tmp/leveldb,baseName=test,partitions=1
 * 
 * Default param values if omitted: path = /tmp/leveldb, baseName = test, dbType empty, partitions = 1, dbOptions empty
 */
LevelStorage::LevelStorage(const std::string& dbString)
: _isOpen(false)
,_numParts(1)
,_dbString(dbString)
{
	using Poco::StringTokenizer;
	//Default parameters
	_path= "/tmp/leveldb";
	_baseName = "test";
	_numParts = 1;
	_dbOptions = "";

	StringTokenizer tkn(_dbString, ",", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
	StringTokenizer::Iterator it;
	for (it = tkn.begin(); it != tkn.end(); ++it) {
		size_t index = (*it).find('=');
		if (index == std::string::npos)
			continue;
		std::string name = (*it).substr(0, index);
		Poco::trimInPlace(name);
		std::string value = "";
		if (index < it->length() - 1)
			value = (*it).substr(index + 1);
		Poco::trimInPlace(value);
		
		if (name == "path") {
			_path = value;
		} else if (name == "baseName") {
			_baseName = value;
		} else if (name == "partitions") {
			_numParts = Poco::NumberParser::parse(value);
		} else if (name == "dbOptions") {
			_dbOptions = value;
		}
	}
	std::cout << "Using path : " << _path
		<< "\nUsing base name : " << _baseName
		<< "\nUsing " << _numParts << " partitions"
		<< "\nUsing options: " << _dbOptions  << std::endl;
	
	//Adjust numParts in form of 2^n, mask = 2^n - 1
	size_t hash_mask = 1;
	while (hash_mask < this->_numParts) hash_mask <<= 1;
    --hash_mask;
    _partitionMask = hash_mask;
	_numParts = hash_mask + 1;
	
	_dbParts.resize(_numParts);	
}

LevelStorage::~LevelStorage() {
	close();
}

bool LevelStorage::open() {
	if (_isOpen)
		return true;
	bool ret = true;
	
	/*create directories*/
	Poco::File aFile(_path);
	aFile.createDirectories();
	
	for (int i = 0; i < _numParts; ++i) {
		std::string dbPath = _path + "/" + _baseName + "_" + Poco::NumberFormatter::format0(i, 3);
		_dbParts[i] = new SimpleLevelStorage(dbPath);
                _dbParts[i]->setOption(_dbOptions);
	}		
	for (int i = 0; i < _numParts; ++i) {
		ret = ret && _dbParts[i]->open();
	}
	_isOpen = true;
	return ret;
}
void LevelStorage::close() {
	for (int i = 0; i < _numParts; ++i) {
		if (_dbParts[i].get() != NULL) {
			_dbParts[i]->close();
			_dbParts[i] = NULL;
		}
	}
	_isOpen = false;
}

SharedPtr<SimpleLevelStorage> LevelStorage::getStorage(const KType& key) const {
	size_t aHash = HasherType::hashdata(key.data(), key.size());
    return _dbParts[ aHash & this->_partitionMask ];
}

SharedPtr<SimpleLevelStorage> LevelStorage::getStorage(const void* kBuf_, int kSize_) const {
	size_t aHash = HasherType::hashdata(kBuf_, kSize_);
    return _dbParts[ aHash & this->_partitionMask ];
}

////////////////////////////////

int32_t LevelStorage::_get(VType& _return, const KType& key) const
{
	SharedPtr<SimpleLevelStorage> storage = getStorage(key);
	if (storage)
		return storage->_get(_return, key);
	return -1;
}

//Copy return value into outData
int32_t LevelStorage::_get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const 
{
	SharedPtr<SimpleLevelStorage> storage = getStorage(inKeyData, keyLen);
	if (storage)
		return storage->_get(inKeyData, keyLen, outData, datalen);
	return -1;
}

int32_t LevelStorage::_multiGet(KVMap& _return, const KList& keys) const {
	KList::const_iterator it = keys.begin();
	for (it = keys.begin(); it != keys.end(); ++it) {
		VType val;
		int32_t r = _get(val, *it);
		if (r == 0)
			_return[*it] = val;
	}
	return 0;
}

int32_t LevelStorage::_put(const void* inKeyData, const int& keyLen, 
				const void* inData, const int& datalen) 
{
	SharedPtr<SimpleLevelStorage> storage = getStorage(inKeyData, keyLen);
	if (storage)
		return storage->_put(inKeyData, keyLen, inData, datalen);
	return -1;
}

int32_t LevelStorage::_remove( void* aKey, int aKeyLen) {
	SharedPtr<SimpleLevelStorage> storage = getStorage(aKey, aKeyLen);
	if (storage)
		return storage->_remove(aKey, aKeyLen);
	return -1;
}

bool LevelStorage::_has(const KType& key) {
	SharedPtr<SimpleLevelStorage> storage = getStorage(key);
	if (storage)
		return storage->_has(key);
	return false;
}

///////////////// Cursor //////////////

class LevelStorage::Cursor : public AbstractCursor {
public:
	Cursor(std::vector<SharedPtr<SimpleLevelStorage> >& parts);

	virtual ~Cursor(){};
	virtual bool next(std::string& aKey, std::string& aVal);

	virtual void close();

protected:
	int partitionIndex;
	SharedPtr<AbstractCursor> _currentCursor;
	std::vector<SharedPtr<SimpleLevelStorage> >& _partitions;
};

SharedPtr<AbstractCursor> LevelStorage::iterate() {
	return new Cursor(_dbParts);
}

LevelStorage::Cursor::Cursor(std::vector<SharedPtr<SimpleLevelStorage> >& parts) 
:  partitionIndex(0), _currentCursor(), _partitions(parts)
{
	_currentCursor = _partitions[partitionIndex]->iterate();
}

void LevelStorage::Cursor::close() {
	_currentCursor->close();
}

bool LevelStorage::Cursor::next(std::string& aKey, std::string& aVal) {
	bool result = _currentCursor->next(aKey, aVal);
	if (result)
		return true;
	while (partitionIndex < _partitions.size() - 1) {
		//Close current, try next partition
		_currentCursor->close();
		++partitionIndex;
		_currentCursor = _partitions[partitionIndex]->iterate();
		bool r = _currentCursor->next(aKey, aVal);
		if (r) {
			return true;
		}
	}
	return false;
}

}}
