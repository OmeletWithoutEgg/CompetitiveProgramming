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

pll extgcd(ll a, ll b) {
    if(!b) return {1, 0};
    auto [x, y] = extgcd(b, a%b);
    return {y, x - (a/b) * y};
}
ll lowbit(ll x) { return x & -x; }
vector<tuple<ll,char,ll>> ans;
bool solve(ll x) {
    if(x == 1) return true;
    if(lowbit(x+1) == x+1) {
        ll y = x ^ (x*2);
        ll z = x+y;
        ll w = z ^ (y*2);
        ans.pb(x, '+', x);
        ans.pb(x, '^', x*2);
        ans.pb(x, '+', y);
        ans.pb(y, '+', y);
        ans.pb(z, '^', y*2);
        while(!(w & y)) {
            ans.pb(w, '+', w);
            w <<= 1;
        }
        ans.pb(w, '^', y);
        return true;
    }
    ll L = __lg(x);
    ll y = x ^ (x << L);
    ans.pb(x, '^', x);
    for(int i = 0; i < L; i++) {
        ll t = x << i;
        ans.pb(t, '+', t);
    }
    ans.pb(x, '^', x<<L);
    auto [a, b] = extgcd(x, y);
    // ax + by = 1;
    auto calc = [](ll p, ll e) {
        ll r = 0;
        for(; p; p>>=1) {
            if(p & 1) {
                ans.pb(r, '+', e);
                r += e;
            }
            ans.pb(e, '+', e);
            e <<= 1;
        }
    };
    calc(abs(a), x);
    calc(abs(b), y);
    ll X = abs(a*x), Y = abs(b*y);
    ans.pb(X, '^', Y);
    return solve(X^Y);
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    /* for(int i = 3; i < N; i+=2) { */
    /*     ans.clear(); */
    /*     assert(solve(i)); */
    /* } */
    /* debug(0); */
    /* return 0; */
    solve(n);
    cout << ans.size() << '\n';
    for(auto [a, b, c]: ans) cout << a << ' ' << b << ' ' << c << '\n';
}
