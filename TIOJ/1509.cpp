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
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 256;
constexpr ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}
constexpr inline ll cdiv(ll x, ll m) { return (x+m-1)/m; } // ceiling divide, x/m for flooring divide
template <typename T> void M(T &x, ll m=MOD){x%=m; if(x<0) x+=m;}

struct SP{
    bitset<N> ok;
    int head[N],to[N],nxt[N],tot;
    int cost[N],dis[N];
    void addEdge(int a,int b,int c) {
        ++tot;
        nxt[tot] = head[a];
        to[tot] = b;
        cost[tot] = c;
        head[a] = tot;
    }
    void dijkstra(int s) {
        for(int i = 0; i < N; i++) dis[i] = -1;
        min_heap<pair<int,int>> pq;
        pq.push({0,s});
        dis[s] = 0;
        while(!pq.empty()) {
            pair<int,int> cur;
            do cur = pq.top(), pq.pop(); while(pq.size() && ok[cur.ss]);
            ok[cur.ss] = 1;
            int i = cur.ss;
            for(int k = head[i]; k; k=nxt[k]) {
                int j = to[k];
                ll d = cost[k];
                if(dis[j] == -1 || dis[j] > dis[i]+d)
                    pq.push({dis[j]=dis[i]+d,j});
            }
        }
    }
} s[2];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int m,n;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a,b,w;
        cin >> a >> b >> w;
        s[0].addEdge(a,b,w);
        s[1].addEdge(b,a,w);
    }
    s[0].dijkstra(1);
    s[1].dijkstra(1);
    ll ans = 0;
    for(int i = 2; i <= n; i++) {
        if(s[0].dis[i] == -1 || s[1].dis[i] == -1) return cout << 0 << '\n', 0;
        ans += s[0].dis[i]+s[1].dis[i];
    }
    cout << ans << '\n';
}

