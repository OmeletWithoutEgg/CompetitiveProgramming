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
int gcd(int a, int b) {
    while(int t = b) b = a%b, a = t;
    return a;
}
signed main() {
    int n = nextint(), g = 0;
    while(n--) g = gcd(nextint(), g);
    printf("%d\n", g);
}
