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
#define get_pos(v,x) (lower_bound(all(v),x)-begin(v))
#define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))
#define pb emplace_back
#define mem(v,x) memset(v,x,sizeof v)

using namespace std;
typedef int64_t ll;
typedef pair<ll,ll> pll;
constexpr ll N = 200025, inf = 1e9;

int n,m,q;
multiset<int> ms[N];
int val[N];
struct BidirectionalConnectedComponents {
    int low[N],vis[N],fa[N];
    int cnt,ap[N],bcc[N];
    stack<int> stk;
    vector<int> g[N],vertices[N];
    void add_edge(int a,int b) {
        g[a].pb(b), g[b].pb(a);
    }
    void dfs(int i) { // root is 1
        static int tot = 0;
        low[i] = vis[i] = ++tot;
        stk.push(i);
        bool isAp = false;
        int child = 0;
        for(int j:g[i]) {
            if(!vis[j]) {
                fa[j] = i;
                dfs(j);
                ++child;
                if(low[j] < vis[i]) low[i] = min(low[i], low[j]); // the child can climb up
                else {
                    isAp = true;
                    ++cnt;
                    int x;
                    do {
                        x = stk.top(), stk.pop();
                        if(!bcc[x]) bcc[x] = cnt;
                        vertices[cnt].pb(x);
                    }while(x != j);
                    bcc[i] = cnt;
                    vertices[cnt].pb(i);
                }
            }else if(j!=fa[i] && vis[j]<vis[i]) low[i] = min(low[i], vis[j]); // back edge, avoid multiple edges
        }
        if(!fa[i] && child == 1) isAp = false;
        if(isAp) bcc[i] = ++cnt, ap[cnt] = true;
    }
    void shrink(vector<int> adj[]) {
        dfs(1);
        //for(int i = 1; i <= cnt; i++) cout << ap[i] << ' '; cout << '\n';
        //for(int i = 1; i <= n; i++) cout << bcc[i] << ' '; cout << '\n';
        for(int i = 1; i <= cnt; i++) {
            for(int j:vertices[i]) if(ap[bcc[j]]) {
                adj[i].pb(bcc[j]);
                adj[bcc[j]].pb(i);
            }
            vertices[i].clear();
        }
        //for(int i = 1; i <= n; i++) for(int j:g[i]) if(ap[i] ^ ap[j]) adj[bcc[i]].pb(bcc[j]);
        for(int i = 1; i <= cnt; i++) sort_uni(adj[i]);
    }
} BCC;

struct RangeMinimumQueries {
    int mn[N<<1],n;
    void init(int _n, int v[]) {
        n = _n;
        for(int i = 0; i < n; i++) mn[i+n] = v[i];
        for(int i = n-1; i > 0; i--) mn[i] = min(mn[i<<1], mn[i<<1|1]);
    }
    void edit(int p, int k) {
        for(mn[p+=n]=k; p>1; p>>=1) mn[p>>1] = min(mn[p], mn[p^1]);
    }
    int get_mn(int l,int r) {
        int res = inf;
        for(l+=n,r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) res = min(mn[l++], res);
            if(r&1) res = min(res, mn[--r]);
        }
        return res;
    }
} RMQ;

struct HeavyLightDecomposition {
    vector<int> adj[N];
    int sz[N],mxs[N],dep[N],fa[N],link_top[N],id[N],W[N];
    void get_sz(int i) {
        mxs[i] = 0, sz[i] = 1;
        for(int j:adj[i]) if(j!=fa[i]) {
            fa[j] = i;
            dep[j] = dep[i]+1;
            get_sz(j);
            sz[i] += sz[j];
            if(!mxs[i] || sz[mxs[i]] < sz[j]) mxs[i] = j;
        }
    }
    void deco(int i,int top) {
        static int tot = 0;
        link_top[i] = top;
        id[i]=tot++;
        if(mxs[i]) deco(mxs[i],top);
        for(int j:adj[i]) if(j!=fa[i] && j!=mxs[i]) deco(j,j);
    }
    void init(int cnt) {
        get_sz(1);
        deco(1,1);
        /*cout<<"===\n";
        for(int i = 1; i <= n; i++) for(int j:adj[i]) if(i < j) cout << i << ' ' << j << '\n';
        debug(cnt);
        debug(n);
        cout << "id: "; for(int i = 1; i <= n; i++) cout << id[i] << ' '; cout << '\n';
        exit(0);*/
        for(int i = 1; i <= n; i++) {
            int x = BCC.bcc[i];
            ms[x].insert(val[i]);
            if(BCC.ap[x] && fa[x]) ms[fa[x]].insert(val[i]); // maintain articulation points value with its parent BCC
        }
        for(int i = 1; i <= cnt; i++) W[id[i]] = *ms[i].begin();
        RMQ.init(cnt,W);
    }
    void update(int i,int k) {
        W[id[i]] = k;
        RMQ.edit(id[i], k);
    }
    int query(int a,int b) {
        int res = inf;
        while(link_top[a] != link_top[b]) {
            if(dep[link_top[a]] < dep[link_top[b]]) swap(a,b);
            int ta = link_top[a]; // top of link of a
            res = min(res, RMQ.get_mn(id[ta],id[a]+1));
            a = fa[ta];
        }
        if(id[a] < id[b]) swap(a,b);
        res = min(res, RMQ.get_mn(id[b],id[a]+1)); // LCA == b
        if(!BCC.ap[b] && fa[b]) res = min(res, W[id[fa[b]]]); // if LCA is BCC, needs to consider its father articulation point
        return res;
    }
    void DFS(int i,int d) {
        for(int k = 0; k < d; k++) cout << '\t';
        cout << i << ' ' << W[i] << '\n';
        for(int j:adj[i]) if(j!=fa[i]) DFS(j,d+1);
    }
} HLD;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++) cin >> val[i];
    for(int i = 0, a,b; i < m; i++) {
        cin >> a >> b;
        BCC.add_edge(a,b);
    }
    BCC.shrink(HLD.adj);
    //for(int i = 1; i <= n; i++) cout << BCC.bcc[i] << " \n"[i==n];
    HLD.init(BCC.cnt);
    while(q--) {
        char c;
        int a,b;
        cin >> c >> a >> b;
        if(c == 'C') {
            int x = BCC.bcc[a];
            if(BCC.ap[x] && HLD.fa[x]) { // maintain articulation points value with its parent BCC
                auto &MS = ms[HLD.fa[x]];
                MS.erase(MS.find(val[a]));
                MS.insert(b);
                HLD.update(HLD.fa[x],*MS.begin());
            }
            auto &MS = ms[x];
            MS.erase(MS.find(val[a]));
            MS.insert(b);
            HLD.update(x, *MS.begin());
            val[a] = b;
        }else if(c == 'A') {
            if(a == b) cout << val[a] << '\n'; // can't even move when a==b
            else cout << HLD.query(BCC.bcc[a],BCC.bcc[b]) << '\n';
        }
        //HLD.DFS(1,0);
    }
}
