#pragma GCC optimize("Ofast")
//#pragma GCC target("sse3","sse2","sse")
//#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
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

int a[1001],d[1001];
int dp[10025];
signed main() {
    int t,W,B,m,n;
    t = nextint();
    while(t--) {
        W = nextint(), B = nextint(), n = nextint();
        for(int i = 0; i < n; i++) a[i] = nextint(), d[i] = nextint();
        m = nextint();
        for(int i = 0; i <= W; i++) dp[i] = 0;
        --W;
        for(int i = 0; i < n; i++) {
            a[i] += m;
            for(int w = a[i]; w <= W; w++)
                if(dp[w] < dp[w-a[i]] + d[i])
                    dp[w] = dp[w-a[i]] + d[i];
            if(dp[W] >= B) break;
        }
        puts(dp[W] >= B ? "Yes" : "No");
    }
}
