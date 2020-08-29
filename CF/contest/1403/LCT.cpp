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
constexpr ll N = 200025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct LinkCutTree {
    struct node {
        int pa, ch[2];
        int sum, sz, val;
        int rev;
        node() : pa(0), ch{0,0}, sum(0), sz(0), val(0), rev(0) {}
        node(int pa, int val) : pa(pa), ch{0,0}, sum(val), sz(1), val(val), rev(0) {}
    } T[N];
    int dir(int x) { return T[T[x].pa].ch[1] == x; }
    int isroot(int x) { return !x || T[T[x].pa].ch[dir(x)] != x; }
    void pull(int x) {
        T[x].sum = T[x].val, T[x].sz = 1;
        for(int c: {0,1}) if(T[x].ch[c]) T[x].sum += T[T[x].ch[c]].sum, T[x].sz += T[T[x].ch[c]].sz;
    }
    void push(int x) {
        if(!T[x].rev) return;
        T[x].sum = T[x].sz * 3 - T[x].sum;
        T[x].val = 3 - T[x].val;
        for(int c: {0,1}) if(T[x].ch[c]) T[T[x].ch[c]].rev ^= 1;
        T[x].rev = 0;
    }
    void pushAll(int x) {
        if(!isroot(x)) pushAll(T[x].pa);
        push(x);
    }
    void rot(int x) {
        int y = T[x].pa, z = T[y].pa, d = dir(x);
        T[x].pa = z;
        if(!isroot(y)) T[z].ch[dir(y)] = x;
        if(T[x].ch[!d]) T[T[x].ch[!d]].pa = y;
        T[y].ch[d] = T[x].ch[!d];
        T[y].pa = x;
        T[x].ch[!d] = y;
        pull(y), pull(x);
    }
    void splay(int x) {
        pushAll(x);
        while(!isroot(x)) {
            int y = T[x].pa;
            if(!isroot(y))
                rot(dir(x) ^ dir(y) ? x : y);
            rot(x);
        }
    }
    int access(int x) {
        int last = 0;
        while(x) {
            splay(x);
            T[x].ch[1] = last;
            pull(x);
            last = x;
            x = T[x].pa;
        }
        return last;
    }
    void rpush(int i) {
        if(!i) return;
        push(i);
        for(int c: {0,1}) rpush(T[i].ch[c]);
    }
    int toggle(int x) { // returns differ
        int id = access(x);
        int res = T[id].sz*3-T[id].sum*2;
        /* debug(T[id].sz, T[id].sum); */
        T[id].rev ^= 1;
        /* debug(T[id].sz, T[id].sum); */
        return res;
    }
} lct;
vector<int> g[N];
int leaf[N];
int deg[N];
ll ans;
int root = -1;
void dfs(int i, int p) {
    leaf[i] = deg[i] <= 1;
    for(int j: g[i]) if(j != p && j != root) {
        dfs(j, i);
        leaf[i] += leaf[j];
    }
    if(leaf[i] & 1)
        leaf[i] = 1;
    else
        leaf[i] = 2;
    ans += leaf[i];
    lct.T[i] = LinkCutTree::node(p, leaf[i]);
}
signed main() {
    /* freopen("input1.txt", "r", stdin); */
    /* freopen("pans.out", "w", stdout); */
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b), g[b].pb(a);
        ++deg[a], ++deg[b];
    }
    for(int i = 1; i <= 3; i++) if(g[i].size() > 1) root = i;
    int rv = 0;
    for(int i = 1; i <= n; i++) if(g[i].size() == 1) ++rv;
    for(int j: g[root]) dfs(j, 0);
    int ans0 = ans;
    while(q--) {
        int d;
        cin >> d;
        vector<int> a(d);
        for(int &x: a) cin >> x;
        bool bad = (rv ^ d) & 1;
        for(int x: a) {
            if(x==root) continue;
            if(deg[x] != 1) ans += lct.toggle(x);
            else bad = !bad;
            ++deg[x];
        }
        if(bad) cout << -1 << '\n';
        else cout << ans+d << '\n';
        for(int x: a) {
            if(x==root) continue;
            --deg[x];
            if(deg[x] != 1) ans += lct.toggle(x);
        }
        assert(ans == ans0);
    }
}

