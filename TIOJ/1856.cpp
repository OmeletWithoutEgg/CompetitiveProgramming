#include <cstdio>
#include <algorithm>
#include <functional>

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

int v[100001], n, t;
inline int calc(int x) {
    int cnt = 0;
    for(int i = 0; i < n; i++) if(v[i] > x) ++cnt;
    return cnt;
}
signed main() {
    t = nextint();
    while(t--) {
        n = nextint();
        for(int i = 0; i < n; i++) v[i] = nextint();
        int x = 0;
        for(int s = 1<<18; s; s >>= 1) if(calc(x+s) >= x+s) x += s;
        //printf("x = %d\n", x);
        long long ans = 0;
        std::nth_element(v,v+x,v+n,std::greater<int>());
        for(int i = 0; i < x; i++) ans += v[i];
        //for(int i = 0; i < n; i++) if(v[i] > x) ans += v[i];
        printf("%lld\n", ans - 1LL*x*(x+1)/2);
    }
}

