#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#include <cstdio>
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
struct FastOut {
    char *buf;
    int q;
    const int B;
    inline void writeln(int x) {
        static char stk[20];
        char p = 0;
        if(!x) stk[p++] = '0';
        while(x) stk[p++] = x%10^'0', x/=10;
        while(p) buf[q++] = stk[--p];
        buf[q++] = '\n';
        if(q + 20 >= B) fwrite(buf, 1, q, stdout), q = 0;
    }
    FastOut(int B = 1<<20) : B(B), q(0), buf(new char[B]){}
    ~FastOut() {
        fwrite(buf, 1, q, stdout);
        delete [] buf;
    }
};

const int N = 100025, K = 18;
struct Edge {
    int to, nxt;
} E[N*2];
int head[N];
void addEdge(int a, int b) {
    static int tot;
    E[++tot] = {b, head[a]}, head[a] = tot;
    E[++tot] = {a, head[b]}, head[b] = tot;
}
int n, q;
int vis[N], tot, dep[N];
int st[K][N*2];
inline void dfs(int i, int p) {
    st[0][vis[i] = tot++] = dep[i];
    for(int id = head[i]; id; id = E[id].nxt) {
        int j = E[id].to;
        if(j == p) continue;
        dep[j] = dep[i] + 1;
        dfs(j, i);
        st[0][tot++] = dep[i];
    }
}
inline int min(int a, int b) { return a<b?a:b; }
inline int query(int a, int b) {
    if(a > b) { int t=a; a=b; b=t; }
    int L = 31-__builtin_clz(b-a);
    /* printf("1<<L=%d, a=%d, b-(1<<L)+1=%d\n", 1<<L, a, b-(1<<L)+1); */
    /* printf("A=%d, B=%d\n", st[L][a], st[L][b-(1<<L)+1]); */
    return min(st[L][a], st[L][b-(1<<L)+1]);
}

signed main() {
    n = nextint(), q = nextint();
    for(int i = 1; i < n; i++) {
        int a = nextint(), b = nextint();
        addEdge(a, b);
    }
    dfs(0, -1);
    for(int L = 1; L < K; L++) {
        int len = 1 << L - 1;
        for(int i = 0; i+len*2 < tot; i++) {
            st[L][i] = min(st[L-1][i], st[L-1][i+len]);
        }
    }
    FastOut ouf;
    while(q--) {
        int a = nextint(), b = nextint();
        ouf.writeln(dep[a] + dep[b] - query(vis[a], vis[b]) * 2);
    }
}
