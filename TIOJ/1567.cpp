
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
template <typename T> using max_heap = __gnu_pbds::priority_queue<T,less<T> >;
template <typename T> using min_heap = __gnu_pbds::priority_queue<T,greater<T> >;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr ld PI = acos(-1), eps = 1e-8;
constexpr ll N = 1000025, INF = 1e18, MOD = 998244353, K = 256, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + (x<0 ^ m>0) && (x%m); } // ceiling divide
constexpr ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}

ll n,r,x,y,ans;
pld seg[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> r;
    for(int i = 0; i < n; i++) {
        cin >> x >> y;
        if(abs(y) > r) return cout << -1 << '\n', 0;
        ld d = sqrt(r*r-y*y);
        seg[i] = {x+d, x-d};
    }
    sort(seg, seg+n);
    ld last = -INF;
    for(int i = 0; i < n; i++) if(seg[i].ss > last) {
        ++ans;
        last = seg[i].ff;
    }
    cout << ans << '\n';
}
