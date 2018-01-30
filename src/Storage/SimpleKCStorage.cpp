#include <kcpolydb.h>
#include <Storage/SimpleKCStorage.h>

namespace openstars { namespace storage {

SimpleKCStorage::SimpleKCStorage() {}

SimpleKCStorage::SimpleKCStorage(const string& path)
: _path(path)
{
	_db = new PolyDB();
		
}

void SimpleKCStorage::initialize(const string& path) {
	_path = path;
	_db = new PolyDB();
}

SimpleKCStorage::~SimpleKCStorage() {
	if (_db.get() != NULL)
		_db->close();
}
void SimpleKCStorage::close() {
	if (_db.get() != NULL) {
		_db->close();
		_db = NULL;
	}
}
bool SimpleKCStorage::open() {
	bool result = _db->open(_path, DirDB::OCREATE | DirDB::OWRITER);
	if (!result) {
		std::cerr << "[KyotoCabinet] Error opening path " << _path << std::endl;
	}
	return result;
}
int32_t SimpleKCStorage::_get(VType& _return, const KType& key) const
{
	if (_db->get(key, &_return)) {
		return 0;
	} else {
		return -1;
	}
}
//Copy return value into outData
int32_t SimpleKCStorage::_get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const 
{
	size_t outLen = 0;
	char* data = _db->get((const char*)inKeyData, (size_t)keyLen, &outLen);
	if (data != NULL) {
		int copyLen = datalen > outLen ? outLen : datalen;
		::memcpy(outData, data, copyLen);
		return 0;
	}
	return -1;
}

int32_t SimpleKCStorage::_multiGet(KVMap& _return, const KList& keys) const {
	return _db->get_bulk(keys, &_return, true);	//true = atomic mode
}

int32_t SimpleKCStorage::_put(const void* inKeyData, const int& keyLen, 
				const void* inData, const int& datalen) 
{
	if (_db->set((const char*)inKeyData, keyLen, (const char*)inData, datalen)) {
		return 0;
	}
	return -1;
}

int32_t SimpleKCStorage::_remove(void* aKey, int aKeyLen) {
	if (_db->remove((const char*)aKey, aKeyLen)) {
		return 0;
	}
	return -1;
}

bool SimpleKCStorage::_has(const KType& key) {
	return _db->check(key);
}

////////////////// Cursor ///////////////
class SimpleKCStorage::Cursor : public AbstractCursor {
public:
	Cursor(SharedPtr<BasicDB> db_);

	~Cursor();

	virtual bool next(std::string& aKey, std::string& aVal);

	virtual void close();

protected:
	DB::Cursor* _cursor;	
};

SharedPtr<AbstractCursor> SimpleKCStorage::iterate() {
	return new Cursor(_db);
}

SimpleKCStorage::Cursor::Cursor(SharedPtr<BasicDB> db_) {
	_cursor = db_->cursor();
	_cursor->jump();
}
SimpleKCStorage::Cursor::~Cursor() {
	if (_cursor != NULL) {
		delete _cursor;
	}
}
void SimpleKCStorage::Cursor::close() {
	if (_cursor != NULL) {
		delete _cursor;
		_cursor = NULL;
	}
}
bool SimpleKCStorage::Cursor::next(std::string& aKey, std::string& aVal) {
	return _cursor->get(&aKey, &aVal, true);
}

}}