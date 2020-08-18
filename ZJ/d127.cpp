#include <iostream>

using namespace std;

int main(){
    uint64_t l;
    while(cin >> l)cout << (l >> 2) * ((l >> 1) - (l >> 2)) << endl;
    return 0;
}
