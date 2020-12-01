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

#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
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
constexpr ll N = 100025, INF = 1e18, MOD = 20191126, K = 15, inf = 1e9;
constexpr ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}
constexpr inline ll cdiv(ll x, ll m) { return (x+m-1)/m; } // ceiling divide, x/m for flooring divide
template <typename T> void M(T &x, ll m=MOD){x%=m; if(x<0) x+=m;}
inline int readchar() {
    const int B = 1048576;
    static char buf[B];
    static char *p = buf, *tail = buf;
    if(p == tail) {
        if((tail = buf + fread(buf, 1, B, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline ll next_ll() {
    //bool neg = false;
    ll x = 0, c = readchar();
    while('0'>c || c>'9') c=readchar();
    //if(c=='-') neg=1, c=readchar();
    while('0'<=c && c<='9') x=x*10+c-'0', c=readchar();
    //if(neg) x=-x;
    return x;
}
inline uint64_t bgcd(int64_t a,int64_t b) {
    a=abs(a), b=abs(b);
    if(!a) return b;
    if(!b) return a;
    int s=__builtin_ctzll(a|b);
    a>>=s, b>>=s;
    a>>=__builtin_ctzll(a);
    do {
        b >>= __builtin_ctzll(b);
        if(a>b) swap(a,b);
        b-=a;
    }while(b);
    return a << s;
}

int n,q;
ll v[N],d[N<<1],sum[N];
void inc(int l, int r, ll k) {
    for(int i=l+1; i<=n; i+=i&-i) sum[i] += k;
    for(int i=r+1; i<=n; i+=i&-i) sum[i] -= k;
    for(d[l+=n]+=k; l>1; l>>=1) d[l>>1] = bgcd(d[l],d[l^1]);
    for(d[r+=n]-=k; r>1; r>>=1) d[r>>1] = bgcd(d[r],d[r^1]);
}
ll qry(int l,int r) {
    ll res = 0;
    for(int i=r; i; i-=i&-i) res += sum[i];
    //debug(res);
    //return res;
    for(++l, l+=n, r+=n; l<r; l>>=1, r>>=1) {
        if(l&1) res=bgcd(res,d[l++]);
        if(r&1) res=bgcd(res,d[--r]);
    }
    return res;
}
/*ll getVal(int p) {
    ll res = 0;
    for(int i=p+1; i; i-=i&-i) res += sum[i];
    return res;
}*/
signed main() {
    //ios_base::sync_with_stdio(0), cin.tie(0);
    //cin >> n >> q;
    n = next_ll(), q = next_ll();
    for(int i = 1; i <= n; i++) v[i] = next_ll();
    for(int i = 0; i < n; i++) d[i+n] = v[i+1]-v[i];
    for(int i = n-1; i > 0; i--) d[i] = bgcd(d[i<<1], d[i<<1|1]);
    for(int i = 1; i <= n; i++) sum[i] = v[i] - v[i-(i&-i)];
    //return 0;
    while(q--) {
        ll t,l,r,k;
        //cin >> t;
        t = next_ll();
        if(t == 1) {
            l = next_ll(), r = next_ll(), k = next_ll(), --l;
            //cin >> l >> r >> k, --l;
            inc(l,r,k);
        }else if(t == 2) {
            l = next_ll(), r = next_ll(), --l;
            //cin >> l >> r, --l;
            //cout << qry(l,r) << '\n';
            printf("%lld\n", qry(l,r));
        }
        //for(int i = 0; i < n; i++) cout << getVal(i) << ' '; cout << '\n';
    }
}

/*
5 7
1 2 3 4 5
2 1 5
1 1 2 1
1 4 5 2
1 5 5 2
2 4 5
2 3 4
2 1 5
*/

