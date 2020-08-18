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
constexpr ll N = 100025, INF = 1e18, MOD = 1000000007, K = 256, inf = 1e9;
constexpr ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}
constexpr inline ll cdiv(ll x, ll m) { return (x+m-1)/m; } // ceiling divide, x/m for flooring divide

struct SuffixArray {
    int sa[N],rk[N],tmp[N],lcp[N];
    void init(int v[],int n) {
        for(int i = 0; i < n; i++) rk[i] = v[i];
        iota(sa,sa+n,0);
        for(int L = 1; L < n; L*=2) {
            auto cmp = [&](int a,int b) {
                if(rk[a]!=rk[b]) return rk[a]<rk[b];
                int ra = (a+L<n ? rk[a+L] : -1);
                int rb = (b+L<n ? rk[b+L] : -1);
                return ra<rb;
            };
            sort(sa,sa+n,cmp);
            tmp[sa[0]] = 0;
            for(int i = 1; i < n; i++) tmp[sa[i]] = tmp[sa[i-1]] + cmp(sa[i-1],sa[i]);
            for(int i = 0; i < n; i++) rk[i] = tmp[i];
        }
        /*
        for(int i = 0; i < n; i++) {
            for(int j = sa[i]; j < n; j++) cout << v[j] << ' ';
            cout << '\n';
        }
        */
        lcp[0] = inf;
        for(int i = 0, h = 0; i < n; i++) {
            if(!rk[i]) continue;
            if(h > 0) --h;
            int j = sa[rk[i]-1];
            while(i+h<n && j+h<n && v[i+h]==v[j+h]) ++h;
            lcp[rk[i]] = h;
        }
        //for(int i = 0; i < n; i++) cout << lcp[i] << ' ';
    }
} SA;

struct RangeMinimumQuery {
    int mn[20][N],n;
    void init(int v[],int _n) {
        n = _n;
        for(int i = 0; i < n; i++) mn[0][i] = v[i];
        for(int L = 1; L < 20; L++) {
            for(int i = 0; i+(1<<L-1) < n; i++) {
                mn[L][i] = min(mn[L-1][i], mn[L-1][i+(1<<L-1)]);
            }
        }
    }
    int query(int l,int r) {
        //cout << "qry: "; for(int i = l; i < r; i++) cout << mn[i+n] << ' '; cout << '\n';
        /*int res = inf;
        for(l+=n,r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) res = min(res, mn[l++]);
            if(r&1) res = min(res, mn[--r]);
        }
        return res;*/
        int L = __lg(r-l);
        return min(mn[L][l], mn[L][r-(1<<L)]);
    }
} RMQ;
int n,q,v[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> q;
    for(int i = 0; i < n; i++) cin >> v[i];
    for(int i = 0; i < n; i++) v[i] = modpow(v[i], (MOD-1)/2);
    SA.init(v,n);
    RMQ.init(SA.lcp, n);
    for(int i = 0,a,b; i < q; i++) {
        cin >> a >> b;
        if(a == b) cout << n-a << '\n';
        else {
            int l = SA.rk[a], r = SA.rk[b];
            if(l > r) swap(l,r);
            cout << RMQ.query(l+1,r+1) << '\n';
        }
    }
}
