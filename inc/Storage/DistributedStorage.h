/* 
 * File:   DistributedStorage.h
 * Author: trungthanh
 *
 * Created on March 26, 2013, 11:14 PM
 */

#ifndef DISTRIBUTEDSTORAGE_H
#define	DISTRIBUTEDSTORAGE_H

#include "Storage/AbstractKVStorage.h"
#include <string>
#include "Distributed/BackendManager.h"

//Todo: using nonblocking client socket.
namespace openstars { namespace storage{

//Remote KV Storage using BackendManager for managing host/port 
//we can use this for consistent hash writing/ reading 
class DistributedStorage : public openstars::storage::AbstractKVStorage
{
public:
    DistributedStorage(openstars::distributed::BackendManager* backendMngr);
    virtual ~DistributedStorage();
private:
    DistributedStorage(const DistributedStorage& orig);
    
public:
    /*
     * of date value of existing key, error if it is not existed
     */
    virtual int32_t update(const KType &key, const VType &data);

    /*
     * add new key-value pair, error if it is already existed
     */
    virtual int32_t add(const KType &key, const VType &data);        
    
    
protected:
    
    virtual int32_t _put(const KType &key, const VType &data);
    
    virtual int32_t _put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) ;
		 // should be overridden

    virtual int32_t _get(VType &_return, const KType &key) const;
    virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const;
    virtual int32_t _multiGet(KVMap &_return, const KList &keys) const;

    int32_t _multiPut(const AbstractKVStorage::KVMap& keyvals);

    int32_t _remove(const KType &key);
    
protected:
    openstars::distributed::BackendManager* _backendMngr;
};

} }
#endif	/* DISTRIBUTEDSTORAGE_H */

