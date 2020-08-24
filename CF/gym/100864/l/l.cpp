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
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}
#else
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
#ifndef local
    freopen("laboratory.in", "r", stdin);
    freopen("laboratory.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    map<string, int> mp;
    vector<tuple<int,int,int>> v;
    auto id = [&mp](const string &s) -> int { return mp.count(s) ? mp[s] : mp[s]=mp.size(); };
    cin >> n;
    for(int i = 0; i < n; i++) {
        string A, B, C;
        cin >> A >> B >> C;
        int a = id(A), b = id(B), c = id(C);
        debug(a, b, c);
        v.pb(a, b, c);
        v.pb(b, c, a);
        v.pb(c, a, b);
    }
    sort(v.begin(), v.end());
    auto has = [&v](tuple<int,int,int> T) -> bool { return binary_search(all(v), T); };
    for(int i = 0; i < v.size(); i++) for(int j = 0; j < i; j++) {
        auto [a, b, c] = v[i];
        auto [d, e, f] = v[j];
        if(a==d || a==e || a==f) continue;
        if(b==d || b==e || b==f) continue;
        if(c==d || c==e || c==f) continue;
        if(has({d, b, e}) && has({e, b, a}) && has({e, a, f}) && has({a, c, f}) && has({c, d, f}) && has({c, b, d}))
            return cout << "YES\n", debug(a, b, c, d, e, f), 0;
    }
    cout << "NO\n";
}
