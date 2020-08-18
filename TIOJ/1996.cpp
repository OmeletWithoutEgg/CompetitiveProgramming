#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#define pb emplace_back
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include "lib1996.h"
using namespace std;
const int N = 3000025, K = 60000025, inf = 1e9;
int pa[N],rk[N];
int anc(int x){return x==pa[x] ? x : (pa[x]=anc(pa[x]));}
void uni(int x,int y) {
    pa[y = anc(y)] = x = anc(x);
    if(rk[x]!=rk[y]) ++rk[x];
}
struct {
    int to, nxt;
} E[K];
int head[N*2],tot;
void addEdge(int a,int b) {
    E[++tot] = {b,head[a]}, head[a] = tot;
}
int dis[N*2],q[N*2];
inline void init(int n,int m,int A[],int B[],int W[]) {
    for(register int i = 0; i < n; i++) pa[i] = i;
    for(register int i = 0; i < m; i++) if(W[i] == 0) uni(A[i],B[i]);
    for(register int i = 0; i < m; i++) {
        int a = anc(A[i]), b = anc(B[i]);
        if(a == b) continue;
        if(W[i] == 1) {
            addEdge(a,b), addEdge(b,a);
        }else if(W[i] == 2) {
            addEdge(a,n), addEdge(b,n), addEdge(n,a), addEdge(n,b);
            pa[n] = n, n++;
        }
    }
    for(int i = 0; i < n; i++) dis[i] = -1;
    //memset(dis, -1, sizeof dis);
    int s = anc(0), h = 0, t = 0;
    dis[q[t++]=s] = 0;
    while(h!=t) {
        int i = q[h++];
        for(int id=head[i]; id; id=E[id].nxt) if(dis[E[id].to]==-1) dis[q[t++]=E[id].to]=dis[i]+16;
    }
}

inline int get_cost(int x) {
    register int d = dis[anc(x)];
    if(d == -1) return -1;
    return d;
}
