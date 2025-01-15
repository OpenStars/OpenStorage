cmake_minimum_required(VERSION 3.10)

# Project name
project(OpenStorage)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Build type
set(CMAKE_BUILD_TYPE Release)

# Include directories
include_directories(
    inc
    ../../contribs/LibEvent/include
    ../../contribs/Boost/include
    ../../contribs/Poco/include
    ../../contribs/ApacheThrift/include
    ../../contribs/SpecialContribs/include
    thrift/gen-cpp
    ../../contribs/SpecialContribs/src/hashkit
    ../../contribs/SpecialContribs/src/libstatgrab
    ../../contribs/SpecialContribs/include/kyotocabinet
    ../../contribs/SpecialContribs/include/leveldb
    ../../contribs/SpecialContribs/src/
    ../../corelibs/BaseFoundation/include
    upframework/Poco/XML/include
    upframework/libevent2/compat
    upframework/libevent2
    upframework/jemalloc
    upframework/zkclient
    upframework/libstatgrab
    ./inc
    upframework
    /zserver/java/include
    /zserver/java/include/linux
)

# Preprocessor definitions
add_definitions(
    -DHAVE_CONFIG_H
    -DTHREADED
    -D_GNU_SOURCE
    -DLEVELDB_PLATFORM_POSIX
)

# Source files
set(SOURCES
    src/Storage/BigsetRemoteKV.cpp
    src/Storage/DistributedStorage.cpp
    src/Storage/FixedSizeSharedMemTable.cpp
    src/Storage/KCStorage.cpp
    src/Storage/KVStorageFactory.cpp
    src/Storage/LevelStorage.cpp
    src/Storage/RemoteKVStorage.cpp
    src/Storage/MongoKVStorage.cpp
    src/Storage/RocksDBStorage.cpp
    src/Storage/SharedMemStorage.cpp
    src/Storage/SimpleKCStorage.cpp
    src/Storage/SimpleLevelStorage.cpp
    thrift/gen-cpp/KVDataService.cpp
    thrift/gen-cpp/RawBigSetKVService.cpp
    thrift/gen-cpp/bskv_constants.cpp
    thrift/gen-cpp/bskv_types.cpp
    thrift/gen-cpp/kv_constants.cpp
    thrift/gen-cpp/kv_types.cpp
)

# Output library
add_library(openstorage STATIC ${SOURCES})

# Linker options
set(LINK_LIBRARIES
    ../UPCaching/lib/libupcaching.a
    ../UPBase/lib/libupbase.a
    ../../contribs/UPThrift/lib/libupthrift.a
    ../../contribs/UPPoco/lib/libuppoco.a
    pthread
    dl
    rt
)

target_link_libraries(openstorage ${LINK_LIBRARIES})
