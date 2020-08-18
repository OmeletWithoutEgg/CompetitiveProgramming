#include <cstdio>
#include <vector>
#define pb emplace_back
const int N = 1000025;
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

int n,sz[N],mx[N],res;
std::vector<int> g[N];
void dfs(int u, int p) {
    for(int v: g[u]) {
        if(v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if(sz[v] > mx[u]) mx[u] = sz[v];
    }
    if(n-sz[u] > mx[u]) mx[u] = n-sz[u];
    // printf("%d\n", mx[u]);
    if(res > mx[u]) res = mx[u];
}
signed main() {
    n = res = nextint();
    for(int i = 1; i < n; i++) {
        int a = nextint(), b = nextint();
        g[a].pb(b), g[b].pb(a);
    }
    for(int i = 0; i < n; i++) sz[i] = 1, mx[i] = 0;
    dfs(0,-1);
    printf("%d\n", res);
}
