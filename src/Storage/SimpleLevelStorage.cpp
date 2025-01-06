#include <Storage/SimpleLevelStorage.h>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>

#include <Poco/StringTokenizer.h>
#include <Poco/String.h>
#include <Poco/File.h>
#include <Poco/NumberParser.h>
#include <Poco/NumberFormatter.h>

using namespace Poco;
namespace openstars { namespace storage {
	
SimpleLevelStorage::SimpleLevelStorage(const std::string& path)
: _path(path), _db(nullptr), _isOpen(false)
{		
}
SimpleLevelStorage::~SimpleLevelStorage() {
	close();
}

bool SimpleLevelStorage::open() {
	if (_isOpen)
		return true;
	leveldb::Options options;
	options.create_if_missing = true;
        ///
	StringTokenizer tkn(this->_dbOption, "#", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
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
                if (name == "cachesizemb"){
                    try {
                        size_t sizeMB = Poco::NumberParser::parse(value);
                        if (sizeMB <= 0)
                            throw 0;
                        options.write_buffer_size = sizeMB* 1024 * 1024;
                    } catch(...)
                    {
                        
                    }
                }
        }        
        ///
	leveldb::Status status = leveldb::DB::Open(options, _path, &_db);
	if (!status.ok()) {
		std::cerr << "[LevelDB] Error opening path " << _path << ": " << status.ToString() << std::endl;
		return false;
	}
	_isOpen = true;
	return true;
}
void SimpleLevelStorage::close() {
	if (_db != NULL) {            
		delete _db;
		_db = NULL;
		_isOpen = false;
	}
}

int32_t SimpleLevelStorage::_get(VType& _return, const KType& key) const
{
	leveldb::Slice slKey(key.data(), key.length());
	leveldb::Status s = _db->Get(leveldb::ReadOptions(), slKey, &_return);
	if (s.ok()) {
		return 0;
	} else {
		//cerr << "Error : " << s.ToString() << endl;
		return -1;
	}
}

//Copy max dataLen bytes of value into outData
int32_t SimpleLevelStorage::_get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const 
{
	leveldb::Slice slKey((const char*)inKeyData, keyLen);
	std::string value;
	leveldb::Status s = _db->Get(leveldb::ReadOptions(), slKey, &value);
	if (s.ok()) {
		size_t outLen = value.length();
		int copyLen = datalen > outLen ? outLen : datalen;
		::memcpy(outData, value.data(), copyLen);
		return 0;
	}
	return -1;
}

int32_t SimpleLevelStorage::_multiGet(KVMap& _return, const KList& keys) const {
	//not implemented yet
	return 0;
}

bool SimpleLevelStorage::_has(const KType& key) {
	leveldb::Slice slKey(key.data(), key.length());
	std::string value;
	leveldb::Status s = _db->Get(leveldb::ReadOptions(), slKey, &value);
	return s.ok();
}

/////// Iteration cursor ////////////

class SimpleLevelStorage::Cursor : public AbstractCursor {
public:
	Cursor(leveldb::DB* db_);

	~Cursor();

	virtual bool next(std::string& aKey, std::string& aVal);

	virtual void close();

protected:
	leveldb::Iterator* _iter;	
};

SharedPtr<AbstractCursor> SimpleLevelStorage::iterate() {
	return new Cursor(_db);
}

SimpleLevelStorage::Cursor::Cursor(leveldb::DB* db_)
:_iter(db_->NewIterator(leveldb::ReadOptions()))
{
	_iter->SeekToFirst();
}
SimpleLevelStorage::Cursor::~Cursor() {
	if (_iter != NULL) {
		delete _iter;
	}
}
void SimpleLevelStorage::Cursor::close() {
	if (_iter != NULL) {
		delete _iter;
		_iter = NULL;
	}
};
bool SimpleLevelStorage::Cursor::next(std::string& aKey, std::string& aVal) {
	if (!_iter->Valid()) {
		return false;
	}
	aKey = _iter->key().ToString();
	aVal = _iter->value().ToString();
	
	_iter->Next();
	
	return true;
}

/////////// Transaction support //////////////
class SimpleLevelStorage::Transaction {
public:
	Transaction(leveldb::DB* db_) : _db(db_), _began(false) {}
	virtual bool begin() {_began = true; return true;}
	virtual bool commit() {return true;}
	virtual bool rollBack() {_began = false;return true;}
	leveldb::WriteBatch* getBatch() {
		return &_batch;
	}
	bool isBegun() {
		return _began;
	}
protected:
	leveldb::DB* _db;
	leveldb::WriteBatch _batch;
	bool _began;
};

//////////////////////////////////////////////////

int32_t SimpleLevelStorage::_put(const void* inKeyData, const int& keyLen, 
				const void* inData, const int& datalen) 
{
	leveldb::Slice key((const char*)inKeyData, keyLen);
	leveldb::Slice value((const char*)inData, datalen);
	leveldb::Status s;
        s = _db->Put(leveldb::WriteOptions(), key, value);

	if (s.ok()) {
		return 0;
	}
	return -1;
}

int32_t SimpleLevelStorage::_remove( void* aKey, int aKeyLen) {
	leveldb::Slice key((const char*)aKey, aKeyLen);
	leveldb::Status s;
        s = _db->Delete(leveldb::WriteOptions(), key);

	if (s.ok()) {
		return 0;
	}
	return -1;
}


}}	//namespace