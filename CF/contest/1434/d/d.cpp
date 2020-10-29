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
#define debug(args...) qqbx(#args, args)
using ost = std::ostream;
#define DESTL(STL, BEG, END, OUT) \
    template <typename ...T> ost& operator<<(ost &O, std::STL<T...> v) { int f=0; for(auto x: v) O << (f++ ? ", " : BEG) << OUT; return O << END; }
DESTL(deque, "[", "]", x); DESTL(vector, "[", "]", x);
DESTL(set, "{", "}", x); DESTL(multiset, "{", "}", x); DESTL(unordered_set, "{", "}", x);
DESTL(map , "{", "}", x.first << ":" << x.second); DESTL(unordered_map , "{", "}", x.first << ":" << x.second);
template <typename U, typename V> ost& operator<<(ost &O, std::pair<U,V> p) { return O << '(' << p.first << ',' << p.second << ')'; }
template <typename T, size_t N> ost& operator<<(ost &O, std::array<T,N> a) { int f=0; for(T x: a) O << (f++ ? ", " : "[") << x; return O << "]"; }
template <typename T, size_t ...I> ost& prtuple(ost &O, T t, std::index_sequence<I...>) { return (..., (O << (I ? ", " : "(") << std::get<I>(t))), O << ")"; }
template <typename ...T> ost& operator<<(ost &O, std::tuple<T...> t) { return prtuple(O, t, std::make_index_sequence<sizeof...(T)>()); }
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
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
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e8;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct Segtree {
    struct node {
        int mx[2], mn;
        int ij[2], jk[2];
        int best;
        friend node operator+(const node &a, const node &b) {
            node res;
            for(int c: {0, 1}) res.mx[c] = max(a.mx[c], b.mx[c]);
            res.mn = min(a.mn, b.mn);
            for(int c: {0, 1}) res.ij[c] = max({ a.ij[c], b.ij[c], a.mx[c] - b.mn * 2 });
            for(int c: {0, 1}) res.jk[c] = max({ a.jk[c], b.jk[c], - a.mn * 2 + b.mx[c] });
            res.best = max({ a.best, b.best, a.ij[0] + b.mx[0], a.mx[0] + b.jk[0], a.ij[1] + b.mx[1], a.mx[1] + b.jk[1] });
            return res;
        }
        void rev() {
            swap(mx[0], mx[1]);
            swap(ij[0], ij[1]);
            swap(jk[0], jk[1]);
        }
        node() : mx{-inf, -inf}, mn(inf), ij{-inf, -inf}, jk{-inf, -inf}, best(0) {}
        node(int p, int d) {
            mx[p] = d, mx[!p] = -inf;
            mn = d;
            ij[p] = jk[p] = -d, ij[!p] = jk[!p] = -inf;
            best = 0;
        }
    } st[N<<1];
    int n;
    int lz[N];
    void init(int p[], int d[], int _n) {
        n = _n;
        for(int i = 0; i < n; i++) st[i+n] = node(p[i], d[i]);
        for(int i = n-1; i > 0; i--) st[i] = st[i<<1] + st[i<<1|1];
        for(int i = n-1; i > 0; i--) lz[i] = false;
    }
    void upd(int p) {
        st[p].rev();
        if(p < n) lz[p] ^= 1;
    }
    void pull(int p) {
        for(p>>=1; p; p>>=1) {
            st[p] = st[p<<1] + st[p<<1|1];
            if(lz[p]) st[p].rev();
        }
    }
    void push(int p) {
        for(int h = __lg(n); h >= 0; h--) {
            int i = p >> h;
            if(!lz[i>>1]) continue;
            upd(i);
            upd(i^1);
            lz[i>>1] = false;
        }
    }
    void toggle(int l, int r) {
        int L = l, R = r;
        push(l+n), push(r-1+n);
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) upd(l++);
            if(r&1) upd(--r);
        }
        pull(L+n), pull(R-1+n);
    }
    int query(int l, int r) {
        node resl, resr;
        push(l+n), push(r-1+n);
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) resl = resl + st[l++];
            if(r&1) resr = st[--r] + resr;
        }
        return (resl + resr).best;
    }
} sgt;
vector<tuple<int,int,int>> g[N];
int parity[N], dep[N];
int eid[N];
int in[N], ou[N], tot;
void dfs(int i, int p, int PR, int DE) {
    parity[tot] = PR, dep[tot] = DE;
    in[i] = ou[i] = tot++;
    for(auto [j, t, id]: g[i]) {
        if(j == p) continue;
        eid[id] = j;
        dfs(j, i, PR ^ t, DE + 1);
        parity[tot] = PR, dep[tot] = DE;
        ou[i] = tot++;
    }
}
int getMax() {
    int ans = 0;
    for(int i = 0; i < tot; i++) for(int j = i; j < tot; j++) for(int k = j; k < tot; k++) {
        if(parity[i] == parity[k]) {
            ans = max(ans, dep[i] + dep[k] - dep[j] * 2);
        }
    }
    return ans;
}
void toggle(int x) {
    for(int i = in[x]; i <= ou[x]; i++) parity[i] ^= 1;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i < n; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        g[a].pb(b, t, i);
        g[b].pb(a, t, i);
    }
    dfs(1, 0, 0, 0);
    sgt.init(parity, dep, tot);
    int q;
    cin >> q;
    while(q--) {
        int x;
        cin >> x;
        /* toggle(eid[x]); */
        /* cout << getMax() << '\n'; */
        /* debug(vector<int>(parity, parity+tot)); */
        x = eid[x];
        sgt.toggle(in[x], ou[x]+1);
        cout << sgt.query(0, tot) << '\n';
    }
}
