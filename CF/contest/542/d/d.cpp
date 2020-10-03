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

ll J(ll n) {
    ll ans = 1;
    for(ll i = 2; i*i <= n; i++) if(n % i == 0) {
        ll x = 1;
        while(n % i == 0) n /= i, x *= i;
        ans *= x+1;
    }
    if(n > 1) ans *= n+1;
    return ans;
}
ll solve(ll A, vector<vector<ll>> &v, int ind) {
    if(ind == v.size()) return A == 1;
    static map<pair<ll,int>, ll> mp;
    if(mp.count({A, ind})) return mp[{A, ind}];
    ll &ans = mp[{A, ind}];
    ans += solve(A, v, ind+1);
    auto &T = v[ind];
    for(ll x: T) if(A % x == 0) ans += solve(A / x, v, ind+1);
    return ans;
}
bool sv[N];
vector<int> prs;

bool isprs(ll x) {
    if(x < N) return !sv[x];
    for(int p: prs) {
        if(1LL*p*p > x) return true;
        if(x % p == 0) return false;
    }
    return true;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    debug(J(2LL*2*3*5*7*11*13*17*19));
    sv[0] = sv[1] = true;
    for(int i = 2; i < N; i++) {
        if(!sv[i]) prs.pb(i);
        for(int p: prs) {
            if(i*p >= N) break;
            sv[i*p] = true;
            if(i%p == 0) break;
        }
    }
    ll A;
    cin >> A;
    if(A == 1) return cout << 1 << '\n', 0;
    if(A == 2) return cout << 0 << '\n', 0;
    vector<ll> divisors;
    map<ll,vector<ll>> mp;
    for(ll i = 1; i*i <= A; i++) if(A % i == 0) {
        if(isprs(i-1)) mp[i-1].push_back(i);
        if(isprs(A/i - 1)) mp[A/i-1].push_back(A / i);
        divisors.push_back(i);
        if(i*i != A) divisors.push_back(A / i);
    }
    cout<<'\n';
    for(int p: prs) {
        for(ll x = p; x <= A; x *= p)
            if(A % (x+1) == 0)
                mp[p].push_back(x+1);
    }
    ll sum = 0;
    for(auto [_, v]: mp) sum+=v.size();
    sort(all(divisors));
    vector<ll> dp(divisors.size());
    dp[0] = 1;
    for(auto [_, v]: mp) {
        sort_uni(v);
        for(int i = int(divisors.size())-1; i >= 0; i--) {
            ll x = divisors[i];
            for(ll p: v) if(x % p == 0) {
                int j = get_pos(divisors, x / p);
                dp[i] += dp[j];
            }
        }
    }
    cout << dp.back() << '\n';
    /* for(int i = 1; i <= 10000; i++) debug(i, J(i)); */
    // A = (p_0^{a_0} + 1) (p_1^{a_1} + 1) (p_2^{a_2} + 1) ...
    // count different p^a;
}
