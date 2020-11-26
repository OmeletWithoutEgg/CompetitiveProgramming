#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n = 3000;
    cout << n << ' ' << n << '\n';
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << "RGW"[(i+j)%3];
        }
        cout << '\n';
    }
}
