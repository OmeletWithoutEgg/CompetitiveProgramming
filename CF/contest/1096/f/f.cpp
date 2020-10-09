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
constexpr ll N = 1000025, INF = 1e18, MOD = 998244353, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

int p[N];
bool app[N];
int suf[N];
int b[N];
void add(int x) {
    for(; x<N; x+=x&-x) b[x] += 1;
}
int qry(int x) {
    int res = 0;
    for(; x>0; x-=x&-x) res += b[x];
    return res;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> p[i];
    for(int i = 1; i <= n; i++) if(p[i] != -1) app[p[i]] = true;
    for(int i = 1; i <= n; i++) if(!app[i]) ++suf[i];
    for(int i = n; i >= 1; i--) suf[i] += suf[i+1];
    int no = 0, cnt = 0, sum = 0;
    for(int i = 1; i <= n; i++) if(p[i] == -1) ++no;
    ll ans = 1LL * no * (no-1) % MOD * modpow(4, MOD-2) % MOD;
    debug(ans);
    for(int i = n; i >= 1; i--) if(p[i] != -1) ans = (ans + qry(p[i])) % MOD, add(p[i]);
    for(int i = 1; i <= n; i++) {
        if(p[i] == -1) {
            // ans += E(p[j] = -1, p[i] = -1, p[i] < p[j]) = #(-1 before) / 2;
            // ans += E(p[j] = x, p[i] = -1, p[i] < p[j]) = sum over j (#not appeared, >p[j])
            ans = (ans + 1LL * sum * modpow(no, MOD-2)) % MOD;
            ++cnt;
        } else {
            // ans += E(p[j] = x, p[i] = y);
            // ans += E(p[j] = -1, p[i] = x) = (#-1 before) * (#not appeared, >p[i]) / (#not appeared)
            int bigger = suf[p[i]];
            sum = (sum + no - bigger) % MOD;
            ans = (ans + 1LL * cnt * bigger % MOD * modpow(no, MOD-2)) % MOD;
        }
    }
    cout << ans << '\n';
}
