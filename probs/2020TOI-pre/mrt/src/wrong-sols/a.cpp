#include <bits/stdc++.h>

using namespace std;
using ld = long double;

ll modpow(ll a, ll p, ll m) {
    // a^p % m
    ll res = 1;
    while (p) {
        if (p & 1)
            res = res * a % m;
        a = a * a % m;
        p >>= 1;
    }
    return res;
}
signed main() {
    int T;
    cin >> T;
    while (T--) {
        int M;
        int a, b, x1, y1, x2, y2;
        cin >> M >> a >> b >> x1 >> y1 >> x2 >> y2;
        int m = 1LL * (y2 - y1 + M) * modpow(x2 - x1 + M, M - 2, M) % M;
        int x3 = m*m - x1 - x2;
        // int x3 = (1LL * m * m % M - x1 - x2 + M + M) % M;
        int y3 = (y2 - 1LL * (y1 - y2 + M) * (x2 - x3 + M) % M * modpow(x1 - x2 + M, M - 2, M) % M + M) % M;
        cout << x3 << ' ' << y3 << '\n';
    }
}
