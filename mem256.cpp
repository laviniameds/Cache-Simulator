#include <stdio.h>
#include <iostream>
#include<fstream>

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

RAM mem[QTD_RAM];
CACHE cache[QTD_CACHE];

int write_memory_data(){
    //write memory data
    for(int i=0;i<QTD_RAM;i++)
        cout << "ADD: " << mem[i].address 
        << " DATA: " << mem[i].data 
        << endl;
}

int write_cache_data(){
    //write memory data
    for(int i=0;i<QTD_CACHE;i++)
        cout << "P: " << cache[i].p 
        << " ADD: " << cache[i].address 
        << " DATA: " << cache[i].data 
        << endl;
}

void load_memory(){
    ifstream myReadFile;
    myReadFile.open("initial_data/initial_data");

    if (!myReadFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    //load memory
    for(int i=0;i<QTD_RAM;i++)
        myReadFile >> mem[i].address >> mem[i].data;

    myReadFile.close();
}

void load_cache(){
    for(int i=0;i<QTD_CACHE;i++){
        cache[i].p = 1;
        cache[i].address = "";
        cache[i].data = "";
    }
}

int search_memory(string address){
    for(int i=0;i<QTD_RAM;i++){
        if(address == mem[i].address)
            return i;
    }
    return -1;    
}

int search_cache(string address){
    for(int i=0;i<QTD_CACHE;i++){
        if(address == cache[i].address)
            return i;
    }
    return -1;
}

int get_min_p_cache(){
    for(int i=0;i<QTD_CACHE;i++){
        if(cache[i].p == 1)
            return i;
    }
}

void update_cache(int index){
    cache[index].p = QTD_CACHE;

    for(int i=0;i<QTD_CACHE;i++){
        if(cache[i].p > 1 && cache[i].p != QTD_CACHE)
            cache[i].p--;
    }
}

void insert_cache(string address){
    cache[get_min_p_cache()].address = address;
    cache[get_min_p_cache()].data = mem[search_memory(address)].data;
    update_cache(get_min_p_cache());
}

int main(){   
    
    //load memory
    load_memory();

    //load_cache
    load_cache();

    //write_memory_data();
    //write_cache_data();

    double hit = 0;
    double miss = 0;

    string address;

    // read trace
    while (cin >> address){

        int index = search_cache(address);

        if(index != -1){
            update_cache(index);
            hit++;
        }              
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
