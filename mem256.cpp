#include <stdio.h>
#include <iostream>

#define QTD_CACHE_ADRESS 8
#define QTD_CACHE_DATA 8
#define QTD_RAM_ADRESS 256
#define QTD_RAM_DATA 256

using namespace std;

struct CACHE {
    int p[QTD_CACHE_ADRESS];
    string adress[QTD_CACHE_ADRESS];
    string data[QTD_CACHE_DATA];
};

struct RAM {
    string adress[QTD_RAM_ADRESS];
    string data[QTD_RAM_DATA];
};

int main(){

    RAM mem;
    CACHE cache;

    



    return 0;
}
