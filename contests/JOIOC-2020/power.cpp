#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename H, typename ...T> void qqbx(const char *s, const H&h, T&&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)
using namespace std;
const int N = 200025;

vector<int> g[N];
int dp[N][2];
int v[N];
void dfs(int i, int p) {
    for(int j: g[i]) if(j != p) dfs(j, i);
    if(v[i]) {
        int sum = 0;
        for(int j: g[i]) if(j != p) {
            dp[i][0] = max(dp[i][0], dp[j][0]);
            dp[i][0] = max(dp[i][0], dp[j][1]+1);
            sum += dp[j][1];
        }
        --sum;
        dp[i][1] = max(1, sum);
    } else {
        int sum = 0;
        for(int j: g[i]) if(j != p) {
            dp[i][0] = max(dp[i][0], dp[j][0]);
            sum += dp[j][1];
        }
        dp[i][0] = max(dp[i][0], sum);
        dp[i][1] = max(0, sum);
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b), g[b].pb(a);
    }
    string s;
    cin >> s;
    for(int i = 0; i < n; i++) if(s[i] == '1') v[i+1] = 1;
    dfs(1, 0);
    debug(dp[2][0], dp[2][1]);
    cout << max(dp[1][0], dp[1][1]) << '\n';
}
