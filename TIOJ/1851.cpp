#include <cstdio>
#include <cmath>

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline unsigned nextint() {
    char c = readchar();
    while(c < '0') c = readchar();
    unsigned x = 0;
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

signed main() {
    while(unsigned n = nextint()) {
        unsigned s = sqrt(n);
        puts(s*s==n ? "yes" : "no");
    }
}
