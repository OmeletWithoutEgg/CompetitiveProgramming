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
constexpr ll N = 100025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + (x%m ? (x<0) ^ (m>0) : 0); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

ll fr[N] = {1};
ll way(pair<int,int> a, pair<int,int> b) {
    int n = b.first - a.first;
    int m = b.second - a.second;
    if(n < 0 || m < 0) return 0;
    ll C = fr[n+m] * modpow(fr[n]*fr[m], MOD-2) % MOD;
    debug(n, m, C);
    return fr[n+m] * modpow(fr[n]*fr[m], MOD-2) % MOD;
}
int dp[200][200], sum[200];
signed main() {
    for(int i = 1; i < N; i++) fr[i] = fr[i-1] * i % MOD;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<pair<int,int>> v(k);
    for(auto &[a, b]: v) cin >> a >> b, --a, --b;
    v.pb(0, 0);
    sort(all(v));
    dp[0][0] = 1;
    for(int i = 0; i <= k; i++) {
        for(int j = 0; j < i; j++) {
            for(int t = 1; t <= k; t++) {
                dp[i][t] = (dp[i][t] + dp[j][t-1] * way(v[j], v[i])) % MOD;
            }
        }
        for(int t = 0; t <= k; t++) {
            sum[t] = (sum[t] + dp[i][t] * way(v[i], {n-1, n-1})) % MOD;
        }
    }
    for(int t = 0; t <= k; t++) debug(t, sum[t]);
    int ans = 0;
    for(int t = 0; t <= k; t++) {
        int c = 0;
        for(int j = 0; t+j <= k; j++) {
            c = (c + (j&1 ? MOD-1 : 1) * sum[t+j]) % MOD;
        }
        ans = (ans + s * c) % MOD;
        s = (s+1)/2;
    }
    cout << ans << '\n';
}
