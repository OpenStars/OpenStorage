/* 
 * File:   KVStorageFactory.cpp
 * Author: trungthanh
 * 
 * Created on October 16, 2012, 3:02 PM
 */

#include "Storage/KVStorageFactory.h"
#include "Storage/KCStorage.h"
#include "Storage/LevelStorage.h"
#include "Storage/RemoteKVStorage.h"
#include "Storage/DistributedStorage.h"
#include "Storage/SharedMemStorage.h"
#include "Storage/FixedSizeSharedMemTable.h"
#include "Storage/BigsetRemoteKV.h"
#include "Storage/SnappyKVStorage.h"


#include "Distributed/RepBackendManager.h"
#include "Distributed/CHBackendManager.h"
#include "Hashing/CastingHasher.h"
#include "Hashing/DefaultHasher.h"
#include "Hashing/MurmurHasher.h"


#include "Poco/StringTokenizer.h"
#include "Poco/NumberParser.h"
#include "Poco/SharedPtr.h"
#include "Storage/RocksDBStorage.h"


#include <map>

namespace openstars { namespace storage{


KVStorageFactory::KVStorageFactory() {
}

KVStorageFactory::~KVStorageFactory() {
}

class KVStorageFactoryImpl{
public:

    
    static openstars::storage::AbstractKVStorage* createBigsetRemote( std::map < std::string, std::string> & aOptions){
        std::string aHost = aOptions["host"];
        int aPort = Poco::NumberParser::parse(aOptions["port"]);

	std::string zkServer = aOptions["zkservers"];
	for (size_t aIndex = 0; aIndex < zkServer.length(); aIndex++)
	    if (zkServer[aIndex] == '_')
		zkServer[aIndex] =',';
	
	std::string zkBasePath = aOptions["dbpath"];
	
        
        int aBigSetID = Poco::NumberParser::parse(aOptions["bigsetid"]);
        
        if ( (aPort <= 0 || aHost =="" ) && (zkServer == "" || zkBasePath =="") )
            return NULL;
        openstars::storage::BigsetRemoteKV* aDb = new openstars::storage::BigsetRemoteKV(aHost, aPort, aBigSetID);
	
	/* load configuration from zk*/
	if (zkServer.length() > 0 && zkBasePath.length() > 0)
	    aDb->loadEndpointsFromZK(zkServer, zkBasePath);
	
	return aDb;
    }

    static openstars::storage::AbstractKVStorage* createRemote( std::map < std::string, std::string> & aOptions){
        std::string aHost = aOptions["host"];
        int aPort = Poco::NumberParser::parse(aOptions["port"]);

	std::string zkServer = aOptions["zkservers"];
	for (size_t aIndex = 0; aIndex < zkServer.length(); aIndex++)
	    if (zkServer[aIndex] == '_')
		zkServer[aIndex] =',';
	
	std::string zkBasePath = aOptions["dbpath"];
	
        if ( (aPort <= 0 || aHost =="" ) && (zkServer == "" || zkBasePath =="") )
            return NULL;
        openstars::storage::RemoteKVStorage* aDb = new openstars::storage::RemoteKVStorage(aHost, aPort);
	
	/* load configuration from zk*/
	if (zkServer.length() > 0 && zkBasePath.length() > 0)
	    aDb->loadEndpointsFromZK(zkServer, zkBasePath);
	
	return aDb;
    }
    
    
    static openstars::storage::AbstractKVStorage* createKC(const std::string & aOptions){
        openstars::storage::KCStorage* aDb = new openstars::storage::KCStorage(aOptions);
        aDb->open();
        return aDb;
    }
	
	
    static openstars::storage::AbstractKVStorage* createLevelStorage(const std::string & aOptions){
		openstars::storage::LevelStorage* aDb = new openstars::storage::LevelStorage(aOptions);
        aDb->open();
		return aDb;
    }
    
    static openstars::storage::AbstractKVStorage* createRocksdbStorage(const std::string & aOptions){
		openstars::storage::RocksDBStorage* aDb = new openstars::storage::RocksDBStorage(aOptions);
        aDb->open();
		return aDb;
    }
    
