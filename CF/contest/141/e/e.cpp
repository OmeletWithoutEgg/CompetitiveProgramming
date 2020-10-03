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
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    std::cerr << "\033[1;32m(" << s << ") = (";
    ( (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")) , ... , void() );
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
constexpr ll N = 100025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct DisjointSets {
    vector<int> pa, rk;
    DisjointSets(int n) : pa(n), rk(n) { iota(all(pa), 0); }
    int anc(int x) { return x==pa[x] ? x : pa[x]=anc(pa[x]); }
    bool same(int x, int y) { return anc(x) == anc(y); }
    bool join(int x, int y) {
        if((x=anc(x)) == (y=anc(y))) return false;
        if(rk[x] < rk[y]) swap(x, y);
        return pa[y] = x, rk[x]!=rk[y]||++rk[x];
    }
};
struct Edge {
    int a, b, color;
};
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<Edge> E(m);
    for(int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        --a, --b;
        E[i] = {a, b, (c=='S')};
    }
    if(n % 2 == 0) return cout << -1 << '\n', 0;
    DisjointSets dsu(n);
    vector<int> ans;
    vector<int> must;
    for(int i = 0; i < m; i++) if(E[i].color == 0) dsu.join(E[i].a, E[i].b);
    for(int i = 0; i < m; i++) if(E[i].color == 1 && dsu.join(E[i].a, E[i].b)) must.pb(i);
    if(must.size() > (n-1)/2) return cout << -1 << '\n', 0;

    dsu = DisjointSets(n);
    for(int i: must) dsu.join(E[i].a, E[i].b), ans.pb(i);
    for(int i = 0; i < m; i++) if(must.size() < (n-1)/2 && E[i].color == 1 && dsu.join(E[i].a, E[i].b)) must.pb(i), ans.pb(i);
    if(must.size() < (n-1)/2) return cout << -1 << '\n', 0;
    for(int i = 0; i < m; i++) if(E[i].color == 0 && dsu.join(E[i].a, E[i].b)) ans.pb(i);
    for(int i = 0; i < n; i++) if(!dsu.same(i, 0)) return cout << -1 << '\n', 0;
    cout << ans.size() << '\n';
    for(int id: ans) cout << id+1 << ' ';
    cout << '\n';
}
