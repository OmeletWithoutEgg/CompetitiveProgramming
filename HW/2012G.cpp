#include <bits/stdc++.h>

using namespace std;
typedef double ld;
const int N = 425;
const int64_t INF = 1e18;

vector<int> g[N];
struct node {
    int x, y, z, h;
} junc[N];
ld dist(node a, node b) { return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z)); }
int n, m;
struct DisjoinSets {
    int cost[N], pa[N], rk[N];
    int anc(int x) { return x==pa[x] ? x : pa[x] = anc(pa[x]); }
    void join(int x, int y) {
        if((x=anc(x)) == (y=anc(y))) return;
        if(rk[x] < rk[y]) swap(x, y);
        pa[y] = x, rk[x]!=rk[y] || ++rk[x], cost[x] += cost[y];
    }
    bool same(int a, int b) { return anc(a) == anc(b); }
    void init(int n) {
        for(int i = 0; i < n; i++) pa[i] = i, rk[i] = 0;
    }
} dsu;
vector<pair<ld,int> > adj[N];
ld dis[N];
int fr[N];
void dijkstra(int s, int t) {
    for(int i = 0; i < n; i++) fr[i] = -1, dis[i] = INF;
    priority_queue<pair<ld,int>, vector<pair<ld,int> >, greater<pair<ld,int> > > pq;
    pq.push({ dis[s] = dsu.cost[s] * 0.5, s });
    if(dsu.cost[s] == 0) return;
    while(!pq.empty()) {
        auto p = pq.top(); pq.pop();
        ld d = p.first;
        int i = p.second;
        if(dis[i] != d || (i!=t && i!=s && dsu.cost[i] < 2)) continue;
        for(auto q: adj[i]) {
            ld c = q.first;
            int j = q.second;
            ld cost = dis[i] + c + dsu.cost[j] * 0.5 - 1;
            if(dis[j] > cost)
                pq.push({ dis[j] = cost, j }), fr[j] = i;
        }
    }
}
void solve() {
    for(int i = 0; i < n; i++) g[i].clear();
    for(int i = 0; i < n; i++) {
        auto &J = junc[i];
        cin >> J.x >> J.y >> J.z >> J.h;
    }
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b, --a, --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    map<int, vector<int> > mp;
    for(int i = 0; i < n; i++) mp[junc[i].z].emplace_back(i);
    vector<int> lower;
    vector<tuple<ld,int,int> > treeEdges;
    dsu.init(n);
    for(int i = 0; i < n; i++) dsu.cost[i] = junc[i].h;
    ld ans = INF;
    bool ok = false;
    for(auto &p: mp) {
        auto &juncs = p.second;
        for(int i: juncs) for(int j: g[i]) if(junc[j].z <= junc[i].z) dsu.join(i, j);
        for(int i: juncs) lower.emplace_back(i);
        for(int i = 0; i < n; i++) adj[i].clear();
        for(int i: lower) for(int j: lower) if(i != j && junc[i].h && junc[j].h) {
            if(dsu.same(i, j)) continue;
            ld dis = dist(junc[i], junc[j]);
            /* cerr << fixed << setprecision(10); */
            /* cerr << dis << ' ' << i << ' ' << j << '\n'; */
            adj[dsu.anc(i)].emplace_back(dis, dsu.anc(j));
        }
        dijkstra(dsu.anc(0), dsu.anc(n-1));
        if(dsu.anc(n-1) == dsu.anc(0) || fr[dsu.anc(n-1)] != -1) ans = min(ans, dis[dsu.anc(n-1)]), ok = true;
    }
    if(!ok) {
        cout << "impossible\n";
    } else {
        cout << fixed << setprecision(4) << ans << '\n';
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int tot = 0;
    while(cin >> n >> m) {
        cout << "Case " << ++tot << ": ";
        solve();
    }
}
