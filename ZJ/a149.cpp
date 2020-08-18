#include <bits/stdc++.h>

using namespace std;

int main(){
    uint64_t t, r;
    cin >> t;
    while(cin >> t){
        r = (t != 0);
        while(t){
            r *= (t % 10);
            t /= 10;
        }
        cout << r << endl;
    }

    return 0;
}
