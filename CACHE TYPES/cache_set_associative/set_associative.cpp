#include <stdio.h>
#include <iostream>
#include <fstream>
#include <bitset>

#define QTD_CACHE 32
#define QTD_RAM 256
#define QTD_TAG 27
#define QTD_LINE 5
#define QTD_SET 2

using namespace std;

struct CACHE {
    string tag;
    string line;
    int priority;
    string data;
};

CACHE cache[QTD_CACHE][QTD_SET];

//write cache data
void write_cache_data(){
  for(int i=0;i<QTD_CACHE;i++)
    for(int j=0;j<QTD_SET;j++){
      cout << "TAG: " << cache[i][j].tag
      << " LINE: " << cache[i][j].line
      << " PRIORITY: " << cache[i][j].priority
      << " DATA: " << cache[i][j].data
      << " SET: " << j+1
      << endl;
    }
}

//load cache
void load_cache(){
    for(int i=0;i<QTD_CACHE;i++)
        for(int j=0;j<QTD_SET;j++){
        bitset<QTD_LINE> bit (i);
        cache[i][j].line = bit.to_string();
        cache[i][j].priority = 1;
        cache[i][j].tag = "";
        cache[i][j].data = "RANDOM DATA";
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

//return minimum priority (always 1)
int get_min_p_cache(int index){
    for(int j=0;j<QTD_SET;j++){
        if(cache[index][j].priority == 1)
            return j;
    }
}

//search if given address is into cache
int search_cache(string address){
    string add = get_address_binary(address);

    //get tag part of full address
    string tag = add.substr(0 , add.length()-QTD_LINE);

    //get line part of full address
    string line =  add.substr(add.length()-QTD_LINE , add.length());

    //get line index
    int index = get_line_index(line);

    //if tag matches return the index (line)
    for(int j=0;j<QTD_SET;j++)
        if(cache[index][j].tag == tag)
          return index;

    return -1;
}

void update_cache(int index){
    int min_p = get_min_p_cache(index);
    int last_priority = cache[index][min_p].priority;

    cache[index][min_p].priority = QTD_SET;

    for(int j=0;j<QTD_SET;j++)
        if(cache[index][j].priority > last_priority && j != min_p) 
            cache[index][j].priority--; 
}

void insert_cache(string address){
    string add = get_address_binary(address);

    //get tag part of full address
    string tag = add.substr(0 , add.length()-QTD_LINE);

    //get line part of full address
    string line =  add.substr(add.length()-QTD_LINE , add.length());

    //get line index
    int index = get_line_index(line);
    
    int min_p = get_min_p_cache(index);
    cache[index][min_p].tag = tag;
    cache[index][min_p].data = "NEW DATA";
    update_cache(index);
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
            update_cache(index);
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