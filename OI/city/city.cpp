#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int f = 0;
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << (f++ ? ", " : "") << args)), std::cerr << ")\n";
}
#else
#define debug(...) ((void)0)
#endif // local
using namespace std;
const int maxn = 100025, mod = 1e9;
namespace dsu {
int pa[maxn], sz[maxn];
void init(int N) {
    for (int i = 0; i < N; i++) pa[i] = i, sz[i] = 1;
}
int anc(int x) {
    return x==pa[x] ? x : pa[x] = anc(pa[x]);
}
bool join(int x, int y) {
    if ((x=anc(x)) == (y=anc(y))) return false;
    if (sz[x] < sz[y]) swap(x, y);
    return pa[y] = x, sz[x] += sz[y], true;
}
}

struct Point {
    int x, y, id;
} pts[maxn];

vector<int> tr[maxn];
bool vis[maxn];
int ds[maxn], sz[maxn];
int ans;
void dfs(int i) {
    vis[i] = true;
    sz[i] = dsu::sz[i];
    ds[i] = 0;
    debug(i, sz[i]);
    for (int j: tr[i]) {
        if (vis[j]) continue;
        dfs(j);
        ans = (ans + 1LL * sz[i] * (ds[j] + sz[j]) + 1LL * sz[j] * ds[i]) % mod;
        ds[i] = (ds[i] + ds[j] + sz[j]) % mod;
        sz[i] += sz[j];
    }
    debug(i, ds[i], sz[i]);
}
void solve(int N) {

    for (int i = 0; i < N; i++) tr[i].clear(), vis[i] = false;
    sort(pts, pts + N, [](Point a, Point b) { return a.x != b.x ? a.x < b.x : a.y < b.y; });
    dsu::init(N);
    for (int i = 1; i < N; i++) {
        if (pts[i].x == pts[i-1].x && pts[i].y == pts[i-1].y + 1)
            dsu::join(pts[i].id, pts[i-1].id);
    }
    sort(pts, pts + N, [](Point a, Point b) { return a.y != b.y ? a.y < b.y : a.x < b.x; });
    for (int i = 1; i < N; i++) {
        if (pts[i].y == pts[i-1].y && pts[i].x == pts[i-1].x + 1) {
            int a = dsu::anc(pts[i].id);
            int b = dsu::anc(pts[i-1].id);
            tr[a].push_back(b);
            tr[b].push_back(a);
        }
    }
#define sort_uni(v) sort(v.begin(),v.end()),v.erase(unique(v.begin(), v.end()), v.end())
    for (int i = 0; i < N; i++)
        sort_uni(tr[i]);
    dfs(dsu::anc(0));
    debug(dsu::anc(0));
    debug("HERE");
}
int DistanceSum(int N, int *X, int *Y) {
    ans = 0;

    for (int i = 0; i < N; i++)
        pts[i] = { X[i], Y[i], i };
    solve(N);
    for (int i = 0; i < N; i++)
        pts[i] = { Y[i], X[i], i };
    solve(N);
    return ans % mod;

}
