//   __________________
//  | ________________ |
//  ||          ____  ||
//  ||   /\    |      ||
//  ||  /__\   |      ||
//  || /    \  |____  ||
//  ||________________||
//  |__________________|
//  \###################\
//   \###################\
//    \        ____       \
//     \_______\___\_______\
// An AC a day keeps the doctor away.

#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/extc++.h>
#ifdef local
#define debug(x) (cerr<<#x<<" = "<<(x)<<'\n')
#else
#include <bits/stdc++.h>
#define debug(x) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define siz(v) (ll(v.size()))
#define get_pos(v,x) (lower_bound(all(v),x)-begin(v))
#define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))
#define pb emplace_back
#define ff first
#define ss second
#define mem(v,x) memset(v,x,sizeof v)

using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;
template <typename T> using max_heap = std::priority_queue<T,vector<T>,less<T> >;
template <typename T> using min_heap = std::priority_queue<T,vector<T>,greater<T> >;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr ld PI = acos(-1), eps = 1e-11;
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 146, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}

int n, m, k, q;
vector<int> g[N];
int sz[N], pa[N], mxs[N], top[N], dep[N], vis[N], cnt[N], tot;
void dfs(int i, int p = 0) {
    sz[i] = 1, mxs[i] = 0, pa[i] = p;
    for(int j: g[i]) if(j != p) {
        dfs(j, i);
        sz[i] += sz[j];
        if(sz[j] > sz[mxs[i]]) mxs[i] = j;
    }
}
void deco(int i, int t, int p = 0) {
    vis[i] = ++tot, top[i] = t, dep[i] = dep[p] + 1;
    if(mxs[i]) deco(mxs[i], t, i);
    for(int j: g[i]) if(j != p && j != mxs[i]) deco(j, j, i);
}
void add(int a, int b) {
    //debug("add");
    while(top[a] != top[b]) {
        int ta = top[a], tb = top[b];
        if(dep[ta] < dep[tb]) swap(a,b), swap(ta,tb);
        //debug(a), debug(b);
        ++cnt[vis[ta]], --cnt[vis[a]+1];
        a = pa[ta];
        //int sum[100] = {}; for(int i = 1; i <= n; i++) sum[i] = cnt[i]+sum[i-1]; for(int i = 1; i <= n; i++) cout << !sum[vis[i]] << ' '; cout << '\n';
    }
    if(a != b) {
        if(dep[a] < dep[b]) swap(a,b);
    //debug(a), debug(b);
        ++cnt[vis[b]+1], --cnt[vis[a]+1];
    }
}
int query(int a, int b) {
    int res = 0;
    while(top[a] != top[b]) {
        int ta = top[a], tb = top[b];
        if(dep[ta] < dep[tb]) swap(a,b), swap(ta,tb);
        res += cnt[vis[a]] - cnt[vis[ta]-1];
        //debug(res);
        a = pa[ta];
    }
    if(a != b) {
        if(dep[a] < dep[b]) swap(a,b);
        assert(vis[b] < vis[a]);
        res += cnt[vis[a]] - cnt[vis[b]];
    }
    //debug(res);
    return res == 0;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m >> k >> q;
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        g[a].pb(b), g[b].pb(a);
    }
    dfs(1);
    deco(1,1);
    while(k--) {
        int a, b;
        cin >> a >> b;
        add(a,b);
    }
    for(int i = 1; i <= n; i++) cnt[i] += cnt[i-1];
    for(int i = 1; i <= n; i++) cnt[i] = !cnt[i];
    //for(int i = 1; i <= n; i++) cout << top[i] << ' '; cout << '\n';
    //for(int i = 1; i <= n; i++) cout << cnt[vis[i]] << ' '; cout << '\n';
    for(int i = 1; i <= n; i++) cnt[i] += cnt[i-1];
    while(q--) {
        int a, b;
        cin >> a >> b;
        cout << query(a, b) << '\n';
    }
}

