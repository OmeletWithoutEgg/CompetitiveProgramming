#include <bits/stdc++.h>

using namespace std;
const int inf = 1e9;
using cd = complex<long double>;
const long double PI = acos(-1);

signed main() {
    int n = 300;
    int q = 300;
    cout << n << ' ' << q << '\n';
    mt19937 rng(712);
    for(int i = 0; i < n; i++)
        cout << rng() % 10<< ' ';
    cout << '\n';
    for(int i = 0; i < q; i++) {
        int k = rng() % 4;
        int l = rng() % n + 1;
        int r = rng() % n + 1;
        if(l > r) swap(l, r);
        if(k == 0 || k == 1) {
            int x = rng() % 10;
            cout << k+1 << ' ' << l << ' ' << r << ' ' << x << '\n';
        } else {
            cout << k+1 << ' ' << l << ' ' << r << '\n';
        }
    }
}
