#include <bits/stdc++.h>
#ifdef local
#define debug(...) QQBX(#__VA_ARGS__, __VA_ARGS__)
void QQBX(const char *s) {}
template <typename H, typename ...T> void QQBX(const char *s, const H&h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if(sizeof...(T)) QQBX(++s, args...);
}
#define safe std::cerr<<__PRETTY_FUNCTION<<" line "<<__LINE__<<" safe\n";
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back

using namespace std;
typedef long long ll;
const int N = 525, inf = 1e9;

int n;
vector<int> g[N];
array<int,N> dis[N], dep;
void dfs(int i, int p = 0, int d = 0) {
    dep[i] = d;
    for(int j: g[i]) if(j != p) dfs(j, i, d+1);
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b), g[b].pb(a);
    }
    for(int i = 1; i <= n; i++) {
        dfs(i);
        dis[i] = dep;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) for(int j = 1; j < i; j++) for(int k = 1; k < j; k++)
        if(dis[i][j] == dis[j][k] && dis[j][k] == dis[k][i])
            ++ans;
    cout << ans << '\n';
}
