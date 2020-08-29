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
 
#ifdef local
#include <bits/extc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}
#else
#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/extc++.h>
#include <bits/stdc++.h>
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define get_pos(v,x) int(lower_bound(begin(v),end(v),x)-begin(v))
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
constexpr ld PI = acos(-1), eps = 1e-7;
constexpr ll N = 200025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct Segtree {
    int sum[N<<1];
    int rev[N];
    int n;
    void init(int v[], int _n) {
        n = _n;
        for(int i = 0; i < n; i++) sum[i+n] = v[i], rev[i] = 0;
        for(int i = n-1; i > 0; i--) sum[i] = sum[i<<1] + sum[i<<1|1];
    }
    void pull(int p) {
        for(int L=2; p>0; p>>=1, L<<=1) {
            sum[p>>1] = sum[p] + sum[p^1];
            if(rev[p>>1]) sum[p>>1] = L*3 - sum[p>>1];
        }
    }
    int upd(int p, int L) {
        int res = L * 3 - sum[p] * 2;
        sum[p] = L * 3 - sum[p];
        if(p < n) rev[p] = !rev[p];
        return res;
    }
    void push(int p) {
        for(int h = __lg(n); h >= 0; --h) {
            int i = p>>h;
            if(!rev[i>>1]) continue;
            upd(i, 1<<h);
            upd(i^1, 1<<h);
            rev[i>>1] = 0;
        }
    }
    int flip(int l, int r) {
        int res = 0, L = l, R = r, len = 1;
        push(l+n), push(r-1+n);
        for(l+=n, r+=n; l<r; l>>=1, r>>=1, len<<=1) {
            if(l&1) res += upd(l++, len);
            if(r&1) res += upd(--r, len);
        }
        pull(L+n), pull(R-1+n);
        return res;
    }
} sgt;
vector<int> g[N];
int leaf[N];
int deg[N];
ll ans;
int sz[N], mxs[N], dep[N], pa[N];
void dfs(int i, int p) {
    leaf[i] = deg[i] <= 1;
    dep[i] = dep[p] + 1;
    pa[i] = p;
    sz[i] = 1;
    for(int j: g[i]) if(j != p) {
        dfs(j, i);
        leaf[i] += leaf[j];
        sz[i] += sz[j];
        if(mxs[i] == 0 || sz[mxs[i]] < sz[j]) mxs[i] = j;
    }
    if(leaf[i] & 1)
        leaf[i] = 1;
    else
        leaf[i] = 2;
    ans += leaf[i];
}
int top[N], vis[N], tot, v[N];
void DFS(int i, int p, int t) {
    top[i] = t;
    vis[i] = tot++;
    v[vis[i]] = leaf[i];
    if(mxs[i]) DFS(mxs[i], i, t);
    for(int j: g[i]) if(j != p && j != mxs[i]) DFS(j, i, j);
}
void toggle(int x) {
    while(pa[top[x]]) {
        int tx = top[x];
        ans += sgt.flip(vis[tx], vis[x]+1);
        x = pa[tx];
    }
    ans += sgt.flip(vis[top[x]], vis[x]+1);
}
signed main() {
    /* freopen("input1.txt", "r", stdin); */
    /* freopen("pans.out", "w", stdout); */
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b), g[b].pb(a);
        ++deg[a], ++deg[b];
    }
    int root = -1;
    for(int i = 1; i <= 3; i++) if(g[i].size() > 1) root = i;
    dfs(root, 0);
    DFS(root, 0, root);
    sgt.init(v, n);
    debug(tot);
    int ans0 = ans;
    while(q--) {
        int d;
        cin >> d;
        vector<int> a(d);
        for(int &x: a) cin >> x;
        bool bad = (leaf[root] ^ d) & 1;
        for(int x: a) {
            if(deg[x] == 1) bad = !bad;
            else toggle(x);
            ++deg[x];
        }
        if(bad) cout << -1 << '\n';
        else cout << ans+d-2 << '\n';
        for(int x: a) {
            --deg[x];
            if(deg[x] != 1) toggle(x);
        }
    }
}
