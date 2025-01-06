/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest.cpp
 * Author: trungthanh
 *
 * Created on May 23, 2016, 3:36 PM
 */

#include <stdlib.h>
#include <iostream>

using namespace std;

#include "Storage/zdb3/IFlatTable.h"
#include "Storage/FixedSizeSharedMemTable.h"
#include "IFlatTableCompactTool.h"


//bigset_0_zdb3_tmp_
FixedSizeSharedMemTable aIndex(8, 0, 20000000);

void openIndex()
{
    std::string indexFile = "/data/bigset/jx2/iflat/bigset/data1M/bigset_zdb3_tmp_.index"; //dir.path() + "/" +  this->_dbName+ ".index";
    Poco::File aFile(indexFile);    
    aIndex.open(aFile);
}

void checkDataFile()
{
    IFlatTable aTable(aIndex, "/data/bigset/jx2/iflat/bigset/data1M/bigset_0_zdb3_tmp_.flat", true, 0);
    aTable.open();
    aTable.startIterate();
    std::string k,v;
    size_t count = 0;
    while (aTable.iterateNextDebug(k,v))
    {
        count++;
    }
    cout<<"iterated done with "<<count<<" records"<<endl;
    aTable.close();
}

void readFile(){
    Poco::FileStream aFile("/data/bigset/jx2/iflat/bigset/data1M/bigset_0_zdb3_tmp_.flat", std::ios::in  | std::ios::binary);
    char data[32768];
    size_t total = 0;
    while (true){
        aFile.read(data, 32768);
        size_t gc = aFile.gcount();
        total += gc;
        if (aFile.eof() || aFile.fail() )
        {
            cout<<"only read "<<gc<<" bytes "<<aFile.eof()<<" "<<aFile.fail()<<endl;
            break;
        }
    }
    cout<<"total read: "<< total<<endl;
}

void readFile2(){
    Poco::FileStream aFile("/data/bigset/jx2/iflat/bigset/data1M/bigset_0_zdb3_tmp_.flat", std::ios::in  | std::ios::binary);
    char data[32768];
    size_t total = 0;
    aFile.seekg(104510652416ll);
    while (true){
        aFile.read(data, 32768);
        size_t gc = aFile.gcount();
        total += gc;
        if (aFile.eof() || aFile.fail() )
        {
            cout<<"only read "<<gc<<" bytes "<<aFile.eof()<<" "<<aFile.fail()<<endl;
            break;
        }
    }
    cout<<"total read: "<< total<<endl;
}

void readFile3(){
    Poco::FileStream aFile("/data/bigset/jx2/iflat/bigset/data1M/bigset_1_zdb3_tmp_.flat", std::ios::in  | std::ios::binary);
    char data[32768];
    size_t total = 0;
    //aFile.seekg(104510652416ll);
    while (true){
        aFile.read(data, 32768);
        size_t gc = aFile.gcount();
        total += gc;
        if (aFile.eof() || aFile.fail() )
        {
            cout<<"only read "<<gc<<" bytes "<<aFile.eof()<<" "<<aFile.fail()<<endl;
            break;
        }
    }
    cout<<"total read: "<< total<<endl;
}

void readFile4(){
    Poco::FileStream aFile("/data/bigset/jx2/iflat/bigset/data1M/bigset_1_zdb3_tmp_.flat", std::ios::in  | std::ios::binary);
    char data[32768];
    size_t total = 0;
    aFile.seekg(104510652416ll);
    while (true){
        aFile.read(data, 32768);
        size_t gc = aFile.gcount();
        total += gc;
        if (aFile.eof() || aFile.fail() )
        {
            cout<<"only read "<<gc<<" bytes "<<aFile.eof()<<" "<<aFile.fail()<<endl;
            break;
        }
    }
    cout<<"total read: "<< total<<endl;
}

#include "Poco/NumberParser.h"

int main(int argc, char** argv) {

    if (argc > 1 && (std::string(argv[1]) == "run")) {
        openIndex();
        checkDataFile();
    } 
    else    if (argc > 1 && (std::string(argv[1]) == "read")) {
        readFile();
    }    
    else    if (argc > 1 && (std::string(argv[1]) == "read2")) {
        readFile2();
    }    
    else    if (argc > 1 && (std::string(argv[1]) == "read3")) {
        readFile3();
    }    
    else    if (argc > 1 && (std::string(argv[1]) == "read4")) {
        readFile4();
    }    
    else    if (argc > 9 && (std::string(argv[1]) == "compact")) {
        
        cout<<"params:"<<argv[2]<<endl
                <<argv[3]<<endl
                <<argv[4]<<endl
                <<argv[5]<<endl
                <<argv[6]<<endl
                <<argv[7]<<endl
                <<argv[8]<<endl
                <<argv[9]<<endl;
        
        IFlatTableCompactTool aTool(
                argv[2],//src index type
                argv[3], // src index path
                argv[4], //src data path
                argv[5],//dst index type
                argv[6], // dst index path
                argv[7], //dst data path
                8,
                Poco::NumberParser::parse64(argv[8]),
                Poco::NumberParser::parse64(argv[9])
                );
        aTool.copyData();
        
    }    
    else {
        cout<<"no run"<<endl;
        cout<<"needed params : compact "
                "src_index_type: filemapping/shm \n"
                "src_index_path\n"
                "src_data_path\n"
                "dst_index_type: filemapping/shm \n"
                "dst_index_path\n"
                "dst_data_path\n"
                "startIndex\n"
                "numberOfItem"<<endl;
    }
    
    return (EXIT_SUCCESS);
}

