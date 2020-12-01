#include <bits/stdc++.h>

using namespace std;

signed main() {
    ofstream fout("02.in");
    int H = 200, W = 200, K = 100;
    fout << H << ' ' << W << ' ' << K << '\n';
    mt19937 rng;
    for(int i = 0; i < 200; i++) {
        array<int,2> a, b;
        do {
            a[0] = uniform_int_distribution<int>(0, H-1)(rng);
            a[1] = uniform_int_distribution<int>(0, H-1)(rng);
            b[0] = uniform_int_distribution<int>(0, W-1)(rng);
            b[1] = uniform_int_distribution<int>(0, W-1)(rng);
        } while(a == b);
        fout << a[0] << ' ' << a[1] << ' ' << b[0] << ' '<< b[1] << '\n';
    }
    fout << -1 << '\n';
}
