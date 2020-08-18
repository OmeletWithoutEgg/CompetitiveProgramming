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
constexpr ld PI = acos(-1), eps = 1e-11;
constexpr ll N = 100025, INF = 1e18, MOD = 1000000007, K = 146, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}

int r1, r2, n, L, p[N], v[N], dp[N][2], mx[N][2];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    while(cin >> r1 >> r2 >> n >> L, r1) {
        L += n;
        for(int i = 0; i < n; i++) cin >> p[i];
        for(int i = 1; i < n; i++) v[i] = p[i]-p[i-1] - 1;
        v[n] = p[0]+L-p[n-1] - 1;
        dp[1][0] = mx[1][0] = 0;
        dp[1][1] = mx[1][1] = v[1];
        int ans = 0;
        for(int i = 2; i <= n; i++) {
            dp[i][0] = mx[i-2][0] + v[i];
            dp[i][1] = mx[i-2][1] + v[i];
            mx[i][0] = max(mx[i-1][0], dp[i][0]);
            mx[i][1] = max(mx[i-1][1], dp[i][1]);
            ans = max(ans, dp[i][0]);
            if(i != n) ans = max(ans, dp[i][1]);
        }
        cout << ans << '\n';
    }
}

