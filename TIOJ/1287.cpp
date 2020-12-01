#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
#include <algorithm>
inline char readchar() {
    static const int B = 1<<20;
    static char buf[B], *p, *q;
    if(p==q && (q=buf+fread(buf,1,B,stdin)) == (p=buf)) return EOF;
    return *p++;
}
inline int nextint() {
    char neg = false, c = readchar();
    int x = 0;
    while(c < '0' && c!='-' && c != EOF) c = readchar();
    if(c == '-') neg = true, c = readchar();
    while(c >= '0') x = x*10 + (c^'0'), c = readchar();
    if(neg) x = -x;
    return x;
}

int n,v[1000000];
signed main() {
    while(n = nextint()) {
        for(int i = 0; i < n; i++) v[i] = nextint();
        std::sort(v,v+n);
        for(int i = 0; i < n; i++) printf("%d%c", v[i], " \n"[i+1==n]);
    }
}
