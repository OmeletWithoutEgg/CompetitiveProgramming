#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
const int N = 200025, inf = 1e9, MOD = 998244353;

int a[21][21], pos[21][21];
int dp[21][1<<20];
int dp2[1<<20];
void modadd(int &a, int v) {
    a += v;
    a %= MOD;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> m >> n;
    for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) cin >> a[i][j], --a[i][j], pos[i][a[i][j]] = j;
    dp[0][0] = 1;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < (1<<n); j++) dp2[j] = dp[i][j];
        for(int t = 0; t+1 < n; t++) {
            for(int j = 0; j < (1<<n); j++) {
                if(!(j >> t & 1) && !(j >> (t+1) & 1)) {
                    int k = j | (1<<t) | (1<<(t+1));
                    modadd(dp2[k], dp2[j]);
                }
            }
        }
        // for(int j = 0; j < (1<<n); j++) cout << dp[i][j] << ' ';
        // cout << '\n';
        // for(int j = 0; j < (1<<n); j++) cout << dp2[j] << ' ';
        // cout << '\n';
        for(int j = 0; j < (1<<n); j++) {
            int nxt = 0;
            for(int t = 0; t < n; t++) if(!(j >> t & 1)) {
                int p = i+1<m ? pos[i+1][a[i][t]] : t;
                nxt |= 1 << p;
            }
            // debug(bitset<4>(j), bitset<4>(nxt));
            modadd(dp[i+1][nxt], dp2[j]);
        }
    }
    cout << dp2[(1<<n)-1] << '\n';
}
