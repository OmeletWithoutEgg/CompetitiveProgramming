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

vector<pair<int,int>> solve(int n) {
    vector<pair<int,int>> res;
    auto pw = [&](int n, int offset) {
        for(int s = 1; s < n; s <<= 1) for(int i = 0; i < n; i++) if(i & s) res.pb(i-s+offset, i+offset);
    };
    int h = 1;
    while(h*2 <= n) h *= 2;
    pw(h, 0);
    int rest = n - h;
    while(rest != (rest & -rest)) {
        pw((rest & -rest) << 1, h - (rest & -rest));
        h -= rest & -rest;
        rest += (rest & -rest);
    }
    pw(rest, n - rest);
    return res;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    /* map<pair<int,int>,int> mp; */
    /* int tot=-1; */
    /* auto f = [&mp,&tot](int a, int b) { return mp.count({a,b}) ? mp[{a,b}] : mp[{a,b}]=tot--; }; */
    int n;
    cin >> n;
    vector<pair<int,int>> v = solve(n);
    /* vector<int> t(n); */
    /* iota(all(t),0); */
    /* for(auto [a,b]:v) t[a]=t[b]=f(t[a],t[b]); */
    /* sort(all(t)); */
    cout << v.size() << '\n';
    for(auto [a, b]: v) ++a, ++b, cout << a << ' ' << b << '\n';
}
/*
 * 1 2 3 4 5 6 7 8 9 10 11 12 13
 * a a b b c c d d e  e  f  f 13
 * g g g g h h h h i  i  i  i 13
 * j j j j j j j j i  i  i  i 13
 * j j j j j j j k i  i  i  i k
 * j j j j j l l l i  i  i  i l
 */
