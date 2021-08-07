// constant: N, inf
// usage: init(n) -> addEdge(x, y, c) -> solve()
struct KuhnMunkres {
    int g[N][N];
    int lx[N], ly[N];
    int visx[N], visy[N];
    int slack[N], match[N];
    int n;
    void init(int _n) {
        n = _n;
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) g[i][j] = 0;
    }
    void addEdge(int a, int b, int weight) {
        g[a][b] = max(g[a][b], weight);
    }
    bool dfs(int i) {
        if(visx[i]) return false;
        visx[i] = true;
        for(int j = 0; j < n; j++) if(!visy[j]) {
            int d = lx[i] + ly[j] - g[i][j];
            if(d == 0) {
                visy[j] = true;
                if(match[j] == -1 || dfs(match[j])) {
                    match[j] = i;
                    return true;
                }
            }
        }
        return false;
    }
    bool augment(int x) {
        for(int i = 0; i < n; i++) visx[i] = visy[i] = false;
        return dfs(x);
    }
    void relabel() {
        int delta = inf;
        for(int i = 0; i < n; i++) if(visx[i]) {
            for(int j = 0; j < n; j++) if(!visy[j]) {
                delta = min(delta, lx[i] + ly[j] - g[i][j]);
            }
        }
        for(int i = 0; i < n; i++) if(visx[i]) lx[i] -= delta;
        for(int j = 0; j < n; j++) if(visy[j]) ly[j] += delta;
    }
    int solve() {
        for(int i = 0; i < n; i++) {
            lx[i] = ly[i] = 0;
            for(int j = 0; j < n; j++) lx[i] = max(lx[i], g[i][j]);
        }
        for(int i = 0; i < n; i++) match[i] = -1;
        for(int i = 0; i < n; i++) while(!augment(i)) relabel();
        int ans = 0;
        for(int j = 0; j < n; j++) if(match[j] != -1) ans += g[match[j]][j];
        return ans;
    }
} KM;
