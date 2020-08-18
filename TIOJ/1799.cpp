#pragma g++ optimize("Ofast, unroll-loops")
#pragma simd
#pragma loop_opt(on)
#include <cstdio>
#include <algorithm>
#include <numeric>

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    register int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

int n;
long long avg, v[5000000];
signed main() {
    n = nextint();
    for(register int i = 0; i < n; i++) v[i] = nextint();
    avg = std::accumulate(v,v+n,0LL) / n;
    for(register int i = 0; i < n; i++) v[i] -= avg;
    std::partial_sum(v,v+n,v);
    std::nth_element(v,v+n/2,v+n);
    printf("%lld\n", std::accumulate(v+(n+1)/2,v+n,0LL) - std::accumulate(v,v+n/2,0LL));
    // x[i] - x[i-1] = a[i] - avg
    // fix x[0] = x, x[1] = a[0]-avg+x[0], x[i] = \sum_{j=0}^{i-1} a[i]-avg
}

