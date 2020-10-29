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
    template <typename ...T> ost& operator<<(ost &O, std::STL<T...> v) { int f=0; O << BEG; for(auto x: v) O << (f++ ? ", " : "") << OUT; return O << END; }
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
constexpr ll N = 18, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

int wei[N];
int dep[N];
vector<int> g[N];
bool vis[N];
int n, m;
void dfs(int i) {
    if(vis[i]) return;
    vis[i] = true;
    for(int j: g[i]) dfs(j), dep[i] |= dep[j];
}
vector<int> topoSort() {
    queue<int> q;
    vector<int> deg(n), res;
    for(int i = 0; i < n; i++) for(int j: g[i]) ++deg[j];
    debug(deg);
    for(int i = 0; i < n; i++) if(deg[i] == 0) q.push(i);
    while(!q.empty()) {
        int i = q.front(); q.pop();
        debug(i);
        res.pb(i);
        for(int j: g[i]) if(--deg[j] == 0) q.push(j);
    }
    return res;
}
int dp[1 << N], nxt[1 << N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        wei[a] += c;
        wei[b] -= c;
        g[a].pb(b);
    }
    vector<int> ord = topoSort();
    debug(ord);
    for(int i = 0; i < n; i++) dfs(i);
    for(int i = 1; i < (1<<n); i++) dp[i] = inf;
    for(int t = 0; t < n; t++) {
        for(int x: ord) {
            for(int s = 0; s < (1<<n); s++) {
                if(s >> x & 1) continue;
                if(~dep[x] & s) continue;
                debug(s);
                nxt[s | (1 << x)] = min(nxt[s | (1<<x)], dp[s] + wei[x] * t);
            }
            for(int s = 0; s < (1<<n); s++) dp[s] = nxt[s];
        }
    }
    cout << dp[(1<<n)-1] << '\n';
}
