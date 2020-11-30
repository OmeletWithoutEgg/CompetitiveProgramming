#pragma GCC optimize("Ofast")
#pragma GCC target("popcnt")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#pragma loop_opt(on)
#include <bitset>
#include <cstdio>

inline char readchar() {
    constexpr int B = 1<<15;
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

using namespace std;
const int N = 80, inf = 1e9;
using magic = bitset<N>;

int n, m;
magic g[N];
int ans = inf;
void dfs(int c, magic alive) {
    if(c > ans) return;
    // reduce
    int mx = -1, mxDeg = -1;
    for(int i = alive._Find_first(); i < n; i = alive._Find_next(i)) {
        int deg = (alive & g[i]).count();
        if(deg == 1) {
            int j = (alive & g[i])._Find_first();
            alive[i] = alive[j] = false;
            dfs(c+1, alive);
            return;
        }
        if(deg != 0 && deg > mxDeg)
            mx = i, mxDeg = deg;
    }
    if(mx == -1) {
        ans = min(ans, c);
        return;
    }
    alive[mx] = false;
    dfs(c+1, alive);
    magic adj = alive & g[mx];
    dfs(c+adj.count(), alive ^ adj);
}
signed main() {
    n = nextint();
    m = nextint();
    for(int i = 0; i < m; i++) {
        int a = nextint();
        int b = nextint();
        g[a][b] = g[b][a] = true;
    }
    magic alive;
    for(int i = 0; i < n; i++) alive[i] = true;
    dfs(0, alive);
    printf("%d\n", n - ans);
}
