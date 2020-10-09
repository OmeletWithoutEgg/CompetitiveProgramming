#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p=buf, *q=buf;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
struct FastOut {
    char *buf;
    int q;
    const int B;
    inline void writeln(int x) {
        static char stk[20];
        char p = 0;
        if(!x) stk[p++] = '0';
        while(x) stk[p++] = x%10^'0', x/=10;
        while(p) buf[q++] = stk[--p];
        buf[q++] = '\n';
        if(q + 20 >= B) fwrite_unlocked(buf, 1, q, stdout), q = 0;
    }
    FastOut(int B = 1<<20) : B(B), q(0), buf(new char[B]){}
    ~FastOut() {
        fwrite_unlocked(buf, 1, q, stdout);
        delete [] buf;
    }
};
const int N = 10000001, K = 65536;
short d[N], prs[K], it;
char np[N];
signed main() {
    d[1] = 1;
    for(int i = 2; i < N; i++) {
        if(!np[i]) {
            np[i] = 1;
            d[i] = 2;
            if(i < K) prs[it++] = i;
        }
        for(int j = 0; j < it && i*prs[j] < N; j++) {
            int p = prs[j];
            if(i%p) {
                np[i*p] = 1;
                d[i*p] = d[i]*d[p];
            } else {
                np[i*p] = np[i]+1;
                d[i*p] = d[i]/(np[i]+1)*(np[i]+2);
                break;
            }
        }
    }
    int q = nextint();
    FastOut ouf;
    while(q--) {
        int n = nextint();
        ouf.writeln(d[n]);
    }
}
