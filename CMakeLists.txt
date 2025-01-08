cmake_minimum_required(VERSION 3.10)

# Project name and version
project(OpenStorage LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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
)

# Preprocessor definitions
add_definitions(
    -DHAVE_CONFIG_H
    -DLEVELDB_PLATFORM_POSIX
    -DTHREADED
    -D_GNU_SOURCE
)

# Source files
set(SOURCES
    src/Storage/MongoStorage.cpp
    src/Storage/BigsetRemoteKV.cpp
    src/Storage/DistributedStorage.cpp
    src/Storage/FixedSizeSharedMemTable.cpp
    src/Storage/KCStorage.cpp
    src/Storage/KVStorageFactory.cpp
    src/Storage/LevelStorage.cpp
    src/Storage/RemoteKVStorage.cpp
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

# Header files
set(HEADERS
    inc/Storage/MongoStorage.h
    inc/Storage/BigsetRemoteKV.h
    inc/Storage/DistributedStorage.h
    inc/Storage/FixedSizeSharedMemTable.h
    inc/Storage/KCStorage.h
    inc/Storage/KVStorageFactory.h
    inc/Storage/LevelStorage.h
    inc/Storage/RemoteKVStorage.h
    inc/Storage/RocksDBStorage.h
    inc/Storage/SharedMemStorage.h
    inc/Storage/SimpleKCStorage.h
    inc/Storage/SimpleLevelStorage.h
    thrift/gen-cpp/KVDataService.h
    thrift/gen-cpp/RawBigSetKVService.h
    thrift/gen-cpp/bskv_constants.h
    thrift/gen-cpp/bskv_types.h
    thrift/gen-cpp/kv_constants.h
    thrift/gen-cpp/kv_types.h
)

# Add library
add_library(OpenStorage STATIC ${SOURCES} ${HEADERS})

# Link directories
link_directories(
    ../UPCaching/lib
    ../UPBase/lib
    ../../contribs/UPThrift/lib
    ../../contribs/UPPoco/lib
)

# Target link libraries
target_link_libraries(OpenStorage
    pthread
    dl
    rt
)
