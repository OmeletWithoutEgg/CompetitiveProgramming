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
constexpr ll N = 200025, INF = 1e18, MOD = 1000000007, K = 1000, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

bool sv[N];
int np[N];
vector<int> prs;
vector<int> pw[N];
int pid[N];
vector<pair<int,int>> fac(int n) {
    vector<pair<int,int>> res;
    while(n > 1) {
        int p = np[n], c = 0;
        while(np[n] == p) n /= p, ++c;
        res.pb(p, c);
    }
    return res;
}
int n;
int a[N];
vector<vector<pair<int,int>>> TA[N / K];
vector<int> PR[N / K];
ll query(int l, int r) {
    if(l / K == r / K) {
        map<int,int> mp;
        for(int i = l; i <= r; i++) for(auto [p, cnt]: fac(a[i])) mp[p] = max(mp[p], cnt);
        ll prod = 1;
        for(auto [p, cnt]: mp) prod = prod * pw[p][cnt] % MOD;
        return prod;
    }
    map<int,int> mp;
    while(l%K != 0) {
        int x = a[l++];
        for(auto [p, cnt]: fac(x)) mp[p] = max(mp[p], cnt);
    }
    ll prod = PR[l / K][r];
    pair<int,int> R(r, inf);
    for(auto [p, cnt]: mp) {
        int c = prev(upper_bound(all(TA[l/K][pid[p]]), R)) -> second;
        if(c < cnt) prod = prod * pw[p][cnt-c] % MOD;
    }
    return prod;
}
signed main() {
    for(int i = 2; i < N; i++) {
        if(!sv[i]) pid[i] = prs.size(), prs.pb(i), np[i] = i;
        for(int p: prs) {
            if(i*p >= N) break;
            sv[i*p] = true;
            np[i*p] = p;
            if(i % p == 0) break;
        }
    }
    for(int i = 2; i < N; i++) if(!sv[i]) {
        auto &p = pw[i];
        p.pb(1);
        while(1LL * p.back() * i < N) p.pb(p.back() * i);
    }
    ios_base::sync_with_stdio(0), cin.tie(0);
#ifdef local
    mt19937 rng(7122);
    n = 100000;
    for(int i = 0; i < n; i++) a[i] = uniform_int_distribution<int>(1, 200000)(rng);
#else
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
#endif // local
    for(int l = 0; l < n; l += K) {
        map<int,int> mp;
        ll prod = 1;
        auto &T = TA[l/K];
        T.resize(prs.size());
        PR[l/K].resize(n);
        for(int i = l; i < n; i++) {
            for(auto [p, cnt]: fac(a[i])) {
                if(!mp.count(p) || mp[p] < cnt) {
                    prod = prod * pw[p][ mp.count(p) ? cnt - mp[p] : cnt ] % MOD;
                    mp[p] = cnt;
                    T[pid[p]].pb(i, cnt);
                }
            }
            PR[l/K][i] = prod;
        }
    }
    int q;
#ifdef local
    q = 100000;
#else
    cin >> q;
#endif // local
    int ans = 0;
    while(q--) {
        int l, r;
#ifdef local
        l = uniform_int_distribution<int>(0, n-1)(rng);
        r = uniform_int_distribution<int>(0, n-1)(rng);
#else
        cin >> l >> r;
#endif // local
        l = (l + ans) % n;
        r = (r + ans) % n;
        if(l > r) swap(l, r);
        ans = query(l, r);
        cout << ans << '\n';
    }
}
