#include <stdio.h>
#include <iostream>
#include <fstream>

#define QTD_CACHE 8
#define QTD_RAM 256

using namespace std;

struct CACHE {
    int p;
    string address;
    string data;
};

struct RAM {
    string address;
    string data;
};

RAM ram[QTD_RAM];
CACHE cache[QTD_CACHE];

int write_ram_data(){
    //write ram data
    for(int i=0;i<QTD_RAM;i++)
        cout << "ADD: " << ram[i].address 
        << " DATA: " << ram[i].data 
        << endl;
}

int write_cache_data(){
    //write cache data
    for(int i=0;i<QTD_CACHE;i++)
        cout << "P: " << cache[i].p 
        << " ADD: " << cache[i].address 
        << " DATA: " << cache[i].data 
        << endl;
}

void load_ram(){
    ifstream myReadFile;
    myReadFile.open("initial_data/initial_data");

    if (!myReadFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    //load ram
    for(int i=0;i<QTD_RAM;i++)
        myReadFile >> ram[i].address >> ram[i].data;

    myReadFile.close();
}

void load_cache(){
    for(int i=0;i<QTD_CACHE;i++){
        cache[i].p = 1;
        cache[i].address = "";
        cache[i].data = "";
    }
}

int search_ram(string address){
    //search if given address is into cache
    for(int i=0;i<QTD_RAM;i++){
        if(address == ram[i].address)
            return i;
    }
    return -1;    
}

int search_cache(string address){
    //search if given address is into cache
    for(int i=0;i<QTD_CACHE;i++){
        if(address == cache[i].address)
            return i;
    }
    return -1;
}

int get_min_p_cache(){
    //return minimum priority (always 1)
    for(int i=0;i<QTD_CACHE;i++){
        if(cache[i].p == 1)
            return i;
    }
}

void update_cache(int index){
    //set maximum priority
    cache[index].p = QTD_CACHE;

    //update other priorities
    for(int i=0;i<QTD_CACHE;i++){
        if(cache[i].p > 1 && cache[i].p != QTD_CACHE)
            cache[i].p--;
    }
}

void insert_cache(string address){
    int min_p = get_min_p_cache();
    cache[min_p].address = address;
    cache[min_p].data = ram[search_ram(address)].data;
    update_cache(min_p);
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
            update_cache(index);
            hit++;
        }    
        //else, insert adress into cache          
        else {
            insert_cache(address);
            miss++;
        }
    }
    
    cout << "HITS: " << hit 
    << " MISS: " << miss << endl
    << "HIT RATE: " << 100*(hit/(hit+miss)) << "%"
    << endl;

    return 0;
}
