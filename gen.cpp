#include <bits/stdc++.h>

using namespace std;

signed main() {
    int k = 4900;
    int n = 5000, q = k * 2;
    cout << n << ' ' << q << '\n';
    for(int i = 1; i <= k; i++) {
        cout << 2 << ' ' << i << ' ' << i+1 << '\n';
    }
    for(int i = k; i >= 1; i--) {
        cout << 2 << ' ' << i << ' ' << n << '\n';
    }
}
