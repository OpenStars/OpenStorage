/* 
 * File:   RemoteKVStorage.h
 * Author: kienpt
 *
 * Created on September 16, 2010, 8:34 AM
 */

#ifndef CREMOTEKVSTORAGE_H
#define	CREMOTEKVSTORAGE_H

#include "Storage/AbstractKVStorage.h"
#include <string>
#include "EndpointManager.h"

//Todo: using nonblocking client socket.
namespace openstars { namespace storage{
    
class RemoteKVStorage : public openstars::storage::AbstractKVStorage {
public:
    //RemoteKVStorage();
    RemoteKVStorage(const std::string& strServerIP, int nPort);
protected:
    virtual int32_t _put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) ;
		 // should be overridden

    virtual int32_t _get(VType &_return, const KType &key) const;
    virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const;
    virtual int32_t _multiGet(KVMap &_return, const KList &keys) const;

    int32_t _multiPut(const AbstractKVStorage::KVMap& keyvals);

    int32_t _remove(const KType &key);

public:
    virtual ~RemoteKVStorage();

public:
    int32_t put(const KType &key, const VType &data);
    
    /*
     * of date value of existing key, error if it is not existed
     */
    virtual int32_t update(const KType &key, const VType &data);

    /*
     * add new key-value pair, error if it is already existed
     */
    virtual int32_t add(const KType &key, const VType &data);        
    
public:
    void changeHostPort(const std::string& strServerIP, int nPort);
    void loadEndpointsFromZK(const std::string& zkServer, const std::string& zkBasePath);
private:
    RemoteKVStorage(const RemoteKVStorage& orig);
    
    EndpointManager _endpointManager;
};

} }

#endif	/* CREMOTEKVSTORAGE_H */


