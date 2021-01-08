#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#include <cstdio>

inline char readchar() {
    constexpr int B = 1<<16;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
const int N = 1024;

int g[N];
int dp[N][N];
inline int max(int a, int b) {
    return a < b ? b : a;
}
void solve() {
    int n = nextint();
    for(int i = 0; i < n; i++) g[i] = nextint();
    for(int i = 0; i+1 < n; i++) dp[1][i] = (g[i] == g[i+1]);
    for(int j = 2; j <= n/2; j++) {
        for(int i = 0; i+j*2 <= n; i++) {
            dp[j][i] = dp[j-1][i+1] + (g[i] == g[i+j*2-1]);
            for(int k = 1; k < j && i+k*2 < n; k++)
                dp[j][i] = max(dp[j][i], dp[k][i] + dp[j-k][i+k*2]);
        }
    }
    printf("%d\n", dp[n/2][0]);
}
signed main() {
    int t = nextint();
    while(t--)
        solve();
}
