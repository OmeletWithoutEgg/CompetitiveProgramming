#include <bits/stdc++.h>

using namespace std;

signed main() {
    const int n = 10000000;
    mt19937 rng(7122);
    cout << n << '\n';
    for(int i = 0; i < n; i++)
        cout << uniform_int_distribution<int>(0, 10)(rng) << '\n';
}
