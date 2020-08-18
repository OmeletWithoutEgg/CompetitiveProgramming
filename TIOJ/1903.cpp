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
constexpr ld PI = acos(-1), eps = 1e-5;
constexpr ll N = 1<<19, INF = 1e18, MOD = 1000000007, K = 26, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}

pair<int,int> readEdge() {
    int a, b;
    cin >> a >> b;
    if(a > b) swap(a, b);
    return {a, b};
}
struct DisjointSets {
    int pa[N], sz[N], CC;
    vector<pair<int,int>> ops;
    void init(int n){iota(pa,pa+n,0),fill(sz,sz+n,1),CC=n,ops.clear();}
    int anc(int x){return x==pa[x] ? x : anc(pa[x]);}
    void uni(int x, int y) {
        if((x=anc(x)) == (y=anc(y))) return;
        if(sz[x] < sz[y]) swap(x, y);
        pa[y] = x, sz[x] += sz[y], --CC;
        //debug(CC);
        ops.pb(x, y);
    }
    void undo(int now) {
        while(ops.size() > now) {
            auto [x, y] = ops.back(); ops.pop_back();
            sz[x] -= sz[y];
            pa[y] = y;
            ++CC;
        }
    }
} dsu;
struct Segtree {
    vector<pair<int,int>> ed[N<<1];
    int n, ans[N];
    void add(int l, int r, pair<int,int> e) {
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) ed[l++].pb(e);
            if(r&1) ed[--r].pb(e);
        }
    }
    void dfs(int i = 1) {
        int now = dsu.ops.size();
        for(auto [a, b]: ed[i]) dsu.uni(a, b);
        if(i >= n) {
            ans[i-n] = dsu.CC;
        } else {
            dfs(i<<1);
            dfs(i<<1|1);
        }
        dsu.undo(now);
    }
    void init(int _n) {
        n = _n;
        for(int i = 0; i < n*2; i++) ed[i].clear();
    }
} seg;

template <> struct std::hash<pair<int,int>> {
    ll operator()(const pair<int,int> &p) const {
        return p.first * MOD + p.second;
    }
};
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    seg.init(1<<__lg(m+q)+1);
    unordered_map<pair<int,int>,int> last, cnt;
    for(int i = 0; i < m; i++) {
        pair<int,int> e = readEdge();
        last[e] = 0;
        ++cnt[e];
    }
    for(int i = 1; i <= q; i++) {
        char c;
        cin >> c;
        pair<int,int> e = readEdge();
        if(c == 'N') {
            if(!cnt.count(e)) cnt[e] = 1, last[e] = i;
            else ++cnt[e];
        } else if(c == 'D') {
            if(--cnt[e] == 0) {
                seg.add(last[e], i, e);
                last.erase(e);
                cnt.erase(e);
            }
        }
    }
    for(auto [e, t]: last) {
        seg.add(t, q+1, e);
    }
    dsu.init(n);
    seg.dfs();
    for(int i = 1; i <= q; i++) cout << seg.ans[i] << '\n';
    //cout << '\n';
}


signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--) solve();
}
