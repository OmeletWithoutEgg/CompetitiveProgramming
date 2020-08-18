#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll N = 300255;

ll V,E,K,L,R;
struct Edge{
    ll w, u, v;
} edges[N];
ll par[N], rk[N], CC;
void init(){CC = V, iota(par,par+V+1,0),memset(rk,0,sizeof rk);}
ll anc(ll x){return x==par[x]?x:(par[x]=anc(par[x]));}
bool join(ll x,ll y){
    if((x=anc(x)) == (y=anc(y))) return false;
    if(rk[x] < rk[y]) swap(x, y);
    return --CC, par[y] = x, rk[x]!=rk[y]||++rk[x];
}
signed main(){
    cin >> V >> E >> K;
    for(int i = 0; i < E; i++) cin >> edges[i].u >> edges[i].v >> edges[i].w;
    sort(edges, edges+E, [](Edge &a, Edge &b){return a.w<b.w;});
    init();
    for(int i = 0; i < E; i++) if(join(edges[i].u,edges[i].v)) L += edges[i].w;
    if(CC != 1) return cout << "NIE\n", 0;
    init();
    for(int i = E-1; i >= 0; i--) if(join(edges[i].u, edges[i].v)) R += edges[i].w;
    if(L <= K && K <= R) cout << "TAK\n";
    else cout << "NIE\n";
}
