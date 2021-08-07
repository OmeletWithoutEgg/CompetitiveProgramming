struct BipartiteMatching {
    vector<int> gx[maxn];
    int mx[maxn],my[maxn],vis[maxn],now;
    void init() {
        for (now = 0; now < maxn; now++) gx[now].clear();
    }
    void addEdge(int x,int y) {
        gx[x].emplace_back(y);
    }
    bool dfs(int x) {
        if (vis[x] == now) return false;
        vis[x] = now;
        for (int y: gx[x]) {
            if (my[y] == -1 || dfs(my[y]))
                return mx[x]=y, my[y]=x, true;
        }
        return false;
    }
    int greedy() {
        int ans = 0;
        for (now = 0; now < maxn; now++)
            for (int y: gx[now])
                if (my[y]==-1) {
                    my[y] = now, mx[now] = y, ans++;
                    break;
                }
        return ans;
    }
    int solve() {
        int ans = 0;
        mem(mx,-1), mem(my,-1), mem(vis,-1);
        ans += greedy();
        for (now = 0; now < maxn; now++)
            if (mx[now] == -1 && dfs(now))
                ans++;
        return ans;
    }
    void dbg() {
        for (now = 0; now < maxn; now++) for (int y: gx[now]) cout << now << ' ' << y << '\n';
    }
} solver;
