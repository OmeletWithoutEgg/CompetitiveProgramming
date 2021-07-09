#include <bits/stdc++.h>
#define all(v) begin(v),end(v)
using namespace std;
signed main() {
    int n = 128;
    vector<int> p(n);
    mt19937 rng(1293);
    iota(all(p), 0);
    shuffle(all(p), rng);
    cout << n << ' ' << 1792 << ' ' << 1792 << '\n';
    for (int i = 0; i < n; i++)
        cout << p[i] << (i+1==n ? '\n' : ' ');
    for (int i = 0; i < n; i++)
        cerr << p[i] << (i+1==n ? '\n' : ' ');
}
