#include <bits/stdc++.h>
#ifdef local
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> void qqbx(const char *s, const H &h, T ...args) {
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
#define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))

using namespace std;
typedef long long ll;
const int N = 100025;

vector<int> g[N];
int vis[N];
ll ans = 0;
int dfs(int i) {
    int s = 1;
    vis[i] = 1;
    for(int j: g[i]) if(!vis[j]) s += dfs(j);
    return s;
}
int dfs2(int i, int n) {
    int s = 0;
    vis[i] = -1;
    for(int j: g[i]) if(~vis[j]) {
        int t = dfs2(j, n);
        ans += 1LL * t * s;
        s += t;
    }
    ans += 1LL * s * (n-s-1);
    return ++s;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b), g[b].pb(a);
    }
    for(int i = 1; i <= n; i++) if(!vis[i]) {
        int s = dfs(i);
        dfs2(i, s);
    }
    cout << ans*2 << '\n';
}
