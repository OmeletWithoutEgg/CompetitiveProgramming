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

#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/extc++.h>
#ifdef local
#define debug(x) (cerr<<#x<<" = "<<(x)<<'\n')
#else
#define debug(x) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define siz(v) (ll(v.size()))
#define get_pos(v,x) (lower_bound(all(v),x)-begin(v))
#define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))
#define pb emplace_back
#define ff first
#define ss second
#define mid (l+(r-l>>1))
#define mem(v,x) memset(v,x,sizeof v)

using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;
template <typename T> using max_heap = __gnu_pbds::priority_queue<T,less<T> >;
template <typename T> using min_heap = __gnu_pbds::priority_queue<T,greater<T> >;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr ld PI = acos(-1), eps = 1e-9;
constexpr ll N = 100025, INF = 1e18, MOD = 1000000007, K = 1000025, inf = 1e9;
constexpr ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}
constexpr inline ll cdiv(ll x, ll m) { return (x+m-1)/m; } // ceiling divide, x/m for flooring divide
template <typename T> void M(T &x, ll m=MOD){x%=m; if(x<0) x+=m;}

int n,dp[K],DP[K],w[N],c[N],W;
int dq[K];
ll v[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> w[i] >> v[i] >> c[i];
    cin >> W;
    for(int i = 0; i < n; i++) {
        //sum = min(W,sum+w[i]*c[i]);
        for(int j = 0; j < w[i]; j++) {
            int head = 0, tail = 0;
            dq[tail++] = 0;
            for(int x = 1; j+x*w[i] <= W; x++) {
                while(tail-head && x-dq[head] > c[i]) ++head;
                DP[j+w[i]*x] = dp[j+w[i]*dq[head]] + v[i]*(x-dq[head]);
                while(tail-head && dp[j+w[i]*x]-v[i]*x >= dp[j+w[i]*dq[tail-1]]-v[i]*dq[tail-1]) --tail;
                dq[tail++] = x;
            }
        }
        for(int j = 0; j <= W; j++) dp[j] = max(dp[j],DP[j]);
    }
    cout << dp[W] << '\n';
}
