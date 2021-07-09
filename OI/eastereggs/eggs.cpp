#include <bits/stdc++.h>
#include "grader.h"

#ifdef local
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define pary(a...) danb(#a, a)
#define debug(a...) qqbx(#a, a)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\033[1;32m(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\033[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\033[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\033[0m\n";
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#define pary(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define pb emplace_back

using namespace std;
const int maxn = 525;

vector<int> g[maxn];
bool vis[maxn];
/*
int sz[maxn], mxCh[maxn];
void getSize(int i, int p = 0) {
    sz[i] = 1;
    mxCh[i] = -1;
    for (int j: g[i]) {
        if (j != p && !vis[j]) {
            getSize(j, i);
            sz[i] += sz[j];
            if (mxCh[i] == -1 || sz[mxCh[i]] < sz[j])
                mxCh[i] = j;
        }
    }
}
int findCent(int n, int i, int p = 0) {
    for (int j: g[i]) {
        if (j != p && !vis[j]) {
            if (sz[j] * 2 >= n)
                return findCent(n, j, i);
        }
    }
    return i;
}
void cd(int i) {
    getSize(i);
    int c = findCent(sz[i], i);
    vis[c] = true;
    if (mxCh[c] != -1) {
        dfs(mxCh[c]);
    }
}
*/
int findEgg (int N, vector < pair < int, int > > bridges) {
    for (int i = 1; i <= N; i++)
        g[i].clear(), vis[i] = 0;
    for (auto [a, b]: bridges) {
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    queue<int> q;
    vector<int> ord;
    vis[1] = true;
    q.push(1);
    while (!q.empty()) {
        int i = q.front(); q.pop();
        ord.emplace_back(i);
        debug(i);
        for (int j: g[i]) {
            if (!vis[j]) {
                vis[j] = true;
                q.push(j);
            }
        }
    }
    int pos = 0;
    for (int s = 1 << 20; s; s >>= 1) {
        if (pos + s >= N) continue;
        auto qq = vector<int>(ord.begin(), ord.begin() + pos + s);
        pary(all(qq));
        if (query(qq) == 0)
            pos += s;
    }
    return ord[pos];
}
