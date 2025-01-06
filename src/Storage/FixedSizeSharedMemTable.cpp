/* 
 * File:   FixedSizeSharedMemTable.cpp
 * Author: trungthanh
 * 
 * Created on April 7, 2013, 11:44 PM
 */

#include <string.h>

#include "Storage/FixedSizeSharedMemTable.h"

#include "Poco/Path.h"
#include "Poco/File.h"

FixedSizeSharedMemTable::FixedSizeSharedMemTable(int16_t valueSize, size_t keyOffset, size_t maxItems, bool useMem)
:_shm(NULL)
,_valueSize(valueSize) // kích thước value 
,_keyOffset(keyOffset) // key bé nhất. 
,_maxItem(maxItems)// số lượng item tối đa 
,_useMem(useMem)
,_pBase(NULL)
{
}

//FixedSizeSharedMemTable::FixedSizeSharedMemTable(const FixedSizeSharedMemTable& orig)
//{
//}

FixedSizeSharedMemTable::~FixedSizeSharedMemTable()
{
    close();
}

bool FixedSizeSharedMemTable::open(const std::string& shmName)
{
    if (_shm)
	return false;
    _shm = new SharedMemoryEx(shmName, _valueSize*_maxItem + 1024, 
	    SharedMemoryEx::AM_WRITE , NULL );
    this->_useMem = false;
    this->_pBase = _shm->begin();
    _shm->setAutoUnlink(false);
    return true;
}

bool FixedSizeSharedMemTable::open(Poco::File& file)
{
    if (_shm)
	return false;
        
    if (!file.exists())
    {
	file.createFile();
    }
    size_t aSize = _valueSize * _maxItem + 1024;
    
    if (file.getSize() < aSize)
	file.setSize(aSize);
    try {
	_shm = new SharedMemoryEx(file, SharedMemoryEx::AM_WRITE);
        if (!_useMem)
            this->_pBase = _shm->begin();
        else
        {
            try {
                this->_pBase = new char[aSize];
                
                ::memcpy(_pBase, _shm->begin(), aSize );
                
            } catch(...)
            {
                this->_pBase = _shm->begin();
                _useMem = false;
            }
        }
    }
    catch(...)
    {
	delete _shm;
	_shm = NULL;
	return false;
    }
    
    return true;
}

void FixedSizeSharedMemTable::flush()
{
    if (!_shm)
	return ;
    if (_useMem && _pBase)
    {
       ::memcpy( _shm->begin(), _pBase, _shm->end() - _shm->begin() );
    }
    
}
bool FixedSizeSharedMemTable::close()
{
    if (!_shm)
	return false;
    if (_useMem && _pBase)
    {
       ::memcpy( _shm->begin(), _pBase, _shm->end() - _shm->begin() );
       _useMem = false;
       delete [] _pBase;
       _pBase = NULL;
    }
    delete _shm;
    _shm = NULL;
    return true;
}

// đảm bảo data sẽ lên mem 
void FixedSizeSharedMemTable::warmUp()
{
    if (!_shm)
	return;
    
    char tmp = 0;
    for (char* aPtr = _shm->begin(); aPtr != _shm->end(); aPtr++)
    {
	tmp = *aPtr;
	*aPtr = tmp;
    }
}

char* FixedSizeSharedMemTable::getExtra(size_t outBoundIndex)
{
    if (!_shm)
	return NULL;
    if (outBoundIndex >= 1016)
        return NULL;
    size_t  aIndex = _valueSize * _maxItem + outBoundIndex + 8;
    return _shm->begin() + aIndex;
}

// lấy con trỏ ứng với vị trí key 
char* FixedSizeSharedMemTable::getAt(size_t key)
{
    if (!_shm)
	return NULL;
    if (key < _keyOffset)
        return NULL;
    size_t index = (key - _keyOffset)*_valueSize;
    if (index + 1024 + _shm->begin() < _shm->end()  )
    {
        if (_pBase)
            return _pBase + index;
	return _shm->begin() + index;
    }
    return NULL;
}

// tăng giá trị ứng với key lên 1 
bool FixedSizeSharedMemTable::increase(size_t key, int value)
{
    Poco::UInt32* aIntValue = (Poco::UInt32*)(getAt(key));
    if (aIntValue)
    {
	__sync_fetch_and_add(aIntValue, value);
	//(*aIntValue)+=value;
	return true;
    }
    return false;
}

// giảm giá trị ứng với key lên 1 
bool FixedSizeSharedMemTable::decrease(size_t key, int value)
{
    return increase(key, -value);
}
