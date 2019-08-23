#include <iostream> 
#include <iomanip>
#include <stdlib.h>

using namespace std;

int main(){
    for(int i=0;i<20;i++){
        cout << showbase // show the 0x prefix
        << internal // fill between the prefix and the number
        << setfill('0'); // fill with 0s

        cout << hex << uppercase << setw(4) << rand() % 15 << endl;
    }

    return 0;
}