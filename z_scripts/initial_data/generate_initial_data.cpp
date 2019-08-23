#include <iostream> 
#include <iomanip>

using namespace std;

int main(){
    char d = 'A';
    for(int i=0;i<256;i++){
        if(d > 90) d = 65;

        cout << showbase // show the 0x prefix
        << internal // fill between the prefix and the number
        << setfill('0'); // fill with 0s

        cout << hex << uppercase << setw(4) << i << " " 
        << d << d << d << d << d << endl;
        
        d++;
    }

    return 0;
}