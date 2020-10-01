
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
    std::cerr << "\033[1;32m" << '(' << s << ')' << " = " << '(';
    constexpr int size = sizeof...(T);
    int cnt = size, dummy[size] = { (std::cerr << args << (--cnt ? ", " : ")\033[0m\n"), 0)... };
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
constexpr ll N = 1025, INF = 1e18, MOD = 998244353, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

ll dp[N][N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<tuple<int,int,int>> V;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        int x;
        cin >> x;
        V.pb(x, i, j);
    }
    sort(all(V));
    ll sx = 0, sy = 0, s2 = 0, sdp = 0;
    for(int i = 0, j = 0; i < n*m; i = j) {
        ll tx = 0, ty = 0, t2 = 0, tdp = 0;
        ll invi = modpow(i, MOD-2);
        for(j = i; j < n*m; j++) {
            if(get<0>(V[i]) != get<0>(V[j])) break;
            auto [val, x, y] = V[j];
            dp[x][y] = i ? (1LL*x*x*i%MOD+1LL*y*y*i%MOD - 2LL*x*sx%MOD - 2LL*y*sy%MOD + s2 + sdp + MOD*2) % MOD : 0;
            dp[x][y] = dp[x][y] * invi % MOD;
            tx = (tx + x) % MOD;
            ty = (ty + y) % MOD;
            t2 = (t2 + x*x+y*y) % MOD;
            tdp = (tdp + dp[x][y]) % MOD;
        }
        sx = (sx + tx) % MOD;
        sy = (sy + ty) % MOD;
        s2 = (s2 + t2) % MOD;
        sdp = (sdp + tdp) % MOD;
    }
    int r, c;
    cin >> r >> c;
    --r, --c;
    cout << dp[r][c] << '\n';
}
