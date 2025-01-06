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
CND_CONF=Release
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

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/flatcompact

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/zdb4compactingtool.o

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk lib/libopenstorage.a

lib/libopenstorage.a: ${OBJECTFILES}
	${MKDIR} -p lib
	${RM} lib/libopenstorage.a
	${AR} -rv lib/libopenstorage.a ${OBJECTFILES} 
	$(RANLIB) lib/libopenstorage.a

${OBJECTDIR}/src/Storage/BigsetRemoteKV.o: src/Storage/BigsetRemoteKV.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/BigsetRemoteKV.o src/Storage/BigsetRemoteKV.cpp

${OBJECTDIR}/src/Storage/DistributedStorage.o: src/Storage/DistributedStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/DistributedStorage.o src/Storage/DistributedStorage.cpp

${OBJECTDIR}/src/Storage/FixedSizeSharedMemTable.o: src/Storage/FixedSizeSharedMemTable.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/FixedSizeSharedMemTable.o src/Storage/FixedSizeSharedMemTable.cpp

${OBJECTDIR}/src/Storage/KCStorage.o: src/Storage/KCStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/KCStorage.o src/Storage/KCStorage.cpp

${OBJECTDIR}/src/Storage/KVStorageFactory.o: src/Storage/KVStorageFactory.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/KVStorageFactory.o src/Storage/KVStorageFactory.cpp

${OBJECTDIR}/src/Storage/LevelStorage.o: src/Storage/LevelStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/LevelStorage.o src/Storage/LevelStorage.cpp

${OBJECTDIR}/src/Storage/RemoteKVStorage.o: src/Storage/RemoteKVStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/RemoteKVStorage.o src/Storage/RemoteKVStorage.cpp

${OBJECTDIR}/src/Storage/RocksDBStorage.o: src/Storage/RocksDBStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/RocksDBStorage.o src/Storage/RocksDBStorage.cpp

${OBJECTDIR}/src/Storage/SharedMemStorage.o: src/Storage/SharedMemStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/SharedMemStorage.o src/Storage/SharedMemStorage.cpp

${OBJECTDIR}/src/Storage/SimpleKCStorage.o: src/Storage/SimpleKCStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/SimpleKCStorage.o src/Storage/SimpleKCStorage.cpp

${OBJECTDIR}/src/Storage/SimpleLevelStorage.o: src/Storage/SimpleLevelStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/SimpleLevelStorage.o src/Storage/SimpleLevelStorage.cpp

${OBJECTDIR}/thrift/gen-cpp/KVDataService.o: thrift/gen-cpp/KVDataService.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/KVDataService.o thrift/gen-cpp/KVDataService.cpp

${OBJECTDIR}/thrift/gen-cpp/RawBigSetKVService.o: thrift/gen-cpp/RawBigSetKVService.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/RawBigSetKVService.o thrift/gen-cpp/RawBigSetKVService.cpp

${OBJECTDIR}/thrift/gen-cpp/bskv_constants.o: thrift/gen-cpp/bskv_constants.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/bskv_constants.o thrift/gen-cpp/bskv_constants.cpp

${OBJECTDIR}/thrift/gen-cpp/bskv_types.o: thrift/gen-cpp/bskv_types.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/bskv_types.o thrift/gen-cpp/bskv_types.cpp

${OBJECTDIR}/thrift/gen-cpp/kv_constants.o: thrift/gen-cpp/kv_constants.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/kv_constants.o thrift/gen-cpp/kv_constants.cpp

${OBJECTDIR}/thrift/gen-cpp/kv_types.o: thrift/gen-cpp/kv_types.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/kv_types.o thrift/gen-cpp/kv_types.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/flatcompact: ${TESTDIR}/tests/zdb4compactingtool.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/flatcompact $^ ${LDLIBSOPTIONS}   ../UPCaching/lib/libupcaching.a ../UPBase/lib/libupbase.a ../../contribs/UPThrift/lib/libupthrift.a ../../contribs/UPPoco/lib/libuppoco.a -lpthread -ldl -lrt 


${TESTDIR}/tests/zdb4compactingtool.o: tests/zdb4compactingtool.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/zdb4compactingtool.o tests/zdb4compactingtool.cpp


${OBJECTDIR}/src/Storage/BigsetRemoteKV_nomain.o: ${OBJECTDIR}/src/Storage/BigsetRemoteKV.o src/Storage/BigsetRemoteKV.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/BigsetRemoteKV.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/BigsetRemoteKV_nomain.o src/Storage/BigsetRemoteKV.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/BigsetRemoteKV.o ${OBJECTDIR}/src/Storage/BigsetRemoteKV_nomain.o;\
	fi

${OBJECTDIR}/src/Storage/DistributedStorage_nomain.o: ${OBJECTDIR}/src/Storage/DistributedStorage.o src/Storage/DistributedStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/DistributedStorage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/DistributedStorage_nomain.o src/Storage/DistributedStorage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/DistributedStorage.o ${OBJECTDIR}/src/Storage/DistributedStorage_nomain.o;\
	fi

${OBJECTDIR}/src/Storage/FixedSizeSharedMemTable_nomain.o: ${OBJECTDIR}/src/Storage/FixedSizeSharedMemTable.o src/Storage/FixedSizeSharedMemTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/FixedSizeSharedMemTable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/FixedSizeSharedMemTable_nomain.o src/Storage/FixedSizeSharedMemTable.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/FixedSizeSharedMemTable.o ${OBJECTDIR}/src/Storage/FixedSizeSharedMemTable_nomain.o;\
	fi

