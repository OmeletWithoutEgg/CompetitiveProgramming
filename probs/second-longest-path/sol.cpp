#include <bits/stdc++.h>
#define pb emplace_back
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
const int N = 100025, INF = 1e18;

ll n;
vector<pll> g[N];
array<ll,2> ans, dis[N];
void ins(array<ll,2> &v, ll x) {
    if(x > v[0])
        v[1] = v[0], v[0] = x;
    else if(x < v[0] && x > v[1])
        v[1] = x;
}
void dfs(int u, int p = 0) {
    dis[u] = {0, -INF};
    for(auto [w, v]: g[u]) {
        if(v == p) continue;
        dfs(v, u);
        for(int a=0;a<2;a++) for(int b=0;b<2;b++)
            ins(ans, dis[u][a]+w+dis[v][b]);
        for(int a=0;a<2;a++)
            ins(dis[u], dis[v][a]+w);
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb(c,b), g[b].pb(c,a);
    }
    ans = {-INF, -INF};
    dfs(1);
    cout << ans[1] << '\n';
}

