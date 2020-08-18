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
#define mid (l+(r-l>>1))
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
constexpr ld PI = acos(-1), eps = 1e-9;
constexpr ll N = 200025, INF = 1e18, MOD = 1000000007, K = 400, inf = 1e6;
constexpr ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}
constexpr inline ll cdiv(ll x, ll m) { return (x+m-1)/m; } // ceiling divide, x/m for flooring divide
template <typename T> void M(T &x, ll m=MOD){x%=m; if(x<0) x+=m;}

ll n,lim,h[N],w[N],dp[N];
struct segTree {
    ll mn[N<<1],laz[N],n;
    void upd(int p,ll d) {
        mn[p] += d;
        if(p < n) laz[p] += d;
    }
    void pull(int p) {
        for(p += n; p > 1; p>>=1) mn[p>>1] = min(mn[p],mn[p^1]) + laz[p>>1];
    }
    void push(int p) {
        p += n;
        for(int h = __lg(n); ~h; h--) {
            int i = p>>h;
            if(!laz[i>>1]) continue;
            upd(i,laz[i>>1]);
            upd(i^1,laz[i>>1]);
            laz[i>>1] = 0;
        }
    }
    void edit(int l,int r,ll k) {
        ll L = l, R = r;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) upd(l++, k);
            if(r&1) upd(--r, k);
        }
        pull(L), pull(R);
    }
    ll query(int l,int r) {
        ll res = INF;
        push(l);
        push(r-1);
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) res = min(mn[l++], res);
            if(r&1) res = min(res, mn[--r]);
        }
        return res;
    }
    void pr(int l,int r) {
        for(int i = l; i < r; i++) cout << query(i,i+1) << " \n"[i==r-1];
    }
} RMQ;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> lim;
    RMQ.n = n+1;
    for(int i = 1; i <= n; i++) cin >> h[i] >> w[i];
    ll width = 0;
    deque<int> dq;
    for(int i = 1, j = 0; i <= n; i++) {
        width += w[i];
        while(width > lim) width -= w[++j];
        while(dq.size() && dq.front() <= j) {
            ll nxt = dq.size() > 1 ? h[dq[1]] : 0;
            RMQ.edit(0,dq.front(),nxt-h[dq.front()]);
            dq.pop_front();
        }
        while(dq.size() && h[dq.back()] <= h[i]) {
            int prvid = dq.size() > 1 ? dq[dq.size()-2] : 0;
            RMQ.edit(prvid, dq.back(), -h[dq.back()]);
            dq.pop_back();
        }
        int prvid = dq.size() ? dq.back() : 0;
        RMQ.edit(prvid, i, h[i]);
        dq.push_back(i);
        dp[i] = RMQ.query(j,i);
        //debug(dp[i]);
        RMQ.edit(i,i+1,dp[i]);
    }
    cout << dp[n] << '\n';
}