    static openstars::distributed::BackendManager* getBackendManager(const std::string& zkServer,
	const std::string& zkBasePath,
	const std::string& distributedType , 
	const std::string& hashType)
    {
	std::string aKey = zkServer + zkBasePath + distributedType + hashType;
	if (backendManagers[aKey])
	    return backendManagers[aKey];
	// tạo mới 
	openstars::distributed::BackendManager* aMngr = NULL;
	if (distributedType == "consistent-hash")
	    aMngr = new  openstars::distributed::CHBackendManager();
	else 
	    aMngr = new openstars::distributed::RepBackendManager();

	if (hashType=="casting")
	{
	    aMngr->setHasher( new openstars::hashing::CastingHasher  );
	} 
	else if (hashType == "murmur")
	{
	    aMngr->setHasher( new openstars::hashing::MurmurHasher );
	}
	else if (hashType =="default") 
	{
	    aMngr->setHasher( new openstars::hashing::DefaultHasher );
	}
	
	if (zkServer.length() > 0 && zkBasePath.length() > 0)
	    aMngr->loadZkConfig(zkServer, zkBasePath);
	
	
	backendManagers[aKey] = aMngr;
	return aMngr;
	
	
    }

    static openstars::storage::AbstractKVStorage* createDistributed( std::map < std::string, std::string> & aOptions){

	std::string zkServer = aOptions["zkservers"];
	for (size_t aIndex = 0; aIndex < zkServer.length(); aIndex++)
	    if (zkServer[aIndex] == '_')
		zkServer[aIndex] =',';
	
	std::string zkBasePath = aOptions["dbpath"];
	
        if ( (zkServer == "" || zkBasePath =="") )
            return NULL;
	
	std::string distributedType = aOptions["disttype"];
	
	std::string hashType = aOptions["hashtype"];	
	
	openstars::distributed::BackendManager* aMngr = getBackendManager(zkServer, zkBasePath,distributedType , hashType);
	
        openstars::storage::DistributedStorage* aDb = new openstars::storage::DistributedStorage(aMngr);
	
	
	return aDb;
    }

    static ::FixedSizeSharedMemTable* createSharedMemtable( std::map < std::string, std::string> & aOptions)
    {
	// get value size
	int valueSize = 1;
        if (aOptions["valuesize"] != "")
            valueSize = Poco::NumberParser::parse(aOptions["valuesize"] );
	
	Poco::UInt64 offset = 0;
        if (aOptions["offset"] != "")
            offset = Poco::NumberParser::parse64(aOptions["offset"] );
	
	Poco::UInt64 maxItem = 1000000;
        if (aOptions["maxItems"] != "")
            maxItem = Poco::NumberParser::parse64(aOptions["maxItems"] );
	cout<<"create FixedSizeSharedMemTable valuesize: "<<valueSize<<" offset: " <<offset<<" maxItem: "<<maxItem<<endl;
	return new FixedSizeSharedMemTable(valueSize, offset, maxItem);
	
    }

    static openstars::storage::AbstractKVStorage* createSHM( std::map < std::string, std::string> & aOptions)
    {
	std::string dbName = aOptions["dbname"];
	if (dbName.length() == 0)
	    dbName = "notsetdbname";
	FixedSizeSharedMemTable* aTable = createSharedMemtable(aOptions);
	openstars::storage::SharedMemStorage* aDb = new openstars::storage::SharedMemStorage(aTable);
	aDb->openShm(dbName);
	return aDb;	
    }
    
    static openstars::storage::AbstractKVStorage* createFileMapping( std::map < std::string, std::string> & aOptions)
    {
	std::string env = aOptions["env"];
	if (env.length() == 0)
	    return NULL;
	

	std::string dbName = aOptions["dbname"];

	if (dbName.length() == 0)
	    dbName = "notsetdbname";

	cout<<"create file mapping with env "<<env<<" db name: "<<dbName<<endl;
	
	FixedSizeSharedMemTable* aTable = createSharedMemtable(aOptions);
	openstars::storage::SharedMemStorage* aDb = new openstars::storage::SharedMemStorage(aTable);
	aDb->openFileMapping(env, dbName);
	return aDb;	
    }
    
