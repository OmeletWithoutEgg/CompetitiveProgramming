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
    int n, h, m, k;
    cin >> n >> h >> m >> k;
    m /= 2;
    vector<pair<int,int>> evt;
    vector<int> pos(n);
    for(int i = 0; i < n; i++) {
        int H, M;
        cin >> H >> M;
        int l = M % m;
        int r = (M + k) % m;
        pos[i] = l;
        // (l, r)
        debug(l, r);
        if(l < r) {
            evt.pb(l+1, 1);
            evt.pb(r, -1);
        } else {
            evt.pb(0, 1);
            evt.pb(r, -1);
            evt.pb(l+1, 1);
        }
    }
    sort(all(evt));
    int t = -1, best = inf;
    for(int i = 0, j = 0, now = 0; i < int(evt.size()); i = j) {
        for(j = i; j < int(evt.size()); j++) {
            if(evt[i].first != evt[j].first) break;
            now += evt[j].second;
        }
        if(best > now) {
            best = now;
            t = evt[i].first;
        }
    }
    cout << best << ' ' << t << '\n';
    for(int i = 0; i < n; i++) {
        int l = (t - k + m) % m;
        int r = t;
        int p = pos[i];
        if(l<r ? l < p && p < r : l < p || p < r) cout << i+1 << ' ';
    }
    cout << '\n';        
}
