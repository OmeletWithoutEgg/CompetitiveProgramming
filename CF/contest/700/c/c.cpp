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
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct Dsu {
    vector<int> pa, rk;
    Dsu(int n) : pa(n), rk(n) { iota(all(pa), 0); }
    int anc(int x) { return x==pa[x] ? x : pa[x]=anc(pa[x]); }
    bool join(int x, int y) {
        if((x=anc(x)) == (y=anc(y))) return false;
        if(rk[x] < rk[y]) swap(x, y);
        return pa[y] = x, rk[x]!=rk[y]||++rk[x];
    }
};
struct Edge {
    int a, b, cost, id;
    bool used;
};
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    --s, --t;
    vector<Edge> E(m), tr;
    vector<vector<tuple<int,int,int>>> g(n);
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        E[i] = {a, b, c, i+1, false};
        g[a].pb(c, i+1, b);
        g[b].pb(c, i+1, a);
    }
    safe;
    sort(all(E), [](Edge &a, Edge &b){ return a.cost < b.cost; });
    {
        Dsu dsu(n);
        for(auto &e: E) {
            if(!e.used && dsu.join(e.a, e.b)) {
                tr.push_back(e);
                e.used = true;
            }
        }
    }
    auto calc = [&](int del) -> pair<int,int> {
        // s -> t, use edge in T and dsu.
        // delete one edge and s, t become not connnected.
        vector<int> vis(n), low(n);
        int tot = 0;
        int ans = -1;
        int ansid = -1;
        function<bool(int,int,int)> dfs = [&](int i, int eid, int ec) -> bool {
            bool hast = (i == t);
            vis[i] = low[i] = ++tot;
            for(auto [cost, id, to]: g[i]) {
                if(id == del || id == eid) continue;
                if(!vis[to]) {
                    hast |= dfs(to, id, cost);
                    low[i] = min(low[i], low[to]);
                } else {
                    low[i] = min(low[i], vis[to]);
                }
            }
            if(low[i] == vis[i]) {
                if(hast && eid != -1) {
                    if(ans == -1 || ans > ec) {
                        ans = ec;
                        ansid = eid;
                    }
                }
            }
            return hast;
        };
        if(!dfs(s, -1, 0)) return {0, -1};
        return {ans, ansid};
    };
    /* sort(all(tr), [](Edge &a, Edge &b){ return a.cost < b.cost; }); */
    auto [ans, vv] = calc(0);
    vector<int> choice;
    if(vv != -1) choice.pb(vv);
    for(auto &e: tr) {
        auto [C, id] = calc(e.id);
        /* debug(C, id, e.cost, e.id); */
        if(C != -1 && (ans == -1 || ans > C + e.cost)) {
            ans = C + e.cost;
            choice = vector<int>{e.id};
            if(id != -1) choice.pb(id);
        }
    }
    cout << ans << '\n';
    if(ans != -1) {
        sort(all(choice));
        cout << choice.size() << '\n';
        for(int x: choice) cout << x << ' ';
        cout << '\n';
    }
}
