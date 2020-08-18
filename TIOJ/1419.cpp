#pragma g++ optimize("Ofast")
#include <cstdio>
#include <algorithm>
inline char readchar() {
    static const constexpr int B = 1<<20;
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

struct node{
    int d, h;
    bool operator<(const node &rhs) const {
        return d!=rhs.d ? d<rhs.d : h>rhs.h;
    }
} v[100001];
signed main() {
    int n = nextint();
    for(int i = 0; i < n; i++) {
        int x = nextint();
        int y = nextint();
        int h = nextint();
        v[i] = {x*x+y*y, h};
    }
    std::sort(v, v+n);
    int best = 0, mx = 0;
    for(int i = 0; i < n; i++) {
        if(mx < v[i].h) mx = v[i].h;
        if(best < mx-v[i].h) best = mx-v[i].h;
    }
    printf("%d\n", best);
}

