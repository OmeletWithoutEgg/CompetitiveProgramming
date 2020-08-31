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
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 1<<7, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

typedef vector<vector<int>> mat;
mat mul(const mat &a, const mat &b) {
    mat c(a.size(), vector<int>(b[0].size()));
    for(int i = 0; i < a.size(); i++) for(int k = 0; k < a[i].size(); k++) for(int j = 0; j < b[k].size(); j++) c[i][j] = (c[i][j] + 1LL*a[i][k]*b[k][j]) % MOD;
    return c;
}
mat tran(int a, int b) {
    auto calc = [](int s, int t, int len) -> int {
        int dp[2] = {0, 1};
        for(int i = 0; i < len; i++) {
            int DP[2] = {}, d = !((s&t) >> i & 1);
            DP[0] = (dp[0]+dp[1]) % MOD;
            DP[1] = (dp[0]+d*dp[1]) % MOD;
            dp[0] = DP[0], dp[1] = DP[1];
            /* debug(dp[0], dp[1]); */
        }
        return dp[1];
    };
    int M = ((1<<b-a)-1) << a;
    /* debug(M, a, b); */
    mat F(1<<a, vector<int>(1<<b));
    for(int i = 0; i < (1<<a); i++) for(int j = 0; j < (1<<b); j++) F[i][j] = calc(i|M, j, b);
    /* pr(F); */
    return F;
}
mat fpw(mat e, int p) {
    assert(e.size() == e[0].size());
    mat r(e.size(), vector<int>(e[0].size()));
    for(int i = 0; i < e.size(); i++) r[i][i] = 1;
    while(p) {
        if(p & 1) r = mul(r, e);
        e = mul(e, e);
        p >>= 1;
    }
    return r;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int width[8] = {};
    for(int i = 1; i <= 7; i++) cin >> width[i];
    mat res(1, vector<int>(1, 1));
    int last = 0;
    for(int i = 1; i <= 7; i++) {
        if(width[i]) {
            res = mul(res, tran(last, i));
            res = mul(res, fpw(tran(i, i), width[i]-1));
            last = i;
        }
    }
    cout << res[0][(1<<last)-1] << '\n';
}
