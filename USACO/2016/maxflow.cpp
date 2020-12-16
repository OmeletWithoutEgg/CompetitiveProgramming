#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
const int N = 50025;

vector<int> g[N];
int pa[N][20], dep[N];
int cnt[N][20];
void dfs(int i, int p = -1) {
    for(int j: g[i]) if(j != p) {
        pa[j][0] = i;
        dep[j] = dep[i] + 1;
        dfs(j, i);
    }
}
void modify(int a, int b) {
    if(dep[a] > dep[b]) swap(a, b);
    int d = dep[b] - dep[a];
    for(int i = 19; i >= 0; i--) if(d >> i & 1) ++cnt[b][i], b = pa[b][i];
    if(a == b) {
        ++cnt[a][0];
        return;
    }
    for(int i = 19; i >= 0; i--) if(pa[a][i] != pa[b][i]) {
        ++cnt[a][i];
        ++cnt[b][i];
        a = pa[a][i];
        b = pa[b][i];
    }
    ++cnt[a][0];
    ++cnt[b][0];
    ++cnt[pa[a][0]][0];
}
signed main() {
#ifndef local
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].pb(b), g[b].pb(a);
    }
    dfs(0);
    for(int L = 1; L < 20; L++) for(int i = 0; i < n; i++) pa[i][L] = pa[pa[i][L-1]][L-1];
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        modify(a, b);
    }
    for(int L = 19; L >= 1; L--) {
        for(int i = 0; i < n; i++) {
            cnt[i][L-1] += cnt[i][L];
            cnt[pa[i][L-1]][L-1] += cnt[i][L];
        }
    }
    int mx = 0;
    for(int i = 0; i < n; i++) mx = max(mx, cnt[i][0]);
    cout << mx << '\n';
}
