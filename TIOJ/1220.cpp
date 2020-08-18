#include <cstdio>
#include <vector>

const int N = 100025;
inline char readchar() {
    constexpr int B = 1<<20;
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

std::vector<int> g[N];
bool in[N], vis[N];
int nxt[N], prv[N], n, m;
int stk[N], p;
void del(int i) {
    nxt[prv[i]] = nxt[i];
    prv[nxt[i]] = prv[i];
}
void dfs(int s) {
    p = 0, stk[p++] = s;
    while(p) {
        int i = stk[--p];
        for(int j: g[i]) in[j] = true;
        for(int i = nxt[0]; i <= n; i = nxt[i]) if(!in[i]) {
            vis[i] = true;
            del(i);
            stk[p++] = i;
        }
        for(int j: g[i]) in[j] = false;
    }
}
signed main() {
    n = nextint(), m = nextint();
    for(int i = 0; i < m; i++) {
        int a = nextint(), b = nextint();
        g[a].push_back(b), g[b].push_back(a);
    }
    int cnt = 0;
    nxt[0] = 1;
    for(int i = 1; i <= n; i++) nxt[i] = i+1, prv[i] = i-1;
    for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i), ++cnt;
    printf("%d\n", cnt);
}

