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
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

mt19937 rng(7122);
struct node {
    node *l, *r;
    int sz, v;
    node(int x) : v(x), l(0), r(0), sz(1) {}
    void pull() {
        sz = 1;
        if(l) sz += l->sz;
        if(r) sz += r->sz;
    }
} *root;
node *join(node *a, node *b) {
    if(!a || !b) return a ? a : b;
    if(rng()%(a->sz+b->sz) < a->sz)
        return a->r = join(a->r, b), a->pull(), a;
    else
        return b->l = join(a, b->l), b->pull(), b;
}
void split(node *o, node *&a, node *&b, int k) {
    if(!o) return a = b = nullptr, void();
    int s = o->l ? o->l->sz + 1 : 1;
    if(k >= s)
        a = o, split(o->r, a->r, b, k-s), a->pull();
    else
        b = o, split(o->l, a, b->l, k), b->pull();
}
void pr(node *x) {
    string ans;
    function<void(node*)> dfs = [&](node *r) {
        if(!r) return;
        dfs(r->l), ans+=char(r->v), dfs(r->r);
    };
    dfs(x);
    cout << ans << '\n';
}
void shift(node *&r, int c) {
    node *A, *B;
    split(r, A, B, c);
    r = join(B, A);
}
signed main() {
#ifndef local
    freopen("coding.in", "r", stdin);
    freopen("coding.out", "w", stdout);
    ios_base::sync_with_stdio(0), cin.tie(0);
#endif
    int q;
    string s;
    cin >> s;
    for(char c: s) root = join(root, new node(c));
    cin >> q;
    vector<tuple<int,int,int>> v(q);
    for(auto &[a, b, c]: v) cin >> a >> b >> c;
    reverse(all(v));
    for(auto [a, b, c]: v) {
        node *A, *B, *C;
        split(root, B, C, b);
        split(B, A, B, a-1);
        shift(B, c % B->sz);
        root = join(join(A, B), C);
        /* pr(root); */
    }
    pr(root);
}
