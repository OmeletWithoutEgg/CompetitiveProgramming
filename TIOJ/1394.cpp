#include <cstdio>
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p=buf, *q=buf;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while('0'>c||c>'9') c = readchar();
    while('0'<=c&&c<='9') x=x*10+(c^'0'), c=readchar();
    return x;
}
inline int min(int a,int b){return a<b?a:b;}
const int N = 40000;

int dp[N][2], to[N], st[N], ed[N], vis[N];
void dfs(int i) {
    if(vis[i]) return;
    vis[i] = true;
    dp[i][0] = 0;
    dp[i][1] = 1;
    for(int k = st[i]; k != ed[i]; k++) {
        int j = to[k];
        dfs(j);
        dp[i][0] += dp[j][1];
        dp[i][1] += min(dp[j][0],dp[j][1]);
    }
}
signed main() {
    int n = nextint();
    for(int i = 0, m = 0; i < n; i++) {
        int k = nextint();
        for(int j = 0; j < k; j++) to[m+j] = nextint();
        st[i] = m;
        m += k;
        ed[i] = m;
    }
    dfs(0);
    printf("%d\n", min(dp[0][0],dp[0][1]));
}

