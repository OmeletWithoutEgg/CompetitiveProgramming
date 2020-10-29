#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m));
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> v[i][j];
    vector<vector<int>> dp(n, vector<int>(m));
    int best = -1e9;
    auto calc = [&]() {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                dp[i][j] = v[i][j];
                if(i) dp[i][j] = max(dp[i][j], dp[i-1][j] - 1);
                if(j) dp[i][j] = max(dp[i][j], dp[i][j-1] - 1);
                best = max(best, dp[i][j] - v[i][j] - 1);
            }
        }
    };
    calc();
    reverse(all(v));
    calc();
    for(auto &u: v) reverse(all(u));
    calc();
    reverse(all(v));
    calc();
    cout << best << '\n';
}
