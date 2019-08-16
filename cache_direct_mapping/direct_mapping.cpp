#include <stdio.h>
#include <iostream>
#include <fstream>
#include <bitset>  

#define QTD_CACHE 8
#define QTD_RAM 256

using namespace std;

struct CACHE {
    string tag;
    string line;
    string data;
};

struct RAM {
    string address;
    string data;
};

RAM ram[QTD_RAM];
CACHE cache[QTD_CACHE];

//write ram data
int write_ram_data(){
    for(int i=0;i<QTD_RAM;i++)
        cout << "ADD: " << ram[i].address 
        << " DATA: " << ram[i].data 
        << endl;
}

//write cache data
int write_cache_data(){
    for(int i=0;i<QTD_CACHE;i++)       
        cout << " TAG: " << cache[i].tag 
        << " LINE: " << cache[i].line 
        << " DATA: " << cache[i].data 
        << endl;
}

//load ram
void load_ram(){
    ifstream myReadFile;
    myReadFile.open("./initial_data/initial_data");

    if (!myReadFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    for(int i=0;i<QTD_RAM;i++)
        myReadFile >> ram[i].address >> ram[i].data;

    myReadFile.close();
}

//load cache
void load_cache(){
    for(int i=0;i<QTD_CACHE;i++){
        bitset<5> bit (i);
        cache[i].line = bit.to_string();
        cache[i].tag = "";
        cache[i].data = "";
    }
}
