#pragma GCC optimize("Ofast")
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#define pb emplace_back
#define int64_t int
using namespace std;

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

int p, q, m;
const int N = 200025;
vector<int> g[N];
int dp[N][2];
struct Dinic {
    struct Edge {
        int to;
        int64_t rest;
        Edge(int t, int64_t r) : to(t), rest(r) {}
    };
    vector<Edge> E;
    vector<vector<int>> g;
    vector<int> dis, cur;
    Dinic(int n) : g(n), dis(n), cur(n) {}
    void addEdge(int a, int b, int64_t cap) {
        g[a].pb(E.size()), E.pb(b, cap);
        g[b].pb(E.size()), E.pb(a, 0);
    }
    bool bfs(int s, int t) {
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
    int64_t dfs(int i, int t, int64_t lim) {
        if(i == t) return lim;
        int64_t ans = 0;
        while(lim && cur[i] < int(g[i].size())) {
            int id = g[i][cur[i]++];
            if(dis[E[id].to] != dis[i] + 1) continue;
            int f = dfs(E[id].to, t, min(lim, E[id].rest));
            lim -= f;
            ans += f;
            E[id].rest -= f;
            E[id^1].rest += f;
        }
        return ans;
    }
    int64_t maxFlow(int s, int t) {
        int64_t ans = 0;
        while(bfs(s, t)) {
            fill(cur.begin(), cur.end(), 0);
            while(int64_t f = dfs(s, t, 1e9)) ans += f;
        }
        return ans;
    }
};
void solve() {
    int s = p+q, t = s+1;
    Dinic flow(t+1);
    for(int i = 0; i < m; i++) {
        int a = nextint() - 1;
        int b = nextint() - 1;
        flow.addEdge(a, b+p, 1);
    }
    for(int i = 0; i < p; i++) flow.addEdge(s, i, 1);
    for(int i = 0; i < q; i++) flow.addEdge(i+p, t, 1);
    printf("%d\n", flow.maxFlow(s, t));
}
struct TreeMatching {
    int head[200000],nxt[400000],to[400000],tot;
    int dp[200000][2];
    void init(int n) {
        tot = 0;
        for(int i = 0; i < n; i++) head[i] = -1;
    }
    void addEdge(int a,int b) {
        nxt[tot] = head[a];
        to[tot] = b;
        head[a] = tot;
        ++tot;
    }
    void DFS(int i, int p) {
        dp[i][0] = 0;
        dp[i][1] = 1;
        int mx = 0;
        for(int id=head[i]; ~id; id=nxt[id]) {
            int j = to[id];
            if(j == p) continue;
            DFS(j,i);
            dp[i][0]+=dp[j][0];
            dp[i][1]+=dp[j][0];
            mx = max(mx, dp[j][1]-dp[j][0]);
        }
        dp[i][0] += mx;
    }
    int solve() {return DFS(0,-1), dp[0][0];}
} tr;
signed main() {
    // ios_base::sync_with_stdio(0), cin.tie(0);
    int t = nextint();
    while(t--) {
        p = nextint(), q = nextint(), m = nextint();
        if(max(p, q) <= 1500) {
            solve();
        } else {
            tr.init(p+q);
            for(int i = 0; i < m; i++) {
                int a = nextint() - 1;
                int b = nextint() - 1;
                b += p;
                tr.addEdge(a, b);
                tr.addEdge(b, a);
            }
            printf("%d\n", tr.solve());
        }
    }
}
