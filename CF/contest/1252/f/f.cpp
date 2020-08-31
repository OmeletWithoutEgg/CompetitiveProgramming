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
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
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

int n;
bool rmed[N];
int sz[N], mxs[N];
vector<int> vtx;
vector<int> g[N];
void getSz(int i, int p) {
    sz[i] = 1, mxs[i] = 0;
    vtx.pb(i);
    for(int j: g[i]) {
        if(j != p && !rmed[j]) {
            getSz(j, i);
            sz[i] += sz[j];
            mxs[i] = max(mxs[i], sz[j]);
        }
    }
}
vector<int> getCent(int i) {
    vtx.clear();
    getSz(i, 0);
    vector<int> res;
    for(int x: vtx) mxs[x] = max(mxs[x], sz[i] - sz[x]);
    /* for(int x: vtx) debug(x, mxs[x]); */
    for(int x: vtx) if(mxs[x] * 2 <= sz[i]) res.pb(x);
    /* debug(res.size(), vtx.size()); */
    return res;
}
int getHash(int i, int p) {
    vector<int> hs;
    for(int j: g[i]) {
        if(j != p && !rmed[j]) {
            hs.pb(getHash(j, i));
        }
    }
    int H = 7122;
    sort(hs.begin(), hs.end());
    for(int h: hs) H = (H*K+h) % MOD;
    return H;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b), g[b].pb(a);
    }
    int c = getCent(1)[0];
    rmed[c] = true;
    vector<int> ans;
    for(int j: g[c]) {
        vector<int> tmp;
        for(int x: getCent(j)) tmp.pb(getHash(x, 0));
        sort(tmp.begin(), tmp.end());
        if(ans.size() && ans != tmp) return cout << -1 << '\n', 0;
        ans = tmp;
    }
    cout << g[c].size() << '\n';
}
