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
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

void solve() {
    int n, k;
    cin >> n >> k;
    int a[125] = {}, cnt[125] = {};
    for(int i = 0; i < n; i++) cin >> a[i];
    int m = 1;
    cnt[0] = 1;
    for(int i = 1; i < n; i++) {
        int d = a[i] - a[i-1];
        if(d) {
            bool ok = 0;
            for(int j = 0; j < m; j++) if(cnt[j] < k) {
                ++cnt[j];
                ok = 1;
                break;
            }
            if(!ok) {
                if(k == 1) return cout << -1 << '\n', void();
                cnt[m++] = 2;
            }
        }
        for(int j = 0; j < m; j++) cerr << cnt[j] << (j==m-1 ? '\n' : ' ');
        debug(m);
    }
    cout << max(1, m) << '\n';
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--) solve();
}