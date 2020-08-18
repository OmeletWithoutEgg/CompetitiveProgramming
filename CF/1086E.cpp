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
#define debug(...) qqbx(#__VA_ARGS__,  __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...); // C++ 17!
}
#else
#include <bits/stdc++.h>
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define get_pos(v,x) (lower_bound(begin(v),end(v),x)-begin(v))
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
constexpr ll N = 2025, INF = 1e18, MOD = 998244353, K = 26, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

ll D[N] = {1}, fr[N] = {1}, n;
ll dp[N][N];
int v[N][N];
int sum[2][N], app[N];
void add(int v[], int p, int d) {
    for(; p < N; p+=p&-p) v[p] += d;
}
int qry(int v[], int p) {
    int r = 0;
    for(; p > 0; p-=p&-p) r += v[p];
    return r;
}
ll calc(const int a[], const int b[]) {
    for(int i = 1; i <= n; i++) sum[0][i] = sum[1][i] = app[i] = 0;
    for(int i = 1; i <= n; i++) add(sum[0], i, 1);
    ll res = 0, same = n, diff = 0;
    auto del = [&](int i, int s){
        if(app[i] < 2) add(sum[app[i]], i, -1);
        if(!app[i])
            app[i] = s, --same, ++diff;
        else
            assert(app[i] != s), app[i] |= s, --diff;
        if(app[i] < 2) add(sum[app[i]], i, 1);
    };
    for(int i = 1; i <= n; i++) {
        del(a[i], 1);
        /*for(int c = 1; c < b[i]; c++) if(c != a[i]) {
            if(!app[c]) { // not appeared in a,b
                debug(diff+1, same-1);
                if(same) res = (res + dp[(diff+1)/2][same-1]) % MOD;
            } else if(app[c] == 1) { // appeared in a, not appeared in b
                debug(diff-1, same);
                if(diff) res = (res + dp[(diff-1)/2][same]) % MOD;
            }
            debug(c, res);
        }*/
        if(same) {
            int cnt = qry(sum[0], b[i]-1);
            debug(cnt);
            res = (res + dp[(diff+1)/2][same-1] * cnt) % MOD;
        }
        if(diff) {
            int cnt = qry(sum[1], b[i]-1) - (a[i]<b[i] && app[a[i]] == 1);
            debug(cnt);
            res = (res + dp[(diff-1)/2][same] * cnt) % MOD;
        }
        del(b[i], 2);
    }
    debug(res);
    return res;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    for(int i = 2; i < N; i++) D[i] = (i-1) * (D[i-1]+D[i-2]) % MOD;
    for(int i = 1; i < N; i++) fr[i] = fr[i-1] * i % MOD;
    for(int i = 0; i < N; i++) dp[i][0] = fr[i];
    for(int j = 0; j < N; j++) dp[0][j] = D[j];
    for(int j = 1; j < N; j++) {
        for(int i = 1; i+1 < N; i++) {
            dp[i][j] = (i * dp[i][j-1] + (j>=2 ? (j-1) * dp[i+1][j-2] : 0)) % MOD;
            dp[i][j] %= MOD;
        }
    }
    cin >> n;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin >> v[i][j];
    ll ans = 0, s = 0;
    for(int i = 1; i <= n; i++) {
        int cnt = 0;
        for(int j = i+1; j <= n; j++) if(v[1][j] < v[1][i]) ++cnt;
        s = (s + cnt * fr[n-i]) % MOD;
    }
    ans = (ans + s * modpow(D[n], n-1)) % MOD;
    for(int i = 2; i <= n; i++)
        ans = (ans + calc(v[i-1], v[i]) * modpow(D[n], n-i)) % MOD;
    cout << ans << '\n';
}
