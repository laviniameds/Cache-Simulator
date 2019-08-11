#include <stdio.h>
#include <iostream>

#define QTD_CACHE 8
#define QTD_RAM 256

using namespace std;

struct CACHE {
    int p[QTD_CACHE];
    string adress;
    string data;
};

struct RAM {
    string adress;
    string data;
};

int main(){

    RAM mem[QTD_RAM];
    CACHE cache[QTD_CACHE];

    //load memory
    for(int i=0;i<QTD_RAM;i++)
        cin >> mem[i].adress >> mem[i].data;
    

    //write memory data
    for(int i=0;i<QTD_RAM;i++)
        cout << "ADD: " << mem[i].adress << " DATA: " << mem[i].data << endl;
    

    return 0;
}
