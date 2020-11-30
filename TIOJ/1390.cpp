#include <vector>
#include <unistd.h>
#define pb emplace_back

using namespace std;
const int inf = 1e9, N = 16;


inline char readchar() {
    constexpr int B = 1<<10;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+read(0, buf, B)) == buf) return -1;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0' && ~c) c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
inline void writeln(int x) {
    static char stk[20], buf[20];
    char p = 0, q = 0;
    if(!x) stk[p++] = '0';
    while(x) stk[p++] = x%10^'0', x/=10;
    while(p) buf[q++] = stk[--p];
    buf[q++] = '\n';
    write(1, buf, q);
}

struct DirectedMST {
    struct Edge {
        int u, v;
        int w;
        Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    };
    vector<Edge> Edges;
    void clear() { Edges.clear(); }
    void addEdge(int a, int b, int w) {
        Edges.pb(a, b, w);
    }
    int solve(int root, int n) {
        vector<Edge> E = Edges;
        int ans = 0;
        while(true) {
            // find best in edge
            vector<int> in(n, -inf), prv(n, -1);
            for(auto e: E) if(e.u != e.v && e.w > in[e.v]) {
                in[e.v] = e.w;
                prv[e.v] = e.u;
            }
            in[root] = 0;
            prv[root] = -1;
            for(int i = 0; i < n; i++) if(in[i] == -inf) return -inf;
            // find cycle
            int tot = 0;
            vector<int> id(n, -1), vis(n, -1);
            for(int i = 0; i < n; i++) {
                ans += in[i];
                for(int x = i; x != -1 && id[x] == -1; x = prv[x]) {
                    if(vis[x] == i) {
                        for(int y = prv[x]; y != x; y = prv[y]) id[y] = tot;
                        id[x] = tot++;
                        break;
                    }
                    vis[x] = i;
                }
            }
            if(!tot) return ans;
            for(int i = 0; i < n; i++) if(id[i] == -1) id[i] = tot++;
            // shrink
            for(auto &e: E) {
                if(id[e.u] != id[e.v]) e.w -= in[e.v];
                e.u = id[e.u], e.v = id[e.v];
            }
            n = tot;
            root = id[root];
        }
        return 7122;
    }
} DMST;
int val[N][N];
signed main() {
    int n;
    while(n = nextint()) {
        DMST.clear();
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) val[i][j] = nextint();
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
            int to = nextint();
            if(i < j) DMST.addEdge(to, i^j^to, val[i][j]);
        }
        int ans = 0;
        for(int i = 0; i < n; i++) ans = max(ans, DMST.solve(i, n));
        writeln(ans);
    }
}
