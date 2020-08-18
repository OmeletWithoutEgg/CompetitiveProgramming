struct Dinic {
    struct Edge {
        int to;
        int64_t cap,rest;
    };
    vector<Edge> E;
    vector<int> g[N];
    int n,dis[N],now[N];
    void init(int sz) {
        n = sz;
        E.resize(0);
        for(int i = 0; i < n; i++) g[i].resize(0);
    }
    void add_edge(int x,int y,int64_t cap) {
        g[x].pb(E.size()), E.push_back({y,cap,cap});
        g[y].pb(E.size()), E.push_back({x,0,0});
    }
    bool BFS(int s,int t) {
        for(int i = 0; i < n; i++) dis[i] = -1;
        queue<int> q;
        q.push(s), dis[s] = 0;
        while(!q.empty()) {
            s = q.front(), q.pop();
            for(int id:g[s]) {
                int v = E[id].to;
                int64_t r = E[id].rest;
                if(dis[v]==-1 && r > 0)
                    q.push(v), dis[v] = dis[s]+1;
            }
        }
        return dis[t]!=-1;
    }
    int64_t DFS(int s,int t,int64_t lim) {
        if(s == t) return lim;
        int64_t ans = 0;
        while(now[s] < g[s].size() && lim != 0) {
            int i = g[s][now[s]++];
            if(dis[E[i].to] != dis[s]+1) continue;
            int64_t tmp = DFS(E[i].to,t,min(E[i].rest,lim));
            ans += tmp;
            E[i^1].rest += tmp;
            E[i].rest -= tmp;
            lim -= tmp;
        }
        return ans;
    }
    int64_t max_flow(int s,int t) {
        int64_t res = 0;
        while(BFS(s,t)) {
            for(int i = 0; i < n; i++) now[i] = 0;
            while(int64_t tmp = DFS(s,t,INF)) res += tmp;
        }
        return res;
    }
} flow;
