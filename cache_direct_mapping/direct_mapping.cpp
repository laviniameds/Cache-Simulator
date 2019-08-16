#include <stdio.h>
#include <iostream>
#include <fstream>
#include <bitset>  

#define QTD_CACHE 8
#define QTD_RAM 256
#define QTD_TAG 5
#define QTD_LINE 3

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
        cout << "TAG: " << cache[i].tag 
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
        bitset<QTD_LINE> bit (i);
        cache[i].line = bit.to_string();
        cache[i].tag = "";
        cache[i].data = "";
    }
}

//search if given address is into ram
int search_ram(string address){
    for(int i=0;i<QTD_RAM;i++){
        if(address == ram[i].address)
            return i;
    }
    return -1;    
}

//search if given address is into cache
int search_cache(string address){
    //get hex address and convert to binary
    bitset<QTD_CACHE> ads_bin (stoi(address, 0, 16));
    //convert binary to string
    string str = ads_bin.to_string();
    
    //get tag part of full address
    string tag = str.substr(0, QTD_TAG-1);
    //get line part of full address
    string line = str.substr(str.length() - QTD_LINE);

    //convert line part to binary
    bitset<QTD_CACHE> bit_index(line);
    //convert binary line to int
    int i = (int)bit_index.to_ulong();
    
    //if tag matches return the index (line)
    if(tag == cache[i].tag)
        return i;
    
    return -1;
}

int main(){   
    //load ram
    load_ram();

    //load_cache
    load_cache();

    //write_ram_data();
    //write_cache_data();

    return 0;
}
