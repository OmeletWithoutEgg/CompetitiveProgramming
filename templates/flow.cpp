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
            while(int64_t f = dfs(s, t, 1e18)) ans += f;
        }
        return ans;
    }
};
