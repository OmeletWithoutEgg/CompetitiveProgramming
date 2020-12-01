#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
const int N = 225;

const int dx[4] = {1,0,-1,0};
const int dy[4] = {0,1,0,-1};
int n,v[N*N],mi[N*N],tot,id[N][N];
vector<int> g[N*N];
int dijkstra(int s, int t, int lim) {
    if(v[s] > lim) return -1e9;
    for(int i = 1; i <= tot; i++) mi[i] = -1e9;
    priority_queue<pair<int,int>> pq; // dis, id
    pq.push({mi[s] = v[s], s});
    while(!pq.empty()) {
        pair<int,int> cur = pq.top(); pq.pop();
        int i = cur.second, d = cur.first;
        if(mi[i] != d) continue;
        for(int j:g[i]) if(v[j] <= lim) {
            if(mi[j] < min(d,v[j]))
                pq.push({mi[j] = min(d,v[j]), j});
        }
    }
    return mi[t];
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) id[i][j] = ++tot;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) for(int k = 0; k < 4; k++) {
        int x = i+dx[k], y = j+dy[k];
        if(x < 1 || x > n || y < 1 || y > n) continue;
        g[id[i][j]].pb(id[x][y]);
    }
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin >> v[id[i][j]];
    int ans = 2e9;
    for(int mx = 0; mx <= 400; mx++) ans = min(ans, mx - dijkstra(id[1][1],id[n][n],mx)); // dijkstra: max(min)
    cout << ans << '\n';
}
