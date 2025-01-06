/* 
 * File:   FixedSizeSharedMemTable.h
 * Author: trungthanh
 *
 * Created on April 7, 2013, 11:44 PM
 */

#ifndef FIXEDSIZESHAREDMEMTABLE_H
#define	FIXEDSIZESHAREDMEMTABLE_H

#include "PocoEx/SharedMemoryEx.h"
#include <stdint.h>


/*
 * Bảng giá trị có key là số nguyên, tăng dần (i32), value có độ dài cố định 
 * Sử dụng SharedMemory 
 * Có thể sử dụng linh hoạt như các dạng counter 
 */



class FixedSizeSharedMemTable
{
public:
    FixedSizeSharedMemTable(int16_t _valueSize, size_t keyOffset, size_t maxItems, bool useMem = false);
    
    bool open(const std::string& shmName);
    
    bool open(Poco::File& file);
    
    bool close();
    
    // đảm bảo data sẽ lên mem 
    void warmUp();
    
    char* begin(){
        return _shm->begin();
    }
    
    size_t getOffset() const{
        return _keyOffset;
    }
    
    // lấy con trỏ ứng với vị trí key 
    char* getAt(size_t key);
    
    
    //outBoundIndex from 0 to 1016
    char* getExtra(size_t outBoundIndex);
    
    template <typename T>
    T* getAt(size_t key)
    {
	T* aPtr = (T*)getAt(key);
	return aPtr;
    }
    
    // tăng giá trị ứng với key lên 
    bool increase(size_t key, int value = 1);
    
    // giảm giá trị ứng với key xuống   
    bool decrease(size_t key, int value = 1);
    
    void flush();
    
    void setAutoUnlinkSHM(bool autoUnlink = true)
    {
        if (_shm)
            _shm->setAutoUnlink(autoUnlink);
    }
    
public:
    const size_t valueSize()const 
    {
	return _valueSize;
    }
    
public:
    
    virtual ~FixedSizeSharedMemTable();
    
private:
    FixedSizeSharedMemTable(const FixedSizeSharedMemTable& orig);
    
protected:
    SharedMemoryEx* _shm;

    int16_t _valueSize; // kích thước value 
    
    size_t _keyOffset; // key bé nhất. 

    size_t _maxItem;// số lượng item tối đa 
    
    bool _useMem;
    
    char* _pBase;
};

#endif	/* FIXEDSIZESHAREDMEMDB_H */

