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
using ost = std::ostream;
#define DESTL(STL, BEG, END, OUT) \
    template <typename ...T> ost& operator<<(ost &O, std::STL<T...> v) { int f=0; for(auto x: v) O << (f++ ? ", " : BEG) << OUT; return O << END; }
DESTL(deque, "[", "]", x); DESTL(vector, "[", "]", x);
DESTL(set, "{", "}", x); DESTL(multiset, "{", "}", x); DESTL(unordered_set, "{", "}", x);
DESTL(map , "{", "}", x.first << ":" << x.second); DESTL(unordered_map , "{", "}", x.first << ":" << x.second);
template <typename U, typename V> ost& operator<<(ost &O, std::pair<U,V> p) { return O << '(' << p.first << ',' << p.second << ')'; }
template <typename T, size_t N> ost& operator<<(ost &O, std::array<T,N> a) { int f=0; for(T x: a) O << (f++ ? ", " : "[") << x; return O << "]"; }
template <typename T, size_t ...I> ost& prtuple(ost &O, T t, std::index_sequence<I...>) { return (..., (O << (I ? ", " : "(") << std::get<I>(t))), O << ")"; }
template <typename ...T> ost& operator<<(ost &O, std::tuple<T...> t) { return prtuple(O, t, std::make_index_sequence<sizeof...(T)>()); }
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
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

signed main() {
    debug(0);
    ios_base::sync_with_stdio(0), cin.tie(0);
    int m;
    cin >> m;
    vector<pair<int,int>> p(m);
    for(auto &[a, b]: p) cin >> a >> b;
    vector<int> X, Y;
    for(auto [a, b]: p) X.pb(a), Y.pb(b);
    sort_uni(X), sort_uni(Y);
    int n = X.size() + Y.size();
    vector<vector<pair<int,int>>> g(n+1);
    for(int i = 0; i < m; i++) {
        auto [a, b] = p[i];
        a = get_pos(X, a), b = get_pos(Y, b) + X.size();
        g[a].pb(b, i), g[b].pb(a, i);
    }
    int tot = m;
    for(int i = 0; i < n; i++) if(g[i].size() & 1) g[i].pb(n, tot), g[n].pb(i, tot), ++tot;
    vector<int> vis(tot), ans(tot), cur(n+1);
    vector<tuple<int,int,int>> v;
    function<void(int)> dfs = [&](int i) -> void {
        while(cur[i] < int(g[i].size())) {
            auto [j, id] = g[i][cur[i]++];
            if(!vis[id]) {
                vis[id] = true;
                dfs(j);
                v.pb(i, j, id);
            }
        }
    };
    for(int i = 0; i <= n; i++) {
        v.clear();
        dfs(i);
        if(v.size() > 1) {
            if(get<1>(v[0]) != get<1>(v[1]) && get<1>(v[0]) != get<0>(v[1])) swap(get<0>(v[0]), get<1>(v[0]));
            for(int i = 0; i < int(v.size()); i++) {
                if(i && get<0>(v[i]) != get<1>(v[i-1])) {
                    swap(get<0>(v[i]), get<1>(v[i]));
                }
                ans[get<2>(v[i])] = (get<0>(v[i]) < get<1>(v[i]));
            }
        }
    }
    for(int i = 0; i < m; i++) cout << (ans[i] ? 'r' : 'b');
    cout << '\n';
}
