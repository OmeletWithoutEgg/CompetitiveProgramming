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
#include <bits/stdc++.h>
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
template <typename T> using max_heap = std::priority_queue<T,vector<T>,less<T> >;
template <typename T> using min_heap = std::priority_queue<T,vector<T>,greater<T> >;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr ld PI = acos(-1), eps = 1e-5;
constexpr ll N = 1<<18, INF = 1e18, MOD = 1000000007, K = 22, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}

int n;
int v[22][22];
int dp[50000], DP[50000],val[50000],best,cnt;
vector<int> valid, g[50000];
uint16_t mp[1<<22];
void dfs(int fr, int s, int j, vector<int> &adj) {
    ++cnt;
    if(j == n) {
        //assert(mp.count(s));
        adj.pb(mp[s]);
        return;
    }
    bool valid = j ? !(s & (1<<j-1)) && !(fr & (7<<j-1)) : !(fr & 3);
    if(valid)
        dfs(fr, s | (1<<j), j+1, adj);
    dfs(fr, s, j+1, adj);
}
void prepare() {
    for(int s = 0; s < (1<<n); s++) {
        bool ok = true;
        for(int i = 1; i < n; i++) {
            if((s >> i & 1) && (s >> i-1 & 1))
                ok = false;
        }
        if(ok)
            valid.push_back(s);
    }
    for(int i = 0; i < valid.size(); i++)
        mp[valid[i]] = i;
    for(int i = 0; i < valid.size(); i++)
        dfs(valid[i], 0, 0, g[i]);
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> v[i][j];
    prepare();
    //debug(valid.size());
    //cout << mp[valid.back()] << '\n';
    for(int i = 0; i < n; i++) {
        for(int t = 0; t < valid.size(); t++) {
            int s = valid[t];
            val[t] = 0;
            for(int j = 0; j < n; j++) if(s>>j & 1) val[t] += v[i][j];
        }
        for(int i = 0; i < valid.size(); i++) for(int j: g[i])
            DP[j] = max(DP[j], dp[i]);
        for(int i = 0; i < valid.size(); i++)
            dp[i] = DP[i]+val[i], DP[i] = 0, best = max(best, dp[i]);
    }
    cout << best << '\n';
}

/*
4
1 1 1 0
1 1 1 0
1 1 1 1
0 0 1 1
*/

