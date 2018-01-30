/* 
 * File:   KVStorageFactory.cpp
 * Author: trungthanh
 * 
 * Created on October 16, 2012, 3:02 PM
 */

#include "Storage/KVStorageFactory.h"
#include "Storage/KCStorage.h"
#include "Storage/LevelStorage.h"
//#include "Storage/ZDB2Storage.h"
#include "Storage/RemoteKVStorage.h"
#include "Storage/DistributedStorage.h"
#include "Storage/SharedMemStorage.h"
#include "Storage/FixedSizeSharedMemTable.h"
#include "Storage/BigsetRemoteKV.h"
//#include "Storage/ManagedIFlatStorage.h"


#include "Distributed/RepBackendManager.h"
#include "Distributed/CHBackendManager.h"
#include "Hashing/CastingHasher.h"
#include "Hashing/DefaultHasher.h"
#include "Hashing/MurmurHasher.h"


#include "Poco/StringTokenizer.h"
#include "Poco/NumberParser.h"
#include "Poco/SharedPtr.h"


#include <map>

namespace openstars { namespace storage{


KVStorageFactory::KVStorageFactory() {
}

KVStorageFactory::~KVStorageFactory() {
}

class KVStorageFactoryImpl{
public:
//    static openstars::storage::AbstractKVStorage* createManagedIFlat( std::map < std::string, std::string> & aOptions){
//
//        cout<<"prepare creating ManagedIFlatStorage "<<endl;
//        
//        size_t blockSize = Poco::NumberParser::parse(aOptions["blocksize"]);
//        size_t maxNumStorage = Poco::NumberParser::parse(aOptions["numactivedb"]);
//        bool isStupid = Poco::NumberParser::parseBool(aOptions["stupid"]);
//	std::string dbPath = aOptions["dbpath"];
//	std::string dbName = aOptions["dbname"];
//        size_t partitions = Poco::NumberParser::parse(aOptions["partitions"]);
//        bool appendOnly = Poco::NumberParser::parseBool(aOptions["appendonly"]);
//        int32_t reservedSize = Poco::NumberParser::parse(aOptions["reservedsize"]);
//
//        cout<<"creating ManagedIFlatStorage "<<endl;
//
//        openstars::storage::ManagedIFlatStorage* aDb = new openstars::storage::ManagedIFlatStorage(
//                blockSize, maxNumStorage, isStupid, 
//                dbPath, dbName, ".flat", 
//                partitions, appendOnly, reservedSize );
//	
//
//        cout<<" create ok "<<endl;
//	
//	return aDb;
//    }
    
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
    
//    static openstars::storage::AbstractKVStorage* createZDB2( std::map < std::string, std::string> & aOptions){
//        
//        int numPartition = 1;
//        
//        if (aOptions["partitions"] != "")
//            numPartition = Poco::NumberParser::parse(aOptions["partitions"] );
//        
//        
//        std::string zdb2Dir = aOptions[ "env"];
//        std::string zdb2Name =  aOptions["dbname"] ; //file name
//        if (zdb2Dir == "" || zdb2Name == "")
//            return NULL;
//        
//        
//        std::string zdb2TableType = aOptions["tabletype"]; // file name
//        if (zdb2TableType=="")
//            zdb2TableType = "I64GTable";
//
//        int zdb2AppendOnly = 0;
//        if (aOptions["appendonly"] != "")
//            zdb2AppendOnly = Poco::NumberParser::parse(aOptions["appendonly"]);
//        
//        int zdb2ReservedSize = 1024;
//        if (aOptions["reservedsize"] != "")
//            zdb2ReservedSize = Poco::NumberParser::parse(aOptions["reservedsize"]);
//
//
//
//        openstars::storage::ZDB2Storage* pZDB2 = new openstars::storage::ZDB2Storage(
//                    zdb2Dir
//                    , zdb2Name
//                    ,".zdb2"
//                    , numPartition
//                    , true );
//
//        pZDB2->autoOpen(zdb2TableType);
//
//        pZDB2->set_params(zdb2AppendOnly, zdb2ReservedSize);
//        cout<<"appendonly:"<<zdb2AppendOnly<<endl;
//        
//        return pZDB2;
//    }
    
//    static openstars::storage::AbstractKVStorage* createIFlat( std::map < std::string, std::string> & aOptions){
//        
//        int numPartition = 1;
//        
//        if (aOptions["partitions"] != "")
//            numPartition = Poco::NumberParser::parse(aOptions["partitions"] );
//        
//        
//        std::string env = aOptions[ "env"];
//        std::string dbName =  aOptions["dbname"] ; //file name
//        if (env == "" || dbName == "")
//            return NULL;
//        
//        
//        int appendOnly = 0;
//        if (aOptions["appendonly"] != "")
//            appendOnly = Poco::NumberParser::parse(aOptions["appendonly"]);
//
//        int useMem = 0;
//        if (aOptions["usemem"] != "")
//            useMem = Poco::NumberParser::parse(aOptions["usemem"]);
//
//        int reservedSize = 1024;
//        if (aOptions["reservedsize"] != "")
//            reservedSize = Poco::NumberParser::parse(aOptions["reservedsize"]);
//
//	Poco::Int64 minItem = 0;
//        if (aOptions["offset"] != "")
//            minItem = Poco::NumberParser::parse64(aOptions["offset"]);
//	
//	Poco::Int64 maxNumItem = 100000000;
//        if (aOptions["maxItems"] != "")
//            maxNumItem = Poco::NumberParser::parse64(aOptions["maxItems"]);
//
//
//        openstars::storage::IFlatStorage* pDB = new openstars::storage::IFlatStorage(
//		env
//		, dbName
//		,".flat"
//		, numPartition
//		, minItem
//		, maxNumItem
//		, appendOnly
//		, reservedSize
//                , useMem
//		);
//
//        pDB->open();
//
//        cout<<"appendonly:"<<appendOnly<<endl;
//        
//        return pDB;
//    }
    
    
//    static openstars::storage::AbstractKVStorage* createSmartIFlat( std::map < std::string, std::string> & aOptions){
//        
//        int numPartition = 1;
//        
//        if (aOptions["partitions"] != "")
//            numPartition = Poco::NumberParser::parse(aOptions["partitions"] );
//        
//        
//        std::string env = aOptions[ "env"];
//        std::string dbName =  aOptions["dbname"] ; //file name
//        if (env == "" || dbName == "")
//            return NULL;
//        
//        
//        int appendOnly = 0;
//        if (aOptions["appendonly"] != "")
//            appendOnly = Poco::NumberParser::parse(aOptions["appendonly"]);
//
////        int useMem = 0;
////        if (aOptions["usemem"] != "")
////            useMem = Poco::NumberParser::parse(aOptions["usemem"]);
//
//        int reservedSize = 1024;
//        if (aOptions["reservedsize"] != "")
//            reservedSize = Poco::NumberParser::parse(aOptions["reservedsize"]);
//
//	Poco::Int64 minItem = 0;
//        if (aOptions["offset"] != "")
//            minItem = Poco::NumberParser::parse64(aOptions["offset"]);
//	
//	Poco::Int64 maxNumItem = 100000000;
//        if (aOptions["maxItems"] != "")
//            maxNumItem = Poco::NumberParser::parse64(aOptions["maxItems"]);
//
//
//        openstars::storage::SmartIflatStorage* pDB = new openstars::storage::SmartIflatStorage(
//		env
//		, dbName
//		,".flat"
//		, numPartition
//		, minItem
//		, maxNumItem
//		, appendOnly
//		, reservedSize                    
//		);
//
//        pDB->open();
//
//        cout<<"appendonly:"<<appendOnly<<endl;
//        
//        return pDB;
//    }    
    
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

openstars::storage::AbstractKVStorage* KVStorageFactory::createStorage(const std::string& creatingOption , std::string& name , int& rwmode ){
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
    
    if (aType == "")
        return NULL;
    
    if (aType =="remote"){
        return KVStorageFactoryImpl::createRemote(aMap);
    }
    
    if (aType == "bigset")
    {
        return KVStorageFactoryImpl::createBigsetRemote(aMap);
    }
//    if (aType == "automanagedflat")
//        return  KVStorageFactoryImpl::createManagedIFlat(aMap);
    
//    if (aType == "zdb2"){
//        return KVStorageFactoryImpl::createZDB2(aMap);
//    }
    
    if (aType == "kc"){
        return KVStorageFactoryImpl::createKC(creatingOption);
    }
	
    if (aType == "leveldb"){
        return KVStorageFactoryImpl::createLevelStorage(creatingOption);
    }
    
    if (aType == "distributed")
	return KVStorageFactoryImpl::createDistributed(aMap);

    if (aType == "filemapping")
	return KVStorageFactoryImpl::createFileMapping(aMap);
    
    if (aType == "shm")
	return KVStorageFactoryImpl::createSHM(aMap);

    if (aType == "smartshmmapping" || aType == "smartshm")
	return KVStorageFactoryImpl::createSmartSHMMapping(aMap);

//    if (aType == "iflat")
//	return KVStorageFactoryImpl::createIFlat(aMap);
//    if (aType == "smartiflat")
//	return KVStorageFactoryImpl::createSmartIFlat(aMap);
    
    return NULL;
    
}


}}