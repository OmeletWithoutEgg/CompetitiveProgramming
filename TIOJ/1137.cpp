#include <cstdio>
#include <algorithm>
const int N = 10001, M = 200025;
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p=buf, *tail=buf;
    if(p == tail) {
        tail = buf+fread(buf, 1, B, stdin);
        if(tail == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while('0'>c||c>'9') c = readchar();
    while('0'<=c&&c<='9') x=x*10+c-'0', c=readchar();
    return x;
}
int head[N],to[M],nxt[M],tot;
inline void addedge(int a,int b) {
    ++tot, to[tot]=b, nxt[tot]=head[a], head[a]=tot;
}
int vis[N],low[N],ap[N];
void dfs(int i, int f = 0) {
    int child = 0;
    low[i] = vis[i] = ++tot;
    for(int id=head[i]; id; id=nxt[id]) {
        int j = to[id];
        if(!vis[j]) {
            child++;
            dfs(j,i);
            if(low[j] < vis[i]) low[i] = std::min(low[i], low[j]);
            else ap[i] = true;
        }else if(j != f) low[i] = std::min(low[i], vis[j]);
    }
    if(!f && child == 1) ap[i] = false;
}
int tmp[N];
signed main() {
    int t = nextint();
    while(t--) {
        int n,m;
        n = nextint(), m = nextint();
        tot = 0;
        for(int i = 1; i <= n; i++) head[i] = vis[i] = low[i] = ap[i] = 0;
        for(int i = 0; i < m; i++) {
            int a = nextint(), b = nextint();
            addedge(a,b), addedge(b,a);
        }
        tot = 0; // wu jiz chi yon
        for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i);
        int p = 0;
        for(int i = 1; i <= n; i++) if(ap[i]) tmp[p++] = i;
        std::sort(tmp, tmp+p);
        printf("%d\n", p);
        if(!p) printf("0\n");
        else for(int i = 0; i < p; i++) printf("%d%c", tmp[i], " \n"[i==p-1]);
    }
}
