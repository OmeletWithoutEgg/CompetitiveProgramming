#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll N = 255, INF = 1LL<<32;

ll v,e,q,cnt,a,b,w;
ll cost[N], g[N][N], id[N], ans[N][N];
inline void upd(ll a,ll b,ll w){ if(g[a][b] > w) g[a][b] = w; }
inline void calc() {
    iota(id,id+v,1);
    sort(id,id+v,[](ll a,ll b){return cost[a]<cost[b];});
    for(ll t = 0; t < v; t++) {
        ll k = id[t];
        for(ll i = 1; i <= v; i++) if(g[i][k]!=INF) for(ll j = 1; j <= v; j++) if(g[k][j]!=INF) {
            upd(i,j,g[i][k]+g[k][j]);
            ans[i][j] = min(ans[i][j], g[i][j]+max({cost[i],cost[j],cost[k]}));
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    while(cin >> v >> e >> q, v||e||q) {
        for(ll i = 1; i <= v; i++) for(ll j = 1; j <= v; j++) g[i][j] = ans[i][j] = INF;
        for(ll i = 1; i <= v; i++) cin >> cost[i];
        for(ll i = 0; i < e; i++) {
            cin >> a >> b >> w;
            upd(a,b,w), upd(b,a,w);
        }
        calc();
        cout << "Case #" << ++cnt << '\n';
        for(ll i = 0; i < q; i++) {
            cin >> a >> b;
            cout << (ans[a][b] == INF ? -1 : ans[a][b]) << '\n';
        }
        cout << '\n';
    }
}
