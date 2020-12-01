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
typedef double ld;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;
template <typename T> using max_heap = __gnu_pbds::priority_queue<T,less<T> >;
template <typename T> using min_heap = __gnu_pbds::priority_queue<T,greater<T> >;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr ld PI = acos(-1), eps = 1e-5;
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 11, inf = 1e9;
constexpr ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}
constexpr inline ll cdiv(ll x, ll m) { return (x+m-1)/m; } // ceiling divide, x/m for flooring divide
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p = buf, *tail = buf;
    if(p == tail) {
        tail = buf + fread(buf, 1, B, stdin);
        if(tail == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int next_int() {
    int x = 0, c = readchar();
    while('0'>c || c>'9') c=readchar();
    while('0'<=c&&c<='9') x=x*10+c-'0', c=readchar();
    return x;
}

int n,v[N],b[N],c[N],deg[N];
struct ordered_set {
    int b[N],sz;
    int size() {return sz;}
    void init() {
        sz = 0;
        for(int i = 1; i <= n; i++) b[i] = 0;
    }
    int order(int x) {
        int r = 0;
        for(++x; x; x-=x&-x) r += b[x];
        return r;
    }
    int kth(int k) {
        if(k >= sz) return inf;
        int x = 0, s = 1<<__lg(n)+1;
        while(s) {
            if(x+s <= n && k >= b[x+s]) k -= b[x+=s];
            s>>=1;
        }
        return x;
    }
    void insert(int x) {
        for(++sz, ++x; x<=n; x+=x&-x) b[x]++;
    }
} fwt;
signed main() {
    n = next_int();
    for(int i = 0; i < n; i++) v[i] = next_int();
    for(int i = 0; i < n; i++) {
        int rk = fwt.order(v[i]);
        b[v[i]] = fwt.kth(rk+(fwt.size()-rk-1)/2);
        fwt.insert(v[i]);
    }
    fwt.init();
    for(int i = n-1; i >= 0; i--) {
        int rk = fwt.order(v[i]);
        c[v[i]] = fwt.kth(rk+(fwt.size()-rk-1)/2);
        fwt.insert(v[i]);
    }
    for(int i = 0; i < n-1; i++) ++deg[i], ++deg[min(b[i],c[i])];
    printf("%d\n", *max_element(deg,deg+n));
}

