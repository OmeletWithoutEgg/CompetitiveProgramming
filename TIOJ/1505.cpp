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

signed main() {
    int t = nextint();
    while(t--) {
        int n = nextint();
        int res = nextint(), mod = nextint();
        for(int i = 2; i < n; i++) res = 1LL * res * nextint() % mod;
        puts(res ? "zzz..." : "Asssss!!");
    }
}
