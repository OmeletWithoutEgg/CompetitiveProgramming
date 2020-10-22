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
constexpr ll N = 325, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e7;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

int dp[N][N][N];
vector<pair<int,int>> cond[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        cond[r].pb(l, x);
    }
    auto add = [](int &a, int v) {
        a = (a + v) % MOD;
    };
    dp[0][0][0] = 1;
    for(int i = 1; i <= n; i++) {
        // k -> j -> i;
        int lj = 0, rj = i-1;
        int lk = 0, rk = i-1;
        for(auto [P, x]: cond[i]) {
            if(x == 1) {
                rj = min(rj, P-1);
            } else if(x == 2) {
                lj = max(lj, P);
                rk = min(rk, P-1);
            } else if(x == 3) {
                lk = max(lk, P);
            }
        }
        debug(lj, rj, lk, rk);
        for(int j = lj; j <= rj; j++) {
            for(int k = lk; k <= rk && k < j; k++) {
                add(dp[i][j][k], dp[i-1][j][k]);
                for(int l = 0; l < max(j, 1); l++)
                    add(dp[i][j][k], dp[i-1][j][l]);
                for(int l = max(k, 1); l < i-1; l++)
                    add(dp[i][j][k], dp[i-1][l][k]);
            }
        }
    }
    int ans = 0;
    for(int j = 1; j < n; j++) for(int k = 1; k < j; k++) add(ans, dp[n][j][k] * 6LL % MOD);
    for(int j = 1; j < n; j++) add(ans, dp[n][j][0] * 6LL % MOD);
    add(ans, dp[n][0][0] * 3LL % MOD);
    cout << ans << '\n';
}
