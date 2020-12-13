#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
using ld = long double;
using ll = long long;

signed main() {
#ifndef local
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
#endif // local
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<int> f(n+2);
    vector<ld> ans(n+2);
    for(int i = 1; i <= n; i++) cin >> f[i];
    for(int i = 1; i <= n; i++) {
        ld res = -1e18;
        for(int j = i; j <= n+1; j++) {
            res = max(res, (f[j] - ans[i-1]) / ld(j-i+1));
        }
        ans[i] = ans[i-1] + res;
    }
    for(int i = 1; i <= n; i++)
        cout << ll(floor(ans[i] * 100000 + 1e-7)) << '\n';
}
