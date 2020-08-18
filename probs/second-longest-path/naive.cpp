#include <bits/stdc++.h>
#define pb emplace_back
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
const int N = 100025;

ll n;
vector<pll> g[N];
vector<ll> dd;
ll dis[N];
void dfs(int i, int p = 0, ll d = 0) {
    dis[i] = dis[p] + d;
    for(auto [w, j]: g[i]) if(j != p) dfs(j,i,w);
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb(c,b), g[b].pb(c,a);
    }
    for(int i = 1; i <= n; i++) {
        dfs(i);
        for(int j = 1; j < i; j++) dd.pb(dis[j]);
    }
    sort(dd.begin(), dd.end());
    dd.erase(unique(dd.begin(), dd.end()), dd.end());
    cout << dd[dd.size()-2] << '\n';
}

