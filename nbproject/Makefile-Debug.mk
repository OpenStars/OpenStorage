#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Storage/BigsetRemoteKV.o \
	${OBJECTDIR}/src/Storage/DistributedStorage.o \
	${OBJECTDIR}/src/Storage/FixedSizeSharedMemTable.o \
	${OBJECTDIR}/src/Storage/KCStorage.o \
	${OBJECTDIR}/src/Storage/KVStorageFactory.o \
	${OBJECTDIR}/src/Storage/LevelStorage.o \
	${OBJECTDIR}/src/Storage/RemoteKVStorage.o \
	${OBJECTDIR}/src/Storage/RocksDBStorage.o \
	${OBJECTDIR}/src/Storage/SharedMemStorage.o \
	${OBJECTDIR}/src/Storage/SimpleKCStorage.o \
	${OBJECTDIR}/src/Storage/SimpleLevelStorage.o \
	${OBJECTDIR}/thrift/gen-cpp/KVDataService.o \
	${OBJECTDIR}/thrift/gen-cpp/RawBigSetKVService.o \
	${OBJECTDIR}/thrift/gen-cpp/bskv_constants.o \
	${OBJECTDIR}/thrift/gen-cpp/bskv_types.o \
	${OBJECTDIR}/thrift/gen-cpp/kv_constants.o \
	${OBJECTDIR}/thrift/gen-cpp/kv_types.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk lib/libopenstoraged.a

lib/libopenstoraged.a: ${OBJECTFILES}
	${MKDIR} -p lib
	${RM} lib/libopenstoraged.a
	${AR} -rv lib/libopenstoraged.a ${OBJECTFILES} 
	$(RANLIB) lib/libopenstoraged.a

${OBJECTDIR}/src/Storage/BigsetRemoteKV.o: src/Storage/BigsetRemoteKV.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/BigsetRemoteKV.o src/Storage/BigsetRemoteKV.cpp

${OBJECTDIR}/src/Storage/DistributedStorage.o: src/Storage/DistributedStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/DistributedStorage.o src/Storage/DistributedStorage.cpp

${OBJECTDIR}/src/Storage/FixedSizeSharedMemTable.o: src/Storage/FixedSizeSharedMemTable.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/FixedSizeSharedMemTable.o src/Storage/FixedSizeSharedMemTable.cpp

${OBJECTDIR}/src/Storage/KCStorage.o: src/Storage/KCStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/KCStorage.o src/Storage/KCStorage.cpp

${OBJECTDIR}/src/Storage/KVStorageFactory.o: src/Storage/KVStorageFactory.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/KVStorageFactory.o src/Storage/KVStorageFactory.cpp

${OBJECTDIR}/src/Storage/LevelStorage.o: src/Storage/LevelStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/LevelStorage.o src/Storage/LevelStorage.cpp

${OBJECTDIR}/src/Storage/RemoteKVStorage.o: src/Storage/RemoteKVStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/RemoteKVStorage.o src/Storage/RemoteKVStorage.cpp

${OBJECTDIR}/src/Storage/RocksDBStorage.o: src/Storage/RocksDBStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/RocksDBStorage.o src/Storage/RocksDBStorage.cpp

${OBJECTDIR}/src/Storage/SharedMemStorage.o: src/Storage/SharedMemStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/SharedMemStorage.o src/Storage/SharedMemStorage.cpp

${OBJECTDIR}/src/Storage/SimpleKCStorage.o: src/Storage/SimpleKCStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/SimpleKCStorage.o src/Storage/SimpleKCStorage.cpp

${OBJECTDIR}/src/Storage/SimpleLevelStorage.o: src/Storage/SimpleLevelStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/SimpleLevelStorage.o src/Storage/SimpleLevelStorage.cpp

${OBJECTDIR}/thrift/gen-cpp/KVDataService.o: thrift/gen-cpp/KVDataService.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/KVDataService.o thrift/gen-cpp/KVDataService.cpp

${OBJECTDIR}/thrift/gen-cpp/RawBigSetKVService.o: thrift/gen-cpp/RawBigSetKVService.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/RawBigSetKVService.o thrift/gen-cpp/RawBigSetKVService.cpp

${OBJECTDIR}/thrift/gen-cpp/bskv_constants.o: thrift/gen-cpp/bskv_constants.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/bskv_constants.o thrift/gen-cpp/bskv_constants.cpp

${OBJECTDIR}/thrift/gen-cpp/bskv_types.o: thrift/gen-cpp/bskv_types.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/bskv_types.o thrift/gen-cpp/bskv_types.cpp

${OBJECTDIR}/thrift/gen-cpp/kv_constants.o: thrift/gen-cpp/kv_constants.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/kv_constants.o thrift/gen-cpp/kv_constants.cpp

${OBJECTDIR}/thrift/gen-cpp/kv_types.o: thrift/gen-cpp/kv_types.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -g -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/kv_types.o thrift/gen-cpp/kv_types.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
