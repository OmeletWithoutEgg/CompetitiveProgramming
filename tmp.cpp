#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const int maxn = 200000 + 5;
const int inf = 1e9;
const ld pi = acos(-1);


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int x = 710;
    for (int i = 0; i < 50000; i++) {
        if (!(sin((i-1) * x) < sin(i * x)))
            cout << i << endl;
        cout << sin(i * x) << endl;
    }
}
