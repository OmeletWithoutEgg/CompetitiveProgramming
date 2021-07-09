#include <bits/stdc++.h>
using namespace std;

int p[100000];
signed main() {
    int n = 41000;
    cout << n << '\n';
    iota(p, p+n+1, 0);
    shuffle(p+1, p+n+1, mt19937(7122));
    for (int i = 1; i <= n; i++)
        cout << i << ' ' << p[i] + n << '\n';
    // for (int i = 1; i <= n; i++) cout << i << ' ' << i+n << '\n';
}
