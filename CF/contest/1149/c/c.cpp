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
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}
#else
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
constexpr ll N = 300025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e8;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct SegmentTree {
    int n;
    struct node {
        int ans; // max(d[i] - 2d[j] + d[k])
        int mx, mn; // max(d[i]); min(d[j])
        int fr, bk; // max(d[i] - 2d[j]); max(-2d[j] + d[k])
        node() : ans(-inf), mx(-inf), mn(inf), fr(-inf), bk(-inf) {}
        node(int d) : ans(-inf), mx(d), mn(d), fr(-inf), bk(-inf) {}
        friend node operator+(const node &a, const node &b) {
            node res;
            res.ans = max({ a.ans, b.ans, a.fr + b.mx, a.mx + b.bk });
            res.mx = max(a.mx, b.mx), res.mn = min(a.mn, b.mn);
            res.fr = max({ a.fr, b.fr, a.mx - 2*b.mn });
            res.bk = max({ a.bk, b.bk, -2*a.mn + b.mx });
            return res;
        }
    } st[N<<1];
    int lz[N];
    void init(int _n, int v[]) {
        n = 1;
        while(n < _n) n *= 2;
        for(int i = 0; i < _n; i++) st[i+n] = node(v[i]);
        for(int i = n-1; i > 0; i--) st[i] = st[i<<1] + st[i<<1|1];
        for(int i = 0; i < n; i++) lz[i] = 0;
    }
    void upd(int p, int d) {
        st[p].mx += d, st[p].mn += d;
        st[p].fr -= d, st[p].bk -= d;
        if(p < n) lz[p] += d;
    }
    void pull(int p) {
        for(p>>=1; p>0; p>>=1) {
            st[p] = st[p<<1] + st[p<<1|1];
            int d = lz[p];
            st[p].mx += d, st[p].mn += d;
            st[p].fr -= d, st[p].bk -= d;
        }
    }
    void push(int p) {
        for(int h = __lg(n)-1; h >= 0; h--) {
            int i = p>>h;
            if(!lz[i>>1]) continue;
            upd(i, lz[i>>1]);
            upd(i^1, lz[i>>1]);
            lz[i>>1] = 0;
        }
    }
    void add(int l, int r, int d) {
        push(l+n), push(r-1+n);
        for(int L = l+n, R = r+n; L<R; L>>=1, R>>=1) {
            if(L&1) upd(L++, d);
            if(R&1) upd(--R, d);
        }
        pull(l+n), pull(r-1+n);
    }
    int query(int l, int r) {
        node resl, resr;
        push(l+n), push(r-1+n);
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) resl = resl + st[l++];
            if(r&1) resr = st[--r] + resr;
        }
        node res = resl + resr;
        return max(res.ans, res.mx);
    }
} sgt;
int v[N], dep[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    n = n*2-1;
    for(int i = 0; i < n-1; i++) v[i+1] = (s[i] == '(' ? 1 : -1);
    for(int i = 1; i < n; i++) dep[i] = dep[i-1] + v[i];
    /* for(int i = 0; i < n; i++) cout << dep[i] << ' '; cout << '\n'; */
    sgt.init(n, dep);
    cout << sgt.query(0, n) << '\n';
    while(q--) {
        int a, b;
        cin >> a >> b;
        sgt.add(a, n, -2*v[a]);
        sgt.add(b, n, -2*v[b]);
        /* for(int i = a; i < n; i++) dep[i] -= 2*v[a]; */
        /* for(int i = b; i < n; i++) dep[i] -= 2*v[b]; */
        /* for(int i = 0; i < n; i++) cout << dep[i] << ' '; cout << '\n'; */
        v[a] = -v[a];
        v[b] = -v[b];
        cout << sgt.query(0, n) << '\n';
    }
}
