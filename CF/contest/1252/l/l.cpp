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
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct Dinic {
    struct Edge {
        int rest, to;
        Edge(int rest, int to) : rest(rest), to(to) {}
    };
    vector<Edge> E;
    vector<vector<int>> g;
    vector<int> dis, cur;
    Dinic(int n) : g(n), dis(n), cur(n) {}
    void addEdge(int a, int b, int c) {
        g[a].pb(E.size()), E.pb(c, b);
        g[b].pb(E.size()), E.pb(0, a);
    }
    bool BFS(int s, int t) {
        fill(dis.begin(), dis.end(), -1);
        queue<int> q;
        dis[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int i = q.front(); q.pop();
            for(int id: g[i]) if(E[id].rest > 0 && dis[E[id].to] == -1) {
                dis[E[id].to] = dis[i] + 1;
                q.push(E[id].to);
            }
        }
        return dis[t] != -1;
    }
    int DFS(int i, int t, int lim) {
        if(i == t) return lim;
        int ans = 0;
        while(cur[i] < g[i].size() && lim) {
            int id = g[i][cur[i]++];
            if(dis[E[id].to] != dis[i] + 1) continue;
            int f = DFS(E[id].to, t, min(lim, E[id].rest));
            ans += f;
            lim -= f;
            E[id].rest -= f;
            E[id^1].rest += f;
        }
        return ans;
    }
    int maxFlow(int s, int t) {
        int ans = 0;
        while(BFS(s, t)) {
            fill(cur.begin(), cur.end(), 0);
            while(int f = DFS(s, t, inf)) ans += f;
        }
        return ans;
    }
    vector<pair<int,int>> full() {
        vector<pair<int,int>> res;
        for(int i = 0; i < E.size(); i += 2) if(E[i].rest == 0) res.pb(E[i^1].to, E[i].to);
        return res;
    }
};
vector<int> like[N];
int a[N], deg[N];
int C[N];
int cid[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        int t;
        cin >> a[i] >> t, --a[i];
        like[i].resize(t);
        for(int &x: like[i]) cin >> x;
    }
    for(int i = 0; i < k; i++) cin >> C[i];
    vector<vector<int>> g(n);
    for(int i = 0; i < n; i++) g[i].pb(a[i]), g[a[i]].pb(i);
    for(int i = 0; i < n; i++) ++deg[a[i]], ++deg[i];
    queue<int> q;
    for(int i = 0; i < n; i++) if(deg[i] == 1) q.push(i);
    while(!q.empty()) {
        int i = q.front(); q.pop();
        for(int j: g[i]) if(--deg[j] == 1) q.push(j);
    }
    vector<bool> cyc(n);
    int cycCnt = 0;
    for(int i = 0; i < n; i++) if(deg[i] == 2) cyc[i] = true, ++cycCnt;

    Dinic flow(n+k+25);
    int s = n+1, t = n+2, c = n;
    for(int i = 0; i < n; i++) {
        if(cyc[i] && cyc[a[i]]) {
            flow.addEdge(i, c, 1);
        } else {
            flow.addEdge(i, t, 1);
        }
    }
    flow.addEdge(c, t, cycCnt - 1);
    int tot = n+3;
    vector<int> u(C,C+k);
    sort_uni(u);
    for(int i = 0; i < u.size(); i++) cid[i] = tot++;
    for(int i = 0; i < k; i++) {
        int id = cid[get_pos(u, C[i])];
        flow.addEdge(s, id, 1);
    }
    for(int i = 0; i < n; i++) {
        for(int j: like[i]) {
            if(!binary_search(all(u), j)) continue;
            int id = cid[get_pos(u, j)];
            flow.addEdge(id, i, 1);
        }
    }
    int f = flow.maxFlow(s, t);
    debug(f);
    if(f != n-1) return cout << -1 << '\n', 0;

    vector<vector<int>> worker(u.size());
    vector<pair<int,int>> ans(k, pair<int,int>(-1,-1));
    for(int i = 0; i < k; i++) worker[get_pos(u, C[i])].pb(i);
    for(auto [i, j]: flow.full()) {
        if(j < n) {
            debug(j);
            i -= n+3;
            ans[worker[i].back()] = {j, a[j]};
            worker[i].pop_back();
        }
    }
    for(auto [a, b]: ans)
        cout << a+1 << ' ' << b+1 << '\n';
}
