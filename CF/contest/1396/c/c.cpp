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
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

ll a[N];
ll A[N], B[N];
ll dp[N][2];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    ll r1, r2, r3, d;
    cin >> n >> r1 >> r2 >> r3 >> d;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) A[i] = min(r2, r1 * (a[i]+1)) + r1, B[i] = r1 * a[i] + r3;
    /* for(int i = 1; i <= n; i++) cerr << A[i] << ' '; cerr << '\n'; */
    /* for(int i = 1; i <= n; i++) cerr << B[i] << ' '; cerr << '\n'; */
    for(int i = 1; i <= n; i++) {
        dp[i][0] = min(dp[i-1][0], dp[i-1][1] + d*2) + B[i];
        dp[i][1] = min(dp[i-1][0], dp[i-1][1] + d*2) + A[i];
    }
    ll sum = d * (n-1);
    ll ans = min(dp[n][0], dp[n][1]) + sum;
    debug(dp[n][0], dp[n][1]);
    debug(ans);
    for(int i = n-1; i >= 1; i--) {
        sum += d + min(A[i], B[i]);
        ans = min(ans, sum + min(dp[i-1][0], dp[i-1][1] + d*2) + min(A[n]+d*2,B[n]));
    }
    cout << ans << '\n';
}