${OBJECTDIR}/src/Storage/KCStorage_nomain.o: ${OBJECTDIR}/src/Storage/KCStorage.o src/Storage/KCStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/KCStorage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/KCStorage_nomain.o src/Storage/KCStorage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/KCStorage.o ${OBJECTDIR}/src/Storage/KCStorage_nomain.o;\
	fi

${OBJECTDIR}/src/Storage/KVStorageFactory_nomain.o: ${OBJECTDIR}/src/Storage/KVStorageFactory.o src/Storage/KVStorageFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/KVStorageFactory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/KVStorageFactory_nomain.o src/Storage/KVStorageFactory.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/KVStorageFactory.o ${OBJECTDIR}/src/Storage/KVStorageFactory_nomain.o;\
	fi

${OBJECTDIR}/src/Storage/LevelStorage_nomain.o: ${OBJECTDIR}/src/Storage/LevelStorage.o src/Storage/LevelStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/LevelStorage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/LevelStorage_nomain.o src/Storage/LevelStorage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/LevelStorage.o ${OBJECTDIR}/src/Storage/LevelStorage_nomain.o;\
	fi

${OBJECTDIR}/src/Storage/RemoteKVStorage_nomain.o: ${OBJECTDIR}/src/Storage/RemoteKVStorage.o src/Storage/RemoteKVStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/RemoteKVStorage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/RemoteKVStorage_nomain.o src/Storage/RemoteKVStorage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/RemoteKVStorage.o ${OBJECTDIR}/src/Storage/RemoteKVStorage_nomain.o;\
	fi

${OBJECTDIR}/src/Storage/RocksDBStorage_nomain.o: ${OBJECTDIR}/src/Storage/RocksDBStorage.o src/Storage/RocksDBStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/RocksDBStorage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/RocksDBStorage_nomain.o src/Storage/RocksDBStorage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/RocksDBStorage.o ${OBJECTDIR}/src/Storage/RocksDBStorage_nomain.o;\
	fi

${OBJECTDIR}/src/Storage/SharedMemStorage_nomain.o: ${OBJECTDIR}/src/Storage/SharedMemStorage.o src/Storage/SharedMemStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/SharedMemStorage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/SharedMemStorage_nomain.o src/Storage/SharedMemStorage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/SharedMemStorage.o ${OBJECTDIR}/src/Storage/SharedMemStorage_nomain.o;\
	fi

${OBJECTDIR}/src/Storage/SimpleKCStorage_nomain.o: ${OBJECTDIR}/src/Storage/SimpleKCStorage.o src/Storage/SimpleKCStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/SimpleKCStorage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/SimpleKCStorage_nomain.o src/Storage/SimpleKCStorage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/SimpleKCStorage.o ${OBJECTDIR}/src/Storage/SimpleKCStorage_nomain.o;\
	fi

${OBJECTDIR}/src/Storage/SimpleLevelStorage_nomain.o: ${OBJECTDIR}/src/Storage/SimpleLevelStorage.o src/Storage/SimpleLevelStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/SimpleLevelStorage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/SimpleLevelStorage_nomain.o src/Storage/SimpleLevelStorage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/SimpleLevelStorage.o ${OBJECTDIR}/src/Storage/SimpleLevelStorage_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/KVDataService_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/KVDataService.o thrift/gen-cpp/KVDataService.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/KVDataService.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/KVDataService_nomain.o thrift/gen-cpp/KVDataService.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/KVDataService.o ${OBJECTDIR}/thrift/gen-cpp/KVDataService_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/RawBigSetKVService_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/RawBigSetKVService.o thrift/gen-cpp/RawBigSetKVService.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/RawBigSetKVService.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/RawBigSetKVService_nomain.o thrift/gen-cpp/RawBigSetKVService.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/RawBigSetKVService.o ${OBJECTDIR}/thrift/gen-cpp/RawBigSetKVService_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/bskv_constants_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/bskv_constants.o thrift/gen-cpp/bskv_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/bskv_constants.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/bskv_constants_nomain.o thrift/gen-cpp/bskv_constants.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/bskv_constants.o ${OBJECTDIR}/thrift/gen-cpp/bskv_constants_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/bskv_types_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/bskv_types.o thrift/gen-cpp/bskv_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/bskv_types.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/bskv_types_nomain.o thrift/gen-cpp/bskv_types.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/bskv_types.o ${OBJECTDIR}/thrift/gen-cpp/bskv_types_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/kv_constants_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/kv_constants.o thrift/gen-cpp/kv_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/kv_constants.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/kv_constants_nomain.o thrift/gen-cpp/kv_constants.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/kv_constants.o ${OBJECTDIR}/thrift/gen-cpp/kv_constants_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/kv_types_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/kv_types.o thrift/gen-cpp/kv_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/kv_types.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DHAVE_CONFIG_H -DLEVELDB_PLATFORM_POSIX -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/include/kyotocabinet -I../../contribs/SpecialContribs/include/leveldb -I../../contribs/SpecialContribs/src/ -I../../corelibs/BaseFoundation/include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/kv_types_nomain.o thrift/gen-cpp/kv_types.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/kv_types.o ${OBJECTDIR}/thrift/gen-cpp/kv_types_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/flatcompact || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
