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

#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/extc++.h>
#ifdef local
#define debug(x) (cerr<<#x<<" = "<<(x)<<'\n')
#else
#define debug(x) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define siz(v) (ll(v.size()))
#define get_pos(v,x) (lower_bound(all(v),x)-begin(v))
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
template <typename T> using max_heap = __gnu_pbds::priority_queue<T,less<T> >;
template <typename T> using min_heap = __gnu_pbds::priority_queue<T,greater<T> >;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr ld PI = acos(-1), eps = 1e-5;
constexpr ll N = 200005, INF = 1e18, MOD = 1000000007, K = 512, inf = 1e9;
constexpr ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}
constexpr inline ll cdiv(ll x, ll m) { return (x+m-1)/m; } // ceiling divide, x/m for flooring divide

int mu[N], np[N], n, m;
vector<int> prs;
unordered_map<int,int> smus, cmus;
void getmus(int n) {
    if(n < N || smus.count(n)) return;
    ll smu = 0, cmu = 0; // g_s(n) = n^2, g_c(n) = 1 (g(1)==1)
    for(ll i = 2,j; i <= n; i = j) { // S(n) = 1 - g(2)S(2) - g(3)S(3) - ...
        getmus(n/i);
        j = (n/(n/i))+1;
        ll sdif = (j*(j-1)%MOD*(j*2-1)%MOD - i*(i-1)%MOD*(i*2-1)%MOD + MOD) % MOD * modpow(6,MOD-2) % MOD;
        ll cdif = j-i;
        smu = (smu + sdif*smus[n/i]) % MOD;
        cmu = (cmu + cdif*cmus[n/i]) % MOD;
    }
    smus[n] = (1 - smu + MOD) % MOD;
    cmus[n] = (1 - cmu + MOD) % MOD;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    mu[1] = 1;
    for(int i = 2; i < N; i++) {
        if(!np[i]) prs.pb(i), mu[i] = -1;
        for(ll p:prs) {
            if(i*p >= N) break;
            np[i*p] = 1;
            if(i%p == 0) break;
            else mu[i*p] = -mu[i];
        }
    }
    for(int i = 1; i < N; i++) cmus[i] = (mu[i]+cmus[i-1]+MOD)%MOD;
    for(int i = 1; i < N; i++) smus[i] = (1LL*mu[i]*i*i%MOD+smus[i-1]+MOD)%MOD;
    cin >> n >> m;
    if(n > m) swap(n,m);
    ll sum = 0;
    ll cnt = 0;
    for(ll i = 1,j; i <= n; i = j) {
        ll tn = n/i, sn = tn*(tn+1)/2%MOD;
        ll tm = m/i, sm = tm*(tm+1)/2%MOD;
        j = min(n/tn, m/tm)+1;
        getmus(j-1), getmus(i-1);
        ll sdif = (smus[j-1] - smus[i-1] + MOD) % MOD;
        ll cdif = (cmus[j-1] - cmus[i-1] + MOD) % MOD;
        sum = (sum+sn*sm%MOD*sdif%MOD)%MOD;
        cnt = (cnt+tn*tm%MOD*cdif%MOD)%MOD;
    }
    //debug(sum), debug(cnt);
    cout << sum * modpow(cnt, MOD-2) % MOD << '\n';
}

