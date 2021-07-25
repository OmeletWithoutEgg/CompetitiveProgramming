#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    assert (cin >> n && 1 <= n && n <= 1000);
    vector<int> a(n);
    for (int i = 0; i < n; i++) assert (cin >> a[i] && 1 <= a[i] && a[i] <= 1024);
    assert (set<int>(a.begin(), a.end()).size() == n);
}
