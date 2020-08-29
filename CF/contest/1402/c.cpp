#include <bits/stdc++.h>
#ifdef local
#define debug(...) QQBX(#__VA_ARGS__, __VA_ARGS__);
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
void QQBX(const char *s) {}
template <typename H, typename ...T> void QQBX(const char *s, const H& h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if(sizeof...(T)) QQBX(++s, args...);
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back

using namespace std;
typedef long long ll;
const int N = 100025, MOD = 1000000007;

vector<int> g[N];
ll dp[N][2];
ll cnt[2];
void dfs(int i, int p) {
    ll all = cnt[0]+cnt[1];
    ll all0 = cnt[0], all1 = cnt[1];
    for(int j: g[i]) if(j != p) {
        dfs(j, i);
        all = all * (dp[j][0]+dp[j][1]) % MOD;
        all0 = all0 * dp[j][0] % MOD;
        all1 = all1 * dp[j][1] % MOD;
    }
    dp[i][0] = all1;
    dp[i][1] = (all - all0 + MOD) % MOD;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, D;
    cin >> n >> D;
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b), g[b].pb(a);
    }
    cnt[1] = 1, cnt[0] = 0;
    for(int t = 0; t < 2; t++) {
        ll now[2] = {0, 1};
        for(int i = 1; i <= n; i++) {
            dfs(i, 0);
            now[0] = (now[0] + dp[i][0]) % MOD;
            now[1] = (now[1] + dp[i][1]) % MOD;
        }
        cout << cnt[0] << '\n';
        cout << cnt[1] << '\n';
        cnt[0] = now[0], cnt[1] = now[1];
    }
    cout << cnt[0] << '\n';
    cout << cnt[1] << '\n';
}
