#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    assert (cin >> n);
    assert (1 <= n && n <= 500);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int x;
            assert (cin >> x);
            assert (0 <= x && x <= 2000000);
        }
}
