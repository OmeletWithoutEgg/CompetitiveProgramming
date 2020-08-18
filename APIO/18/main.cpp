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

#define int ll
int vis[N], low[N], tot;
int bccn, bcc[N], ap[N], bccAp[N];
vector<int> stk, g[N], BCT[N], bccv[N];
int sz[N], ans;
void dfs(int i, int p) {
    bool isAp = false;
    int child = 0;
    vis[i] = low[i] = ++tot;
    stk.pb(i);
    for(int j: g[i]) {
        if(!vis[j]) {
            // tree edge
            dfs(j, i);
            ++child;
            low[i] = min(low[i], low[j]);
            if(low[j] >= vis[i]) {
                isAp = true;
                int x;
                ++bccn;
                do {
                    x = stk.back(), stk.pop_back();
                    bcc[x] = bccn;
                    bccv[bccn].pb(x);
                } while(x != j);
                bcc[i] = bccn;
                bccv[bccn].pb(i);
            }
        } else if(j != p) {
            // back edge
            low[i] = min(low[i], vis[j]);
        }
    }
    if(!p && child < 2) isAp = false;
    if(isAp) ap[i] = true;
}
int getSz(int i, int p) {
    int s = sz[i];
    for(int j: BCT[i]) {
        if(j == p) continue;
        s += getSz(j, i);
    }
    return s;
}
int DFS(int i, int p, int n) {
    vis[i] = true;
    int S = bccv[i].size();
    int an = 0;
    for(int j: BCT[i]) {
        if(j == p) continue;
        int s = DFS(j, i, n);
        if(!bccAp[i]) an += s * S;
        S += s;
    }
    {
        int s = n-S;
        if(!bccAp[i]) an += s * S;
    }
    an += (bccv[i].size()-1)*(bccv[i].size()-2);
    an *= bccv[i].size();
    ans+=an;
    debug(i, an);
    return S;
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
    dfs(1, 0);
    for(int i = 1; i <= n; i++) if(ap[i]) bccAp[bcc[i]=++bccn] = true;
    for(int i = 1; i <= bccn; i++) {
        for(int j: bccv[i]) if(bccAp[bcc[j]]) {
            BCT[i].pb(bcc[j]);
            BCT[bcc[j]].pb(i);
        }
    }
    for(int i = 1; i <= n; i++) ++sz[bcc[i]];
    for(int i = 1; i <= bccn; i++) sort_uni(BCT[i]);
    for(int i = 1; i <= bccn; i++) debug(sz[i], bccAp[i]);
    for(int i = 1; i <= bccn; i++) for(int j: BCT[i]) cout << i << ", " << j << '\n';
    for(int i = 1; i <= bccn; i++) vis[i] = 0;
    for(int i = 1; i <= bccn; i++) if(!vis[i]) {
        int s = getSz(i, 0);
        /* ans += 1LL*s*(s-1)*(s-2); */
        if(!s) continue;
        DFS(i, 0, s);
    }
    cout << ans << '\n';
}
