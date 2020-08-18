#include <cstdio>
const int N = 267981;
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p=buf, *q=buf;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(('0'>c||c>'9')&&~c) c = readchar();
    while('0'<=c&&c<='9') x=x*10+(c^'0'), c=readchar();
    return x;
}


int n,he[N],ta,i;
int L[229659],R[227742],S[276732];
signed main() {
    while(n = nextint()) {
        for(i = 0; i < n; i++) he[i] = nextint();
        ta = 0;
        for(i = 0; i < n; i++) {
            while(ta && he[S[ta-1]] < he[i]) --ta;
            L[i] = (ta ? S[ta-1] : 0);
            S[ta++] = i;
        }
        ta = 0;
        for(i = n-1; i >= 0; i--) {
            while(ta && he[S[ta-1]] < he[i]) --ta;
            R[i] = (ta ? S[ta-1] : n-1);
            S[ta++] = i;
        }
        for(i = 0; i < n; i++) printf("%d%c", R[i]-L[i]+1, " \n"[i+1==n]);
    }
}

