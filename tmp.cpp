#include <bits/stdc++.h>
#ifdef local
#define safe std::cerr << __PRETTY_FUNCTION__ << " line " << __LINE__ << " safe\n"
#define debug(a...) qqbx(#a, a)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = ("), ... , (std::cerr << a << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local

using namespace std;
const int maxn = 10025;
const int64_t INF = 1e18;

int n, m, X;
int64_t p[maxn], d[maxn], DP[maxn];
vector<int64_t> dp[2][maxn];
bool vis[maxn], used[maxn];
vector<int> combo[maxn];
map<int, vector<int>> g[maxn];
int sz[maxn];

void getSize() {
    ;
}
void dfs(int i, const vector<int> & pacs, int pa = -1) {
    debug(i);
    for (const auto &[j, cs]: g[i]) {
        if (j != pa) {
            dfs(j, cs, i);
            for (int a = n; a >= 0; a--) {
                for (int b = 1; b <= a; b++) {
                    dp[0][i][a] = min(dp[0][i][a], dp[0][i][a-b] + min(dp[0][j][b], dp[1][j][b]));
                    dp[1][i][a] = min(dp[1][i][a], dp[1][i][a-b] + dp[0][j][b]);
                }
            }
        }
    }
    for (int c: combo[i]) if (!used[c]) {
        for (int k = sz[i]; k >= 1; k--) {
            dp[0][i][k] = min(dp[0][i][k], dp[0][i][k-1] + p[c]);
        }
    }
    for (int k = sz[i]; k >= 0; k--) {
        dp[1][i][k] = (k >= combo[i].size() ? dp[1][i][k-combo[i].size()] + d[i] : INF);
        if (k) {
            for (int c: pacs)
                dp[1][i][k] = min(dp[1][i][k], dp[0][i][k-1] + p[c]);
        }
    }
    debug(i, d[i]);
}
struct Dsu {
    int pa[maxn];
    Dsu() { iota(pa, pa+maxn, 0); }
    int anc(int x) { return x==pa[x] ? x : pa[x]=anc(pa[x]); }
    bool join(int x, int y) {
        if ((x=anc(x)) == (y=anc(y))) return false;
        return pa[y] = x, true;
    }
} dsu;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m >> X;
    for (int i = 1; i <= n; i++) cin >> p[i];
    map<int, int> mp;
    for (int i = 0; i < m; i++) {
        cin >> d[i];
        int sz;
        cin >> sz;
        combo[i].resize(sz);
        for (int &c: combo[i]) {
            cin >> c;
            vis[c] = true;
            if (mp.count(c)) {
                int j = mp[c];
                g[i][j].push_back(c);
                g[j][i].push_back(c);
                dsu.join(i, j);
                used[c] = true;
            } else {
                mp[c] = i;
            }
        }
    }
    for (int i = 1; i <= n; i++) if (!vis[i]) combo[m].emplace_back(i);
    for (int i = 0; i <= m; i++) for (int k = 1; k <= n; k++) dp[0][i][k] = dp[1][i][k] = INF;
    p[0] = INF;
    d[m] = 0;
    for (int i = 0; i < m; i++)
        if (dsu.anc(i) == i)
            g[i][m].push_back(0), g[m][i].push_back(0);
    dfs(m, vector<int>());

    /*
    for (int d: {0, 1})
        for (int i = 0; i <= m; i++) {
            for (int k = 0; k <= n; k++) {
                cerr << dp[d][i][k] << ' ';
            }
            cerr << '\n';
        }
    */
    for (int k = n; k >= 0; k--)
        if (dp[0][m][k] <= X)
            return cout << k << '\n', 0;
    cout << -1 << '\n';
}

/*
5 2 7
1 2 5 3 4
6 2 2 3
5 3 1 4 5

6 4 17
2 5 7 3 4 3
3 2 1 2
9 2 4 5
10 2 2 3
8 2 3 5
*/
