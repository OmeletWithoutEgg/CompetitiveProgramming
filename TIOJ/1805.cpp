#include <cstdio>
#include <algorithm>
using namespace std;
inline char readchar() {
    constexpr int B = 1<<15;
    static char buf[B], *p=buf, *q=buf;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    bool neg=false;
    int x = 0, c = readchar();
    while(('0'>c||c>'9')&&c!='-') c = readchar();
    if(c=='-') neg=true, c=readchar();
    while('0'<=c&&c<='9') x=x*10+c-'0', c=readchar();
    if(neg) x = -x;
    return x;
}

int t,n,v[4001];
signed main() {
    t = nextint();
    while(t--) {
        n = nextint();
        for(int i = 0; i < n; i++) v[i] = nextint();
        sort(v,v+n);
        int m = (v[0]+v[n-1]+1)/2;
        int z = lower_bound(v,v+n,m) - v;
        int L = z==0 ? 0 : v[z-1] - v[0];
        int R = z==n ? 0 : v[n-1] - v[z];
        printf("%d\n", max(L,R));
    }
}

