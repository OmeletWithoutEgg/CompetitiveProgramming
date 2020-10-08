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

vector<pll> g[N];
ll dis[N];
void dijkstra(int s) {
    mem(dis, -1);
    min_heap<pll> pq;
    pq.push({0, s});
    dis[s] = 0;
    while(!pq.empty()) {
        auto [d, i] = pq.top(); pq.pop();
        if(d != dis[i]) continue;
        for(auto [c, j]: g[i]) {
            if(dis[j] == -1 || dis[j] > dis[i] + c) {
                dis[j] = dis[i] + c;
                pq.push({dis[j], j});
            }
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    array<int,2> s, f;
    cin >> s[0] >> s[1] >> f[0] >> f[1];
    vector<array<int,2>> p(m);
    for(int i = 0; i < m; i++) cin >> p[i][0] >> p[i][1];
    int tot = m+1;
    map<int,int> cor[2];
    auto getId = [&](int c, int x) {
        if(cor[c].count(x)) return cor[c][x];
        return cor[c][x] = tot++;
    };
    for(int i = 0; i < m; i++) {
        for(int c = 0; c < 2; c++) {
            int id = getId(c, p[i][c]);
            g[i].pb(0, id);
            g[id].pb(0, i);
        }
    }
    int src = m;
    for(int c = 0; c < 2; c++) {
        int lastx = -1;
        int last = -1;
        debug(c);
        for(auto [x, id]: cor[c]) {
            debug(x, id);
            g[src].pb(abs(s[c]-x), id);
            if(last != -1) {
                g[id].pb(x - lastx, last);
                g[last].pb(x - lastx, id);
            }
            lastx = x;
            last = id;
        }
    }
    dijkstra(src);
    ll ans = abs(s[0]-f[0]) + abs(s[1]-f[1]);
    /* for(int i = 0; i < m; i++) cerr << dis[i] << ' '; */
    /* cerr << '\n'; */
    for(int i = 0; i < m; i++) if(dis[i] != -1) ans = min(ans, dis[i] + abs(p[i][0]-f[0]) + abs(p[i][1]-f[1]));
    cout << ans << '\n';
}
