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

#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/extc++.h>
#ifdef local
#define debug(x) (cerr<<#x<<" = "<<(x)<<'\n')
#else
#define debug(x) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define siz(v) (ll(v.size()))
#define get_pos(v,x) (lower_bound(all(v),x)-begin(v))
#define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))
#define pb emplace_back
#define ff first
#define ss second
#define mid (l+(r-l>>1))
#define mem(v,x) memset(v,x,sizeof v)

using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;
template <typename T> using max_heap = __gnu_pbds::priority_queue<T,less<T> >;
template <typename T> using min_heap = __gnu_pbds::priority_queue<T,greater<T> >;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr ld PI = acos(-1), eps = 1e-9;
constexpr ll N = 100025, INF = 1e18, MOD = 1LL<<32, K = 20;
constexpr ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}
constexpr inline ll cdiv(ll x, ll m) { return (x+m-1)/m; } // ceiling divide, x/m for flooring divide
template <typename T> void M(T &x, ll m=MOD){x%=m; if(x<0) x+=m;}

int n,q;
int dep[N],pa[K][N];
vector<int> g[N];
void DFS(int i) {
    for(int j:g[i]) if(j!=pa[0][i]) pa[0][j]=i, dep[j]=dep[i]+1, DFS(j);
}
int LCA(int x,int y) {
    if(dep[x] < dep[y]) swap(x,y);
    int dif = dep[x]-dep[y];
    for(int i = K-1; i >= 0; i--) if(dif & (1<<i)) x = pa[i][x];
    if(x == y) return x;
    for(int i = K-1; i >= 0; i--) if(pa[i][x] != pa[i][y]) x = pa[i][x], y = pa[i][y];
    return pa[0][x];
}
int query(int x,int y,int k) {
    int v = LCA(x,y), dis = 0;
    if(v == x || v == y) {
        dis = abs(dep[x]-dep[y]);
        if(k > dis) return -1;
        if(dep[x] < dep[y]) k = dis-k, swap(x,y);
        for(int i = K-1; i >= 0; i--) if(k & (1<<i)) x = pa[i][x];
        return x;
    }else {
        dis = dep[x]+dep[y] - dep[v]*2;
        if(k > dis) return -1;
        if(k > dep[x]-dep[v]) k = dis-k, swap(x,y);
        for(int i = K-1; i >= 0; i--) if(k & (1<<i)) x = pa[i][x];
        return x;
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> q;
    for(int i = 1,a,b; i < n; i++) {
        cin >> a >> b;
        g[a].pb(b), g[b].pb(a);
    }
    DFS(1);
    for(int L = 1; L < K; L++) for(int i = 1; i <= n; i++) pa[L][i] = pa[L-1][pa[L-1][i]];
    for(int i = 0,a,b,k; i < q; i++) {
        cin >> a >> b >> k;
        cout << query(a,b,k) << '\n';
    }
}

