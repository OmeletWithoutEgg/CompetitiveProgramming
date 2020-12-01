#pragma GCC optimize("Ofast")
#include <cstdio>

inline char readchar() {
    constexpr int B = 65536;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0' && c!='-') c = readchar();
    if(c=='-') return 0;
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
int main() {
    int n;
    while(n=nextint()) printf("%d %d\n", n, n-1+31-__builtin_clz(n-1));
}
