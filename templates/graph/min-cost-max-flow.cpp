struct MCMF {
    struct Edge {
        int to;
        int64_t rest, cost;
        Edge(int a, int64_t b, int64_t c) : to(a), rest(b), cost(c) {}
    };
    vector<Edge> E;
    vector<int> g[maxn];
    int n;
    int prv[maxn];
    int64_t dis[maxn], P[maxn];
    void init(int sz) {
        n = sz;
        E.clear();
        for (int i = 0; i < n; i++) g[i].clear();
    }
    void addEdge(int x, int y, int64_t cap, int64_t cost) {
        g[x].emplace_back(E.size());
        E.emplace_back(y, cap, cost);
        g[y].emplace_back(E.size());
        E.emplace_back(x, 0, -cost);
    }
    void dagdp(int s) {
        fill(dis, dis + n, INF);
        dis[s] = 0;
        vector<int> indeg(n);
        for (int i = 0; i < n; i++)
            for (int id : g[i])
                if (E[id].rest != 0) indeg[E[id].to] += 1;
        queue<int> que;
        que.push(s);
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            for (int id : g[i]) {
                if (E[id].rest == 0) continue;
                int j = E[id].to;
                int64_t d = E[id].cost;
                dis[j] = min(dis[j], dis[i] + d);
                if (--indeg[j] == 0) que.push(j);
            }
        }
        orange(all(indeg));
        for (int i = 0; i < n; i++) P[i] = dis[i];
    }
    bool dijkstra(int s, int t) {
        fill(dis, dis + n, INF);
        min_heap<pair<int64_t, int>> pq;
        pq.emplace(dis[s] = 0, s);
        while (!pq.empty()) {
            auto [d, i] = pq.top();
            pq.pop();
            for (int id : g[i]) {
                if (E[id].rest == 0) continue;
                int j = E[id].to;
                int64_t d = E[id].cost;
                if (dis[j] > dis[i] + d + P[i] - P[j]) {
                    dis[j] = dis[i] + d + P[i] - P[j];
                    prv[j] = id;
                    pq.emplace(dis[j], j);
                }
            }
        }
        return dis[t] != INF;
    }
    pair<int64_t, int64_t> flow(int s, int t) {
        int64_t ans = 0, cost = 0;
        // dagdp(s);
        while (dijkstra(s, t)) {
            int64_t mn = INF;
            for (int v = t; v != s; v = E[prv[v] ^ 1].to)
                mn = min(mn, E[prv[v]].rest);
            for (int v = t; v != s; v = E[prv[v] ^ 1].to) {
                // debug(v);
                E[prv[v]].rest -= mn;
                E[prv[v] ^ 1].rest += mn;
            }
            ans += mn;
            cost += mn * (dis[t] - P[s] + P[t]);
            for (int i = 0; i < n; i++) P[i] += dis[i];
        }
        debug(ans);
        // debug(ans), debug(cost);
        return {ans, cost};
    }
} mcmf;
