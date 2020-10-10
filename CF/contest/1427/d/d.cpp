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
    int n;
    cin >> n;
    vector<int> p(n+1);
    for(int i = 1; i <= n; i++) cin >> p[i];
    auto perform = [&](vector<int> op) {
        debug(op.size());
        debug(accumulate(all(op), 0));
        vector<vector<int>> bb;
        int i = 1;
        for(int b: op) {
            bb.pb();
            while(b--) bb.back().pb(p[i++]);
        }
        reverse(all(bb));
        i = 1;
        for(auto v: bb) for(int x: v) p[i++] = x;
    };
    vector<vector<int>> ans;
    for(int x = 1; x < n; x++) {
        if(p[1] == 1 ? p[x] == x : p[n+1-x] == x) continue;
        vector<int> op;
        int pos = -1;
        for(int j = 1; j <= n; j++) if(p[j] == x) pos = j;
        if(p[1] == 1) {
            for(int i = 1; i < x; i++) op.pb(1);
            op.pb(pos - x + 1);
            if(pos != n) op.pb(n - pos);
        } else {
            pos = n+1-pos;
            for(int i = 1; i < x; i++) op.pb(1);
            op.pb(pos - x + 1);
            if(pos != n) op.pb(n - pos);
            reverse(all(op));
        }
        perform(op);
        ans.pb(op);
    }
    if(p[1] != 1) {
        vector<int> op(n, 1);
        perform(op);
        ans.pb(op);
    }
    /* debug(ans.size()); */
    /* for(int i = 1; i <= n; i++) cerr << p[i] << ' '; */
    /* cerr << '\n'; */
    cout << ans.size() << '\n';
    for(auto v: ans) {
        cout << v.size() << '\n';
        for(int x: v) cout << x << ' ';
        cout << '\n';
    }
}
