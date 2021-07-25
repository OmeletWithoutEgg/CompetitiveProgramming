#include <bits/stdc++.h>

using namespace std;

int readInt(int l, int r) {
    int x;
    assert (cin >> x && l <= x && x <= r);
    return x;
}
signed main() {
    int n = readInt(1, 200000);
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) a[i] = readInt(0, 1000000000);
    for (int i = 0; i < n; i++) b[i] = readInt(0, 1000000000);

    set<int> sa(a.begin(), a.end());
    set<int> sb(b.begin(), b.end());
    assert (sa.size() == sb.size() && (int)sa.size() == n);
}
