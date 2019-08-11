#include <stdio.h>
#include <iostream>

#define QTD_CACHE 8
#define QTD_RAM 256

using namespace std;

struct CACHE {
    int p[QTD_CACHE];
    string address;
    string data;
};

struct RAM {
    string address;
    string data;
};

int write_memory_data(RAM mem[QTD_RAM]){
    //write memory data
    for(int i=0;i<QTD_RAM;i++)
        cout << "ADD: " << mem[i].address << " DATA: " << mem[i].data << endl;
}

void load_memory(RAM mem[QTD_RAM]){
    //load memory
    for(int i=0;i<QTD_RAM;i++)
        cin >> mem[i].address >> mem[i].data;
}

int main(){
    RAM mem[QTD_RAM];
    CACHE cache[QTD_CACHE];
    
    string address;
    
    //load memory
    load_memory(mem);

    while (cin >> address){
        
    }
    

    return 0;
}
