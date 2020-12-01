#pragma g++ optimize("O3")
#pragma loop_opt(on)
#include <cstdio>
#include <algorithm>
const int N = 1000001;
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p=buf, *q=buf;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    //bool neg=false;
    int x = 0, c = readchar();
    while('0'>c||c>'9') c = readchar();
    //if(c=='-') neg=true, c=readchar();
    while('0'<=c&&c<='9') x=x*10+(c^'0'), c=readchar();
    //if(neg) x = -x;
    return x;
}

int n,L,x[N],id[N],cnt;
signed main() {
    int t = -1e9, dir, pos;
    n = nextint(), L = nextint();
    for(int i = 0,d; i < n; i++) {
        x[i] = nextint();
        d = nextint();
        int dis = d ? L-x[i] : x[i];
        if(t < dis) t = dis, dir = d;
        if(!d) cnt++;
    }
    pos = cnt+dir-1;
    for(int i = 0; i < n; i++) id[i] = i;
    std::nth_element(id,id+pos,id+n,[](int a,int b){return x[a]<x[b];});
    printf("%d\n", id[pos]);
}

/*
3 4
0 0
1 0
2 0
*/
