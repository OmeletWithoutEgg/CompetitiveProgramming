#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int &x: a) cin >> x;
    int ans = 0;
    for(int s = 0; s < (1<<n); s++) {
        int mx = 0;
        for(int i = 0; i < n; i++) if(s>>i&1) mx = max(mx, a[i]);
        ans = (ans + mx) % MOD;
    }
    cout << ans << '\n';
}
