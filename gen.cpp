#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n = 20;
    int m = 8;
    cout << m << ' ' << n << '\n';
    int a[20] = {1, 2, 4, 8, 1, 2, 4, 8, 1, 2, 4, 8, 1, 2, 4, 8, 1, 2, 4, 5};
    for(int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
    cerr << accumulate(a,a+n,0) << '\n';
}
