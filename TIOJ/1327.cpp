#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>
#define pb emplace_back

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

typedef long long ll;
const int N = 100025;

int n, m;
struct Point {
    ll x, y;
    int id;
} v[N];
struct Edge {
    ll w;
    int a, b;
} edges[N*2];
struct DisjointSets {
    int pa[N], rk[N];
    void init(int n) {
        for(int i = 0; i < n; i++) pa[i] = i, rk[i] = 0;
    }
    int anc(int x){return x==pa[x] ? x : pa[x]=anc(pa[x]);}
    bool join(int x, int y) {
        if((x=anc(x)) == (y=anc(y))) return false;
        if(rk[x] < rk[y]) std::swap(x,y);
        return pa[y] = x, rk[x]!=rk[y] || ++rk[x];
    }
} dsu;
void addEdge(int a, int b, ll w) {
    edges[m++] = {w, a, b};
}
void solve() {
    n = nextint();
    for(int i = 0; i < n; i++) v[i].x = nextint(), v[i].y = nextint(), v[i].id = i;
    m = 0;
    std::sort(v,v+n,[](Point &a, Point &b){return a.x != b.x ? a.x < b.x : a.y < b.y;});
    for(int i = 1; i < n; i++) {
        if(v[i].x == v[i-1].x)
            addEdge(v[i].id, v[i-1].id, v[i].y - v[i-1].y);
    }
    std::sort(v,v+n,[](Point &a, Point &b){return a.y != b.y ? a.y < b.y : a.x < b.x;});
    for(int i = 1; i < n; i++) {
        if(v[i].y == v[i-1].y)
            addEdge(v[i].id, v[i-1].id, v[i].x - v[i-1].x);
    }
    dsu.init(n);
    std::sort(edges, edges+m, [](Edge &a, Edge &b){return a.w<b.w;});
    ll ans = 0;
    for(int i = 0; i < m; i++) if(dsu.join(edges[i].a, edges[i].b)) ans += edges[i].w;
    printf("%lld\n", ans);
}
signed main() {
    int t = nextint();
    while(t--)
        solve();
}
