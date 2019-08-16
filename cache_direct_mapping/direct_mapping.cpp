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

string get_address_binary(string address){
    //get hex address and convert to binary
    bitset<QTD_CACHE> ads_bin (stoi(address, 0, 16));
    //convert binary to string
    return ads_bin.to_string();
}

string get_line_binary(string address){
    //get hex address
    string str = get_address_binary(address);
    
    //get line part of full address
    return str.substr(str.length() - QTD_LINE);
}

string get_tag_binary(string address){
    //get binary full address
    string str = get_address_binary(address);
    
    //get tag part of full address
    return str.substr(0, QTD_TAG);
}

int get_line_index(string line){
    //convert line part to binary
    bitset<QTD_CACHE> bit_index(line);
    //convert binary line to int
    return (int)bit_index.to_ulong();
}

//search if given address is into cache
int search_cache(string address){    
    //get tag part of full address
    string tag = get_tag_binary(address);
    //get line part of full address
    string line = get_line_binary(address);
    
    //get line index
    int i = get_line_index(line);

    //if tag matches return the index (line)
    if(tag == cache[i].tag)
        return i;
    
    return -1;
}

void insert_cache(string address){
    string line = get_line_binary(address);
    string tag = get_tag_binary(address);
    int i = get_line_index(line);

    cache[i].tag = tag;
    cache[i].data = ram[search_ram(address)].data;
}

void update_cache(int i, string address){
    cache[i].tag = get_tag_binary(address);
    cache[i].data = ram[search_ram(address)].data;
}

int main(){   
    //load ram
    load_ram();

    //load_cache
    load_cache();

    //write_ram_data();
    //write_cache_data();

    double hit = 0;
    double miss = 0;

    string address;

    // read trace
    while (cin >> address){

        //check if adress is into cache
        int index = search_cache(address);

        //if it is, update cache priority
        if(index != -1){
            update_cache(index, address);
            hit++;
        }    
        //else, insert adress into cache          
        else {
            insert_cache(address);
            miss++;
        }
    }
    
    cout << "HIT: " << hit 
    << " MISS: " << miss << endl
    << "HIT RATE: " << 100*(hit/(hit+miss)) << "%"
    << endl;

    cout << endl << endl << endl;
    write_cache_data();

    return 0;
}
