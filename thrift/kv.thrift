namespace cpp kv
namespace java org.storage.keyvalue
typedef string KType
typedef string VType

struct KVPair
{
    1: required KType first,
    2: required VType second,
}

typedef list<KVPair> KVList
typedef list<KType> KList

typedef map<KType,VType> KVMap

service KVDataService
{
	i32 put(1:KType key, 2:VType value),
        i32 multiPut(1:KVList keyval),
        i32 multiPutM(1:KVMap keysvals),
        
	VType get(1:KType key),
        KVList multiGet(1:KList keys),
        KVMap multiGetM(1:KList keys),

        i32 remove(1:KType key),
        i32 multiRemove(1:KList keys),

    // return false if data is existed 
	i32 add(1:KType key, 2:VType value),

    // overwrite existed data, fail if the key is not existed
	i32 update(1:KType key, 2:VType value),
}
