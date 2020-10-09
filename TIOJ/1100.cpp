#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#include <cstdio>
#include <cstring>
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0' && ~c) c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

using namespace std;
const int N = 1025, inf = 1 << 24;

int dp[N];
inline int max(int a, int b) { return a < b ? b : a; }
signed main() {
    int n;
    while(n = nextint()) {
        /* for(int i = 1; i <= n; i++) dp[i] = inf; */
        memset(dp, 0x3f, sizeof(int) * (n+1));
        dp[0] = 0;
        int ans = 0;
        for(int i = 0; i < n; i++) {
            int L = nextint() - 1;
            int R = nextint();
            int P = nextint();
            int last = 0;
            for(int c = 1; c <= ans+1; c++) {
                int T = max(last, L) + P;
                if(T > R) break;
                last = dp[c];
                if(T <= R && dp[c] > T)
                    dp[c] = T;
            }
            if(dp[ans+1] <= inf) ++ans;
        }
        printf("%d\n", ans);
    }
}
