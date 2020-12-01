#include <bits/stdc++.h>
#define pb emplace_back
#define debug(x) cerr<<#x<<" = "<<x<<'\n'

using namespace std;
const int N = 400, INF = 1e9;

struct MCMF {
    struct Edge {
        int to;
        int64_t rest,cost;
    };
    vector<Edge> E;
    vector<int> g[N];
    int n,dis[N],now[N],inQ[N],prv[N];
    void init(int sz) {
        n = sz;
        E.resize(0);
        for(int i = 0; i < n; i++) g[i].resize(0);
    }
    void addEdge(int x,int y,int64_t cap,int64_t cost) {
        g[x].pb(E.size()), E.push_back({y,cap,cost});
        g[y].pb(E.size()), E.push_back({x,0,-cost});
    }
    bool SPFA(int s,int t) {
        for(int i = 0; i < n; i++) dis[i] = INF;
        queue<int> q;
        q.push(s), dis[s] = 0, inQ[s] = 1;
        while(!q.empty()) {
            s = q.front(), q.pop(), inQ[s] = 0;
            for(int id:g[s]) {
                if(E[id].rest == 0) continue;
                int v = E[id].to;
                int64_t d = E[id].cost;
                if(dis[v] > dis[s]+d) {
                    dis[v] = dis[s]+d;
                    prv[v] = id;
                    if(!inQ[v]) q.push(v), inQ[v] = 1;
                }
            }
        }
        return dis[t]!=INF;
    }
    pair<int64_t,int64_t> flow(int s,int t) {
        int64_t ans = 0, cost = 0;
        while(SPFA(s,t)) {
            int64_t mn = INF;
            for(int v = t; v != s; v = E[prv[v]^1].to) mn = min(mn, E[prv[v]].rest);
            for(int v = t; v != s; v = E[prv[v]^1].to) {
                //debug(v);
                E[prv[v]].rest -= mn;
                E[prv[v]^1].rest += mn;
                cost += mn * E[prv[v]].cost;
            }
            ans += mn;
        }
        //debug(ans), debug(cost);
        return {ans, cost};
    }
} mcmf;

int w[101][101];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    while(cin >> n && n) {
        for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin >> w[i][j];
        mcmf.init(n*2+2);
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(w[i][j] > 0) mcmf.addEdge(i, j+n, 1, -w[i][j]);
            }
        }
        for(int i = 1; i <= n; i++) mcmf.addEdge(0, i, 1, 0);
        for(int i = 1; i <= n; i++) mcmf.addEdge(i+n, n*2+1, 1, 0);
        cout << -mcmf.flow(0, n*2+1).second << '\n';
    }
}
