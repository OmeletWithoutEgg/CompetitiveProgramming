#include <cstdio>
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
const int N = 16, inf = 1e9;
inline int cdiv(int x, int m) {return (x+m-1)/m;}
inline int __lg(int x) {return 31 - __builtin_clz(x);}
inline int abs(int x) {return x<0 ? -x : x;}
int m,n,dp[N][1<<N];
int x[N],y[N],t[N];
signed main() {
    while(m = nextint(), n = nextint()) {
        for(int i = 0; i < n; i++) {
            x[i] = nextint()-1;
            y[i] = nextint()-1;
            t[i] = nextint();
        }
        for(int i = 0; i < n; i++) for(int s = 0; s < (1<<n); s++) dp[i][s] = inf;
        for(int i = 0; i < n; i++) dp[i][1<<i] = cdiv(x[i]+y[i], t[i]) * t[i];
        for(int s = 0; s < (1<<n); s++) {
            for(int u = s; u; u -= u&-u) {
                int f = s^(u&-u);
                for(int v = f; v; v -= v&-v) {
                    int i = __lg(u&-u);
                    int j = __lg(v&-v);
                    int T = cdiv(dp[j][f]+abs(x[i]-x[j])+abs(y[i]-y[j]), t[i]) * t[i];
                    if(dp[i][s] > T) dp[i][s] = T;
                }
            }
        }
        int mn = inf;
        for(int i = 0; i < n; i++) if(mn > dp[i][(1<<n)-1]) mn = dp[i][(1<<n)-1];
        printf("%d\n", mn);
    }
}

