#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")

#include <unistd.h>

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+read(0, buf, B)) == buf) return -1;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
inline void writeint(int x) {
    static char stk[20], buf[20];
    char p = 0, q = 0;
    if(!x) stk[p++] = '0';
    while(x) stk[p++] = x%10^'0', x/=10;
    while(p) buf[q++] = stk[--p];
    write(1, buf, q);
}

inline int calc(int n, register int m) {
    register int r = 0;
    for(register int i = 1; i <= n; i++) r = (r + m) % i;
    return r;
}
signed main() {
    int n = nextint(), k = nextint();
    --k;
    for(register int i = 2; i <= 30000; i++) if(calc(n, i) == k) return writeint(i), 0;
    writeint(0);
}
