#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
const int maxn = 300025;

int dp[1001][11];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int T, n, A;
    cin >> T >> n >> A;
    memset(dp, -1, sizeof dp);
    dp[0][0] = 0;
    for(int i = 0; i < n; i++) {
        int c, e, s;
        cin >> c >> e >> s;
        for(int t = 0; t <= T; t++) {
            for(int j = 0; j <= A; j++) {
                if(dp[t][j] == -1) continue;
                /* if(c <= j) { */
                /*     int k = j+e-c; */
                /*     if(t+c <= T && k <= A) */
                /*         dp[t+c][k] = max(dp[t+c][k], dp[t][j] + s); */
                /* } else { */
                for(int k = 0; k <= A; k++) {
                    int nt = t+j+e-k;
                    if(nt-t >= c && nt <= T && k >= e) {
                        dp[nt][k] = max(dp[nt][k], dp[t][j] + s);
                    }
                }
                /* } */
            }
        }
        /* for(int t = 0; t <= T; t++) */
        /*     for(int j = 0; j <= A; j++) */
        /*         if(t+j <= T && dp[t][j] != -1) */
        /*             debug(t, j, dp[t][j]); */
    }
    int ans = 0;
    for(int t = 0; t <= T; t++)
         for(int j = 0; j <= A; j++)
             if(t+j <= T && dp[t][j] != -1)
                 ans = max(ans, dp[t][j]);
    cout << ans << '\n';
}
/*
   9 1 10
   1 2 3
 */
