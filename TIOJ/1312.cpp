#pragma GCC optimize("Ofast")
#include <unistd.h>
/* #include <cstdio> */

inline char readchar() {
    constexpr int B = 1<<10;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+read(0, buf, B)) == buf) return -1;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0' && ~c) c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
char outBuf[1<<6], q;
inline void writeint(int x) {
    static char stk[10];
    char p = 0;
    while(x) stk[p++] = x%10+'0', x/=10;
    while(p) outBuf[q++] = stk[--p];
    outBuf[q++] = '\n';
}

const int N = 10005;
int n,a,b,m,k;
short pa[N];
char rk[N];
inline short anc(short x) {
    return pa[x]==x ? x : pa[x]=anc(pa[x]);
}
inline void join(short a, short b) {
    if((a=anc(a)) == (b=anc(b))) return;
    if(rk[a]<rk[b])
        pa[b]=a, rk[a]!=rk[b]||++rk[a];
    else
        pa[a]=b, rk[a]!=rk[b]||++rk[b];
}
signed main() {
    while(n=nextint()) {
        m = nextint();
        for(int i = 1; i <= n; i++) pa[i] = i, rk[i] = 0;
        while(m--) a=nextint(), b=nextint(), join(a,b);
        k = nextint();
        k = anc(k);
        for(int i = 1; i <= n; i++) if(anc(i) == k) {
            writeint(i);
            break;
        }
    }
    write(1, outBuf, q);
}
