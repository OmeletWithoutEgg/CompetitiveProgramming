struct bpt_matching {
    vector<int> gx[N];
    int mx[N],my[N],vis[N],now;
    void init() {
        for(now = 0; now < N; now++) gx[now].clear();
    }
    void addE(int x,int y) {
        gx[x].pb(y);
    }
    int dfs(int x) {
        if(vis[x] == now) return false;
        vis[x] = now;
        //debug(x);
        for(int y:gx[x]) {
            if(my[y]==-1 || dfs(my[y]))
                return mx[x]=y, my[y]=x, true;
        }
        return false;
    }
    int greedy() {
        int ans = 0;
        for(now = 0; now < N; now++) for(int y:gx[now]) if(my[y]==-1) {
            my[y] = now, mx[now] = y, ans++;
            break;
        }
        return ans;
    }
    int solve() {
        int ans = 0;
        mem(mx,-1), mem(my,-1), mem(vis,-1);
        ans += greedy();
        for(now = 0; now < N; now++) {
            //debug(now);
            if(mx[now]==-1 && dfs(now)) ans++;
            //for(int i = 0; i < N; i++) cout << mx[i] << ' '; cout << '\n';
        }
        return ans;
    }
    void dbg() {
        for(now = 0; now < N; now++) for(int y:gx[now]) cout << now << ' ' << y << '\n';
    }
} solver;
