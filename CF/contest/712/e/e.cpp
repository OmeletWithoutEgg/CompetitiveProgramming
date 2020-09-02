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
constexpr ll N = 100025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct SegmentTree {
    int n;
    struct node {
        ld a, b;
        friend node operator+(const node &s, const node &t) {
            return {s.a*t.a, s.a*t.b + s.b};
        }
    } st[N<<1];
    void init(ld v[], int _n) {
        n = _n;
        for(int i = 0; i < n; i++) st[i+n] = {v[i], 1};
        for(int i = n-1; i > 0; i--) st[i] = st[i<<1] + st[i<<1|1];
    }
    void edit(int p, ld v) {
        for(st[p+=n] = {v, 1}, p>>=1; p>0; p>>=1)
            st[p] = st[p<<1] + st[p<<1|1];
    }
    ld query(int l, int r) {
        node resl = {1, 0}, resr = {1, 0};
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) resl = resl + st[l++];
            if(r&1) resr = st[--r] + resr;
        }
        node res = resl + resr;
        return res.a + res.b;
    }
} sgt;
int n, q;
ld f[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    // ans[x] = p[x] * ans[x+1] + (1-p[x]) * ans[x-1]
    // p[x] * (ans[x+1]-ans[x]) + (1-p[x]) * (ans[x-1]-ans[x]) = 0
    // (ans[x+1] - ans[x]) * p[x] = (1-p[x]) * (ans[x] - ans[x-1]);
    // ans[i] - ans[i-1] = k
    // f := (1-p[x]) / p[x]
    // k + f[i]*k + f[i]*f[i+1]*k + f[i]*f[i+1]*f[i+2]*k + ... = 1
    // F[x] = 1+f[x]*F[x+1]
    // ans = 1 / F[i]
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        f[i] = (b-a) / ld(a);
    }
    sgt.init(f, n);
    while(q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int x, a, b;
            cin >> x >> a >> b, --x;
            sgt.edit(x, (b-a) / ld(a));
        } else if(t == 2) {
            int l, r;
            cin >> l >> r, --l;
            cout << fixed << setprecision(10);
            ld F = sgt.query(l, r);
            if(abs(F) > 1e-6)
                cout << 1 / F << '\n';
            else
                cout << 0 << '\n';
        }
    }
}
