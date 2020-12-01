#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v), end(v)
using namespace std;
using ll = long long;

ll calc(vector<string> v) {
    int n = v.size(), m = v[0].size();
    vector<vector<array<ll,2>>> dp(n, vector<array<ll,2>>(m));
    dp[0][0][0] = 1;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        if(i == n-1 && j == m-1) continue;
        if(v[i][j] == '.') {
            dp[i+1][j][0] += dp[i][j][0];
            dp[i][j+1][1] += dp[i][j][1];
        } else {
            ll s = dp[i][j][0] + dp[i][j][1];
            if(v[i][j] != 'r')
                dp[i+1][j][0] += s;
            if(v[i][j] != 'd')
                dp[i][j+1][1] += s;
        }
    }
    return dp[n-1][m-1][0] + dp[n-1][m-1][1];
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
#if 0
    int n, m;
    cin >> n >> m;
    vector<string> v(n, string(n, '.'));
    for(int i = 0; i < n-1; i++) {
        v[i] = string(m, 'X');
        v[i].back() = 'd';
    }
    v[n-1] = string(m, 'r');
    v[n-1].back() = '.';
    cout << n << ' ' << n << '\n';
    for(int i = 0; i < n; i++) cout << v[i] << '\n';
    cout << ll(1e18) << '\n';
    cout << calc(v) << '\n';
#else
    ll k;
    cin >> k;
    bool f = k >= 16 && k <= 19;
    int n = 0;
    while((1LL<<n) <= k) ++n;
    k -= (1LL<<n-1);
    debug(k);
    n += 1;
    debug(n);
    vector<string> v(n, string(n, '.'));
    for(int i = 0; i < n; i++) v[i][n-1] = 'd', v[n-1][i] = 'r';
    v[n-1][n-1] = '.';
    for(int i = 0; i < n-2; i++) {
        v[i][i] = 'X';
        if(i+1 != n-1) v[i+1][i] = 'r';
        v[i][i+1] = 'd';
        if(k >> i & 1) {
            v[i][i+1] = 'X';
            k -= 1LL << i;
        }
    }
    if(f) {
        --n;
        v.pop_back();
        for(int i = 0; i < n; i++) v[i].pop_back();
        for(int i = 0; i < n; i++) v[i].back() = 'd';
        v[n-1] = string(n, 'r');
        v[n-1][n-1] = '.';
    }
    cout << n << ' ' << n << '\n';
    for(int i = 0; i < n; i++) cout << v[i] << '\n';
    debug(calc(v));
#endif
}
