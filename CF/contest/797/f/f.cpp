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
    int cnt = sizeof...(T);
    std::cerr << "\033[1;32m(" << s << ") = (";
    ( (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")) , ... , void() );
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
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<ll> mice(n);
    vector<pair<ll,ll>> hole(m);
    for(ll &x: mice) cin >> x;
    int tot = 0;
    for(auto &[p, c]: hole) cin >> p >> c, tot += c;
    if(tot < n) return cout << -1 << '\n', 0;
    sort(all(mice));
    sort(all(hole));
    vector<ll> nxt(n, INF), dp(n, INF);
    for(auto [p, c]: hole) {
        vector<ll> pre(n);
        for(int i = 0; i < n; i++) pre[i] = abs(mice[i] - p);
        for(int i = 1; i < n; i++) pre[i] += pre[i-1];
        deque<pair<ll,int>> dq{{0, -1}};
        for(int i = 0; i < n; i++) {
            while(dq.size() && dq.front().second < i - c) dq.pop_front();
            while(dq.size() && dq.back().first >= dp[i] - pre[i]) dq.pop_back();
            dq.emplace_back(dp[i] - pre[i], i);
            nxt[i] = dq.front().first + pre[i];
            // pre[i] = abs(m[i] - p) + abs(m[i-1] - p) + ... + abs(m[0] - p)
            // cost(i, j) = pre[i] - pre[j];
            /* nxt[i] = dp[i]; */
            /* ll cost = abs(mice[i] - p); */
            /*
            for(int j = i-1; j >= 0 && i-j <= c; j--) {
                nxt[i] = min(nxt[i], dp[j] + cost);
                // dp[j] - pre[j] + pre[i];
                cost += abs(mice[j] - p);
            }
            if(i <= c) nxt[i] = min(nxt[i], cost);
            */
        }
        for(int i = 0; i < n; i++) dp[i] = nxt[i];
    }
    cout << dp[n-1] << '\n';
}
// dp[j][i] = min(dp[j-1][i'] + cost(i', i, p[j]))
