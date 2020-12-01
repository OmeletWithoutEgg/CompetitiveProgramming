#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#include <cstdio>
#include <algorithm>
#include <utility>
#include <functional>
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
const int N = 1000025;
typedef long long ll;

int fr[N];
ll dis[N];
bool vis[N];
struct Edge {
    int to, cost, nxt;
} E[N*5];
int tot, head[N];
void addEdge(int a, int b, int c) {
    E[++tot] = {b, c, head[a]}, head[a] = tot;
}
std::pair<ll,int> pq[N];
signed main() {
    int n = nextint(), m = nextint();
    for(int i = 0; i < m; i++) {
        int a = nextint(), b = nextint(), c = nextint();
        addEdge(b, a, c);
    }
    tot = 0;
    for(int i = 1; i <= n; i++) dis[i] = 1e18;
    pq[tot++] = {dis[n+1] = 0, n+1};
    std::push_heap(pq, pq+tot, std::greater<>());
    while(tot) {
        std::pop_heap(pq, pq+tot, std::greater<>());
        auto [d, i] = pq[--tot];
        if(vis[i]) continue;
        vis[i] = true;
        for(int id = head[i]; id; id = E[id].nxt) {
            int j = E[id].to, c = E[id].cost;
            if(dis[j] > c+d) {
                dis[j] = c+d;
                fr[j] = i;
                pq[tot++] = {dis[j], j};
                std::push_heap(pq, pq+tot, std::greater<>());
            } else if(dis[j] == c+d && fr[j] > i) fr[j] = i;
        }
    }
    printf("%lld\n", dis[1]);
    for(int x = 1; x != n+1; x = fr[x]) printf("%d-", x);
    printf("%d\n", n+1);
}
