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
constexpr ld PI = acos(-1), eps = 1e-9;
constexpr ll N = 100025, INF = 1e18, MOD = 1000000007, K = 146, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}

int n, q, t[N];
ll v[N], res[N];
vector<tuple<int,int,int>> Q[N];
struct segtree {
    ll mn[N<<1],n;
    void init(int _n) {
        n = _n;
        for(int i = 1; i < n*2; i++) mn[i] = INF;
    }
    void edit(int p, ll d) {
        for(p += n, mn[p] = min(mn[p], d); p > 1; p >>= 1)
            mn[p>>1] = min(mn[p], mn[p^1]);
    }
    ll qry(int l, int r) {
        ll res = INF;
        // debug(l), debug(r);
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) res = min(res, mn[l++]);
            if(r&1) res = min(res, mn[--r]);
        }
        // debug(res);
        return res;
    }
} ans, idx;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> v[i];
    cin >> q;
    for(int i = 0, l, r; i < q; i++) {
        cin >> l >> r;
        Q[l].pb(l, r, i);
    }
    vector<ll> u;
    for(int i = 1; i <= n; i++) u.pb(v[i]);
    sort_uni(u);
    for(int i = 1; i <= n; i++) t[i] = get_pos(u, v[i]) + 1;
    ans.init(n+1);
    idx.init(N);
    // cout << "OK\n";
    for(int i = n; i >= 1; i--) {
        // debug(i);
        for(ll j = idx.qry(0, t[i]), m; j <= n; j = idx.qry(m, t[i])) {
            ans.edit(j, v[i] - v[j]);
            // v[i]-m < m-v[j], m > (v[i]+v[j])/2.0, m >= (v[i]+v[j])/2 + 1
            m = get_pos(u, (v[i]+v[j])/2+1) + 1;
        }
        for(ll j = idx.qry(t[i], N), m; j <= n; j = idx.qry(t[i], m)) {
            ans.edit(j, v[j] - v[i]);
            // v[j]-m > m-v[i], m < (v[i]+v[j])/2.0, m < (v[i]+v[j]+1)/2
            m = get_pos(u, (v[i]+v[j]+1)/2) + 1;
        }
        idx.edit(t[i], i);
        for(auto [l, r, id]: Q[i])
            res[id] = ans.qry(0, r+1);
    }
    for(int i = 0; i < q; i++) cout << res[i] << '\n';
}

