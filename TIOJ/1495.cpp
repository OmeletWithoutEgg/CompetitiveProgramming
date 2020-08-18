#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
const int N = 500001, MOD = 1000000007;
int pa[N],rk[N];
int anc(int x) {return x==pa[x] ? x : (pa[x] = anc(pa[x]));}
bool uni(int x,int y) {
    if((x=anc(x)) == (y=anc(y))) return false;
    if(rk[x] < rk[y]) swap(x,y);
    return pa[y] = x, rk[x]!=rk[y] || ++rk[x];
}
int n,m;
int a[N],b[N],c[N];
char vis[N],valid = 1;
struct edge {
    int to, nxt;
} E[N];
int tot,head[N];
void add_edge(int a, int b) {
    E[tot] = {b, head[a]}, head[a] = tot++;
}
void dfs(int i) {
    static int stk[N], p;
    p = 0;
    stk[p++] = i;
    while(p) {
        i = stk[--p];
        for(int id = head[i]; id; id = E[id].nxt) {
            int j = E[id].to;
            if(!vis[j]) vis[j] = -vis[i], stk[p++] = j;
            else if(vis[i] == vis[j]) valid = 0;
        }
    }
}
signed main() {
    scanf("%d%d", &n, &m);
    iota(pa, pa+n, 0);
    int CC = n;
    for(int i = 0; i < m; i++) scanf("%d%d%d", a+i, b+i, c+i);
    for(int i = 0; i < m; i++) if(c[i] && uni(a[i],b[i])) --CC;
    for(int i = 0; i < m; i++) if(!c[i]) add_edge(anc(a[i]), anc(b[i]));
    for(int i = 0; i < n; i++) if(i == anc(i) && !vis[i]) {
        vis[i] = 1;
        dfs(i);
    }
    for(int i = 0; i < m; i++) if(!c[i] && uni(a[i],b[i])) --CC;
    long long ans = valid;
    while(--CC) ans = (ans*2%MOD);
    printf("%lld\n", ans);
}

