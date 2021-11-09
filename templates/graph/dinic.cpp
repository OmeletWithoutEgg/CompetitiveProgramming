template <typename flow_t>
struct Dinic {
    struct Edge {
        int to;
        flow_t rest;
        Edge(int t, flow_t r) : to(t), rest(r) {}
    };
    vector<Edge> E;
    vector<vector<int>> g;
    vector<int> dis, cur;
    Dinic(int n) : g(n), dis(n), cur(n) {}
    void addEdge(int a, int b, flow_t cap) {
        g[a].emplace_back(E.size()), E.emplace_back(b, cap);
        g[b].emplace_back(E.size()), E.emplace_back(a, 0);
    }
    bool bfs(int s, int t) {
        fill(dis.begin(), dis.end(), -1);
        queue<int> q;
        dis[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int i = q.front();
            q.pop();
            for (int id : g[i])
                if (E[id].rest > 0 && dis[E[id].to] == -1) {
                    dis[E[id].to] = dis[i] + 1;
                    q.push(E[id].to);
                }
        }
        return dis[t] != -1;
    }
    flow_t dfs(int i, int t, flow_t lim) {
        if (i == t) return lim;
        flow_t ans = 0;
        while (lim > 0 && cur[i] < int(g[i].size())) {
            int id = g[i][cur[i]++];
            if (dis[E[id].to] != dis[i] + 1) continue;
            flow_t f = dfs(E[id].to, t, min(lim, E[id].rest));
            lim -= f;
            ans += f;
            E[id].rest -= f;
            E[id ^ 1].rest += f;
        }
        return ans;
    }
    static constexpr flow_t inf = numeric_limits<flow_t>::max();
    flow_t maxFlow(int s, int t) {
        flow_t ans = 0, f;
        while (bfs(s, t)) {
            fill(cur.begin(), cur.end(), 0);
            while ((f = dfs(s, t, inf)) > 0) ans += f;
        }
        return ans;
    }
};
