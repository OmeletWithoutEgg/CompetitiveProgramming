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
constexpr ll N = 100025, INF = 1e18, MOD = 1000000007, K = 10, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct Dsu {
    int k;
    mutable vector<int> pa;
    vector<int> mn, mx, col;
    int CC;
    Dsu(int v[], int k) : k(k), pa(k*2), mn(k*2), mx(k*2), col(k*2), CC(k*2) {
        iota(all(pa), 0), iota(all(mn), 0), iota(all(mx), 0);
        for(int i = 0; i < k; i++) col[i] = col[i+k] = v[i];
        for(int i = 0; i < k; i++) join(i, i+k);
        for(int i = 1; i < k; i++) if(v[i] == v[i-1]) join(i, i-1), join(i+k, i+k-1);
    }
    Dsu(int k = 0) : k(k), pa(k*2), mn(k*2), mx(k*2), col(k*2), CC(0) {}
    int anc(int x) const { return x==pa[x] ? x : pa[x]=anc(pa[x]); }
    void join(int x, int y) {
        if((x=anc(x)) == (y=anc(y))) return;
        pa[y] = x;
        mn[x] = min(mn[x], mn[y]), mx[x] = max(mx[x], mx[y]);
        --CC;
    }
    int getmn(int x) const { return mn[anc(x)]; }
    int getmx(int x) const { return mx[anc(x)]; }
    friend ostream& operator<<(ostream &O, const Dsu &d) {
        O << '\n';
        const int k = d.k;
        O << "----------\n";
        for(int i = 0; i < k; i++)
            O << '(' << d.getmn(i) << ',' << d.getmx(i) << ')' << ':' << d.col[i] << ' '
              << '(' << d.getmn(i+k) << ',' << d.getmx(i+k) << ')' << ':' << d.col[i+k] << '\n';
        O << "CC = " << d.CC << '\n';
        O << "----------\n";
        return O;
    }
    friend Dsu operator+(const Dsu &a, const Dsu &b) {
        if(a.k == 0) return b;
        if(b.k == 0) return a;
        /* debug(a, b); */
        assert(a.k == b.k);
        const int k = a.k;
        Dsu tmp(k*2);
        safe;
        debug(a, b);
        for(int i = 0; i < k*2; i++) {
            tmp.pa[i] = a.anc(i);
            tmp.mn[i] = a.getmn(i);
            tmp.mx[i] = a.getmx(i);
        }
        for(int i = 0; i < k*2; i++) {
            tmp.pa[i+k*2] = b.anc(i) + k*2;
            tmp.mn[i+k*2] = b.getmn(i) + k*2;
            tmp.mx[i+k*2] = b.getmx(i) + k*2;
        }
        tmp.CC = a.CC + b.CC;
        for(int i = 0; i < k; i++) if(a.col[i+k] == b.col[i]) tmp.join(i+k, i+k*2);
        Dsu res(k);
        res.CC = tmp.CC;
        for(int i = 0; i < k; i++) {
            res.pa[i] = tmp.getmn(i);
            res.pa[i+k] = tmp.getmn(i+k*3) < k ? tmp.getmn(i+k*3) : tmp.getmx(i+k*3) - k*2;
            res.mn[i] = tmp.getmn(i);
            res.mx[i+k] = tmp.getmx(i+k*3) - k*2;
        }
        for(int i = 0; i < k; i++) {
            res.mx[i] = tmp.getmx(i) >= k*3 ? tmp.getmx(i) - k*2 : i;
            res.mn[i+k] = tmp.getmn(i+k*3) < k ? tmp.getmn(i+k*3) : i+k;
        }
        for(int i = 0; i < k; i++) res.col[i] = a.col[i];
        for(int i = 0; i < k; i++) res.col[i+k] = b.col[i+k];
        /* debug(res); */
        return res;
    }
    /* Dsu(int n) : pa(n), rk(n), col(n) { iota(all(pa), 0); } */
};
struct Segtree {
    Dsu st[N << 1];
    int n;
    void build(int v[][K], int k, int _n) {
        n = _n;
        for(int i = 0; i < n; i++) st[i+n] = Dsu(v[i], k);
        for(int i = n-1; i > 0; i--) st[i] = st[i<<1] + st[i<<1|1];
    }
    int query(int l, int r) {
        Dsu resl, resr;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) resl = resl + st[l++];
            if(r&1) resr = st[--r] + resr;
        }
        Dsu res = resl + resr;
        return res.CC;
    }
} sgt;
int n, m, q;
int v[N][K];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m >> q;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> v[j][i];
    sgt.build(v, n, m);
    /* cout << sgt.query(0, m) << '\n'; */
    /* return 0; */
    while(q--) {
        int l, r;
        cin >> l >> r, --l;
        cout << sgt.query(l, r) << '\n';
    }
}
