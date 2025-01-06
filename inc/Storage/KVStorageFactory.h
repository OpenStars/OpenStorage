/* 
 * File:   KVStorageFactory.h
 * Author: trungthanh
 *
 * Created on October 16, 2012, 3:02 PM
 */

#ifndef KVSTORAGEFACTORY_H
#define	KVSTORAGEFACTORY_H

#include "Storage/AbstractKVStorage.h"
#include "Storage/AbstractStorageFactory.h"
#include <Poco/SharedPtr.h>

namespace openstars { namespace storage{
    

class KVStorageFactory : public AbstractStorageFactory{
public:
    KVStorageFactory();
    virtual ~KVStorageFactory();
public:
    virtual openstars::storage::AbstractKVStorage* createStorage(const std::string& creatingOption , std::string& name , int& rwmode);
};


}}
#endif	/* KVSTORAGEFACTORY_H */

