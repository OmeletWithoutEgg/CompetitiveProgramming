#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>

const int N = 8025, INF = (1LL<<31) - 1;

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
int n, k;
int x[N], y[N], c[N];
inline int dist(int a, int b) {
    return (x[a]-x[b]) * (x[a]-x[b]) + (y[a]-y[b]) * (y[a]-y[b]);
}
struct edge {
    int to, prv, nxt, cost;
} E[N];
int head[N], tot;
void addedge(int a, int b, int c) {
    E[tot] = {b, -1, head[a], c}, head[a] = E[head[a]].prv = tot++;
    E[tot] = {a, -1, head[b], c}, head[b] = E[head[b]].prv = tot++;
}
void deledge(int id) {
    if(~E[id].nxt) E[E[id].nxt].prv = E[id].prv;
    if(~E[id].prv) E[E[id].prv].nxt = E[id].nxt;
    int i = E[id^1].to;
    if(id == head[i]) head[i] = E[id].nxt, E[head[i]].prv = -1;
}
int mxe[N], val[N], d[N], fr[N];
bool used[N], ok[N];
void dfs(int i, int p = -1, int e = -1) {
    mxe[i] = e;
    for(int id = head[i]; ~id; id = E[id].nxt) {
        int j = E[id].to;
        if(j == p) continue;
        dfs(j, i, ~e && E[e].cost>E[id].cost ? e : id);
    }
}
long long solve() {
    long long ans = 0, res;
    {
        // read-in and init
        n = nextint(), k = nextint();
        if(k > n) k = n;
        for(int i = 1; i <= n; i++) x[i] = nextint(), y[i] = nextint(), c[i] = nextint();
        for(int i = 0; i <= n; i++) head[i] = -1, used[i] = false;
        tot = 0;
    }
    {
        // MST
        for(int i = 1; i <= n; i++) ok[i] = false, d[i] = INF;
        auto relax = [](int x) {
            for(int i = 1; i <= n; i++) if(!ok[i]) {
                if(d[i] > dist(i,x))
                    d[i] = dist(i,x), fr[i] = x;
            }
        };
        ok[1] = true;
        relax(1);
        for(int t = 1; t < n; t++) {
            int mn = 0;
            for(int i = 1; i <= n; i++) if(!ok[i])
                if(mn == 0 || d[mn] > d[i])
                    mn = i;
            // cout << fr[mn] << ' ' << mn << ' ' << d[mn] << '\n';
            addedge(fr[mn], mn, d[mn]);
            ans += d[mn];
            ok[mn] = true;
            relax(mn);
        }
    }
    res = ans;
    {
        // MST with smallest degree of v0
        int s = 1;
        for(int i = 1; i <= n; i++) if(c[s] > c[i]) s = i;
        addedge(0, s, c[s]);
        ans += c[s];
        used[s] = true;
        // cout << ans << '\n';
    }
    {
        // iterate and calc m+1 from m
        for(int deg = 1; deg < k; deg++) {
            dfs(0);
            for(int i = 1; i <= n; i++) val[i] = used[i] ? INF : c[i] - E[mxe[i]].cost;
            int j = 1;
            for(int i = 1; i <= n; i++) if(val[j] > val[i]) j = i;
            // assert(val[j] != INF);
            deledge(mxe[j]), deledge(mxe[j]^1);
            addedge(0, j, c[j]);
            ans += val[j];
            used[j] = true;
            if(res > ans) res = ans;
        }
    }
    return res;
}
signed main() {
    int t = nextint();
    while(t--) printf("%lld\n", solve());
}

/*
1
3 0
0 6 1
0 0 1
8 0 1
*/
