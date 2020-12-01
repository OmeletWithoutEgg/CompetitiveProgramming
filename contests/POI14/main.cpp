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
const int N = 5025, inf = 1e9;

int n;
vector<int> g[N];
void dfs(int i, int p, int d, vector<int> &deps) {
    deps.pb(d);
    for(int j: g[i]) if(j != p) dfs(j, i, d+1, deps);
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b), g[b].pb(a);
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        vector<int> cnt(n), tmp;
        for(int j: g[i]) {
            tmp.clear();
            dfs(j, i, 0, tmp);
            for(int d: tmp) ans += 1LL * cnt[d] * (cnt[d]-1) / 2;
            for(int d: tmp) ++cnt[d];
        }
    }
    cout << ans << '\n';
}
