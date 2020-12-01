#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int V,E;
struct {
    int par[10010],rk[10010];
    void init(){memset(rk,0,sizeof rk),iota(par,par+V+1,0);}
    int anc(int x){return x==par[x]?x:(par[x]=anc(par[x]));}
    bool join(int x,int y){
        if((x=anc(x)) == (y=anc(y))) return false;
        if(rk[x] < rk[y]) swap(x,y);
        return par[y] = x, rk[x]==rk[y]&&++rk[x], true;
    }
} dsu;
struct Edge{
    int u,v;
    ll w;
    bool operator<(Edge &b) const {return w<b.w;}
} edges[1000010];
signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    while(cin >> V >> E, V&&E){
        dsu.init();
        for(int i = 0;i < E;i++) cin >> edges[i].u >> edges[i].v >> edges[i].w;
        sort(edges,edges+E);
        int mstSz = 1;
        ll mstWt = 0;
        for(int i = 0;i < E;i++) if(dsu.join(edges[i].u,edges[i].v))
            ++mstSz, mstWt += edges[i].w;
        if(mstSz != V) cout << -1 << '\n';
        else cout << mstWt << '\n';
    }
}