    static openstars::storage::AbstractKVStorage* createSmartSHMMapping( std::map < std::string, std::string> & aOptions)
    {
	std::string env = aOptions["env"];
	if (env.length() == 0)
	    return NULL;
	

	std::string dbName = aOptions["dbname"];
	std::string shmName = aOptions["shmname"];

	if (dbName.length() == 0)
	    dbName = "notsetdbname";

	cout<<"create file mapping with env "<<env<<" db name: "<<dbName<<endl;
	
	FixedSizeSharedMemTable* aShmTable = createSharedMemtable(aOptions);
	FixedSizeSharedMemTable* aFmTable = createSharedMemtable(aOptions);
	openstars::storage::SmartSharedMemStorage* aDb = new openstars::storage::SmartSharedMemStorage(aShmTable , aFmTable);
	//aDb->openFileMapping(env, dbName);
        aDb->open(shmName, env, dbName);
	return aDb;	
    }
        
    
private:
    static std::map< std::string , Poco::SharedPtr< openstars::distributed::BackendManager > > backendManagers;

};

// khai báo biến static lưu trữ ánh xạ từ key sang BackendManager 
std::map< std::string , Poco::SharedPtr< openstars::distributed::BackendManager > > KVStorageFactoryImpl::backendManagers;

openstars::storage::AbstractKVStorage* createKVStorageByType(const std::string& aType, 
        std::map < std::string, std::string>& aMap, const std::string& creatingOption)
{

    if (aType == "")
        return NULL;
    
    if (aType =="remote"){
        return KVStorageFactoryImpl::createRemote(aMap);
    }
    
    if (aType == "bigset")
    {
        return KVStorageFactoryImpl::createBigsetRemote(aMap);
    }
    
    if (aType == "kc"){
        return KVStorageFactoryImpl::createKC(creatingOption);
    }
	
    if (aType == "leveldb"){
        return KVStorageFactoryImpl::createLevelStorage(creatingOption);
    }
    
    if (aType == "rocksdb"){
        return KVStorageFactoryImpl::createRocksdbStorage(creatingOption);
    }
        
    if (aType == "distributed")
	return KVStorageFactoryImpl::createDistributed(aMap);

    if (aType == "filemapping")
	return KVStorageFactoryImpl::createFileMapping(aMap);
    
    if (aType == "shm")
	return KVStorageFactoryImpl::createSHM(aMap);

    if (aType == "smartshmmapping" || aType == "smartshm")
	return KVStorageFactoryImpl::createSmartSHMMapping(aMap);    
}

openstars::storage::AbstractKVStorage* KVStorageFactory::createStorage(
    const std::string& creatingOption , std::string& name , int& rwmode ){
    Poco::StringTokenizer aStk(creatingOption, ",", Poco::StringTokenizer::TOK_TRIM);
    
    /*Put options to map*/
    std::map < std::string, std::string> aMap;
    for (size_t aIndex = 0; aIndex < aStk.count(); aIndex++ ){
        std::string aOption = aStk[aIndex];
        cout<<aOption<<endl;
        Poco::StringTokenizer aStk2(aOption, "=",Poco::StringTokenizer::TOK_TRIM);
        if (aStk2.count() <2){
            continue;
        }
        aMap[aStk2[0] ] = aStk2[1];
        
    }
    
    rwmode = 0;
    std::string aType = aMap["type"];
    name = aMap["name"];
    if (aMap.find("readable") != aMap.end() ){
        if (aMap["readable"] =="true")
            rwmode |= openstars::storage::ERead;
        if (aMap["writable"] == "true"){
            rwmode |= openstars::storage::EWrite;
        }
    }
    
    openstars::storage::AbstractKVStorage* aStorage 
            = createKVStorageByType (aType, aMap, creatingOption);
    if (aMap["snappykv"]=="true" || aMap["snappywrapper"]=="true" )
        aStorage = new openstars::storage::SnappyKVStorage(aStorage);
    cout<<"OpenStorage created "<<aType<<endl;
    return aStorage;
    
}


}}