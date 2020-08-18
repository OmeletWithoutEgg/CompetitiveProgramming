#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")

#include <cstdio>
#include <algorithm>

inline char readchar() {
    constexpr int B = 65536;
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

const int N = 5025;
int M, dp[N], sum[N];
int v[N], n, k;
int add(unsigned a, unsigned b){return a+b<M ? a+b : a+b-M;}
int sub(unsigned a, unsigned b){return b ? add(a, M-b) : a;}
void go(int cnt) {
    sum[k+1] = 0;
    for(int w = k; w >= 0; w--) sum[w] = add(sum[w+1], dp[w]);
    for(int w = k; w >= 0; w--) {
        int l = w<cnt ? 0 : w-cnt;
        int r = w;
        dp[w] = add(dp[w], sub(sum[l], sum[r]));
    }
}
signed main() {
    while(n = nextint()) {
        k = nextint(), M = nextint();
        for(int i = 0; i < n; i++) v[i] = nextint();
        std::sort(v,v+n);
        dp[0] = 1;
        for(int i = 1; i <= k; i++) dp[i] = 0;
        for(int i = 0, j; i < n; i = j) {
            for(j = i; j < n; j++) if(v[i]!=v[j]) break;
            go(j-i);
        }
        printf("%u\n", dp[k]);
    }
}
