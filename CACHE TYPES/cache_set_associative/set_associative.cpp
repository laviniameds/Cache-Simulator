#include <stdio.h>
#include <iostream>
#include <fstream>
#include <bitset>  

#define QTD_CACHE 32
#define QTD_RAM 256
#define QTD_TAG 27
#define QTD_LINE 5
#define QTD_SET 16

using namespace std;

struct CACHE {
    string tag;
    string line;
    int priority;
    string data;
};

CACHE cache[QTD_CACHE];

//write cache data
int write_cache_data(){
    for(int i=0;i<QTD_CACHE;i++)       
        cout << "TAG: " << cache[i].tag 
        << " LINE: " << cache[i].line 
        << " PRIORITY: " << cache[i].priority 
        << " DATA: " << cache[i].data 
        << endl;
}

//load cache
void load_cache(){
    for(int i=0;i<QTD_CACHE;i++){
        bitset<QTD_LINE> bit (i);
        cache[i].line = bit.to_string();
        cache[i].priority = 0;
        cache[i].tag = "";
        cache[i].data = "";
    }
}

string get_address_binary(string address){
    //get hex address and convert to binary
    bitset<QTD_CACHE> ads_bin (stol(address, nullptr, 16));
    //convert binary to string
    return ads_bin.to_string();
}

int get_line_index(string line){
    //convert line part to binary
    bitset<QTD_LINE> bit_index(line);
    //convert binary line to int
    return (int)bit_index.to_ulong();
}

int other_index(int index){
    if(index%2 == 0)
        return index+1;
    else
        return index-1;
}

//search if given address is into cache
int search_cache(string address){  
    string add = get_address_binary(address);
      
    //get tag part of full address
    string tag = add.substr(0 , add.length()-QTD_LINE);

    //get line part of full address
    string line =  add.substr(add.length()-QTD_LINE , add.length());

    //get line index
    int i = get_line_index(line);

    //if tag matches return the index (line)
    if(tag == cache[i].tag || tag == cache[other_index(i)].tag){
        return i;
    }
    
    return -1;
}

void update_cache(int index, string address){
    cache[index].priority = 1;
    cache[other_index(index)].priority = 0;
}

void insert_cache(string address){
    string add = get_address_binary(address);
      
    //get tag part of full address
    string tag = add.substr(0 , add.length()-QTD_LINE);

    //get line part of full address
    string line =  add.substr(add.length()-QTD_LINE , add.length());

    //get line index
    int i = get_line_index(line); 
    
    int less_p;

    if(cache[i].priority == 0)
        less_p = i;
    else 
        less_p = other_index(i);

    cache[less_p].tag = tag;
    cache[less_p].data = "RANDOM DATA";
    cache[less_p].priority = 1;
    cache[other_index(less_p)].priority = 0;
}

int main(){   
    //load_cache
    load_cache();

    double hit = 0;
    double miss = 0;

    string address;
    int index;

    // read trace
    while (cin >> address){

        //check if adress is into cache
        index = search_cache(address);

        //if it is, hit!
        if(index != -1){
            update_cache(index, address);
            hit++;
        }    
        //else, insert adress into cache, miss!          
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
