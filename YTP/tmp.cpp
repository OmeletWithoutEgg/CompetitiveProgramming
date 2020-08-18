#include <bits/stdc++.h>
#define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))
#define get_pos(v,x) int(lower_bound(begin(v),end(v),x)-begin(v))
#define debug(x) cerr<<#x<<" = "<<(x)<<'\n'

#define int long long
using namespace std;
typedef int64_t ll;
typedef pair<ll,ll> pll;
const int N = 800025, inf = 1e9;
#define pb emplace_back

struct node {
    ll ans, sum;
    ll lans, rans;
    node(ll v = 0) : ans(max<ll>(0, v)), sum(v), lans(max<ll>(0, v)), rans(max<ll>(0, v)) {}
    friend node operator+(const node &lhs, const node &rhs) {
        node res(0);
        res.sum = lhs.sum + rhs.sum;
        res.lans = max(lhs.lans, lhs.sum + rhs.lans);
        res.rans = max(rhs.rans, rhs.sum + lhs.rans);
        res.ans = max({ lhs.ans, rhs.ans, lhs.rans + rhs.lans, res.lans, res.rans });
        return res;
    }
};
struct Segtree {
    node st[N<<1];
    int n;
    void init(int v[], int _n) {
        n = _n;
        for(int i = 0; i < n; i++) st[i+n] = node(v[i]);
        for(int i = n-1; i > 0; i--) st[i] = st[i<<1] + st[i<<1|1];
    }
    node query(int l, int r, bool inv) {
        /* cerr << "l = " << l << " r = " << r << endl; */
        node resl(0), resr(0);
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) resl = resl + st[l++];
            if(r&1) resr = st[--r] + resr;
        }
        resl = resl + resr;
        if(!inv) swap(resl.lans, resl.rans);
        return resl;
    }
} sgt;
int sz[N], mxs[N], pad[N];
vector<pll> g[N];
void dfs(int i, int p) {
    sz[i] = 1;
    for(auto [c, j]: g[i]) {
        if(j == p) continue;
        pad[j] = c;
        dfs(j, i);
        sz[i] += sz[j];
        if(!mxs[i] || sz[mxs[i]] < sz[j]) mxs[i] = j;
    }
}
int vis[N], tot, val[N], top[N], pa[N];
int dep[N];
void DFS(int i, int p, int t) {
    vis[i] = tot++;
    pa[i] = p;
    dep[i] = dep[p] + 1;
    top[i] = t;
    val[vis[i]] = pad[i];
    if(mxs[i]) DFS(mxs[i], i, t);
    for(auto [c, j]: g[i]) {
        if(j == p || j == mxs[i]) continue;
        DFS(j, i, j);
    }
}
ll query(int a, int b) {
    node resa(0), resb(0);
    while(top[a] != top[b]) {
        int pta = pa[top[a]];
        int ptb = pa[top[b]];
        if(dep[pta] > dep[ptb])
            resa = resa + sgt.query(vis[top[a]], vis[a]+1, 0), a = pta;
        else
            resb = sgt.query(vis[top[b]], vis[b]+1, 1) + resb, b = ptb;
    }
    if(dep[a] > dep[b])
        resa = resa + sgt.query(vis[b]+1, vis[a]+1, 0);
    else
        resb = sgt.query(vis[a]+1, vis[b]+1, 1) + resb;
    resa = resa + resb;
    return resa.ans;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb(c, b);
        g[b].pb(c, a);
    }
    dfs(1, 0);
    DFS(1, 0, 1);
    /* for(int i = 0; i < n; i++) cout << val[i] << ' '; */
    /* cout << '\n'; */
    /* for(int i = 1; i <= n; i++) cout <<vis[i] << ' '; */
    /* cout << '\n'; */
    sgt.init(val, n);
    for(int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        cout << query(a,b) << '\n';
    }
}
