#include <cstdio>
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0' && ~c) c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
#define int long long
const int N = 525, inf = 1e18;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};
int n, m, h[N][N], vis[N][N], ans[N][N], ax[N][N], ay[N][N];
inline int min(int a, int b){return a<b?a:b;}
inline int max(int a, int b){return a>b?a:b;}
void dfs(int i, int j) {
    vis[i][j] = -1;
    for(int k = 0; k < 4; k++) {
        int x = i+dx[k], y = j+dy[k];
        if(x<1||x>n||y<1||y>m||vis[x][y]||h[x][y]<h[i][j]) continue;
        dfs(x,y);
    }
}
void DFS(int i, int j, int ai, int aj) {
    vis[i][j] = 1;
    ax[i][j] = ai, ay[i][j] = aj;
    for(int k = 0; k < 4; k++) {
        int x = i+dx[k], y = j+dy[k];
        if(x<1||x>n||y<1||y>m||vis[x][y]) continue;
        DFS(x,y,ai,aj);
        ans[i][j] = min(ans[i][j], ans[x][y]);
    }
}
signed main() {
    while(scanf("%lld%lld", &n, &m) == 2) {
        //m = nextint();
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) vis[i][j] = 0, ans[i][j] = inf;
        //for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) h[i][j] = nextint();
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%lld", &h[i][j]);
        long long res = 0;
        // 非嚴格遞增路徑
        for(int i = 1; i <= n; i++) dfs(i, 1), dfs(i, m);
        for(int j = 1; j <= m; j++) dfs(1, j), dfs(n, j);
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(!vis[i][j]) {
            for(int k = 0; k < 4; k++) {
                int x = i+dx[k], y = j+dy[k];
                if(x<1||x>n||y<1||y>m) continue;
                if(vis[x][y] == -1)
                    ans[i][j] = min(ans[i][j], h[x][y]);
            }
        }
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(!vis[i][j]) DFS(i,j,i,j);
        //puts("");
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
            int H = ~vis[i][j] ? max(h[i][j], ans[ax[i][j]][ay[i][j]]) : h[i][j];
            printf("%lld%c", H, " \n"[j==m]);
            //res += max(0, H - h[i][j]);
            res += H-h[i][j];
        }
        printf("%lld\n", res);
    }
}

/*
7 7
7 7 7 7 7 7 7
7 5 5 5 5 5 7
7 5 6 6 6 5 7
7 5 6 5 6 5 7
7 5 6 6 6 5 7
7 5 5 5 5 5 7
7 7 7 7 7 7 7

5 5
1 1 1 1 1
1 2 2 2 1
1 2 1 2 1
1 2 2 2 1
1 1 1 1 1
*/
