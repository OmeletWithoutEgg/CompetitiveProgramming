#pragma gcc Optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
#define debug(x) 1&&(cout<<#x<<':'<<x<<'\n')

using namespace std;
typedef long long ll;
const ll N = 1000;

struct Edge{
    ll u,v,w;
    Edge(ll u,ll v,ll w):u(u),v(v),w(w){}
    friend bool operator<(Edge &a,Edge &b){return a.w<b.w;}
};
struct {
    int par[N+1], rk[N+1];
    void init(int n){memset(rk,0,sizeof rk), iota(par,par+n,0);}
    int anc(int x){return (x==par[x]) ? x : (par[x]=anc(par[x]));}
    bool same(int x,int y){return anc(x) == anc(y);}
    void join(int x,int y){
        if((x=anc(x)) == (y=anc(y))) return;
        if(rk[x] < rk[y]) swap(x,y);
        par[y] = x, rk[x]==rk[y]&&++rk[x];
    }
} dsu;
ll pa[N+1][25] = {};
ll pa_d[N+1][25] = {};
vector<Edge> edges,p,q;
vector<int> g[N+1] = {};
ll d, dep[N+1] = {};
void dfs(int u = 1, int fa = 0,ll w = 0){
    pa[u][0] = fa, pa_d[u][0] = w, dep[u] = d;
    for(auto id:g[u]){
        int v = p[id].u^p[id].v^u;
        if(v != fa) ++d, dfs(v,u,p[id].w), --d;
    }
}
void LCA_init(int n){
    for(int L = 1;L < 25;L++)
        for(int i = 1;i <= n;i++){
            pa[i][L] = pa[pa[i][L-1]][L-1];
            pa_d[i][L] = max(pa_d[i][L-1], pa_d[pa[i][L-1]][L-1]);
        }
}
ll query(ll x,ll y){
    ll res = 0;
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) swap(x,y);
        ll dif = dep[x]-dep[y];
        for(int L = 0;L < 25;L++) if((dif>>L)&1){
            res = max(res,pa_d[x][L]);
            x = pa[x][L];
        }
        assert(dep[x] == dep[y]);
    }
    if(x == y) return res;
    for(int L = 24;L > 0;L--) if(pa[x][L]!=pa[y][L])
        res = max({res,pa_d[x][L],pa_d[y][L]}),
        x = pa[x][L], y = pa[y][L];
    if(x != y)
        //assert(pa[x][0] == pa[y][0]),
        res = max({res,pa_d[x][0],pa_d[y][0]});
    return res;
}
signed main(){
    ll V,E;
    scanf("%lld%lld",&V,&E);
    rep(_,E){
        ll u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w);
        edges.emplace_back(u,v,w);
    }

    ll mst = 0,smst = 1e18;
    sort(edges.begin(),edges.end());
    dsu.init(V);
    for(auto &e:edges){
        if(!dsu.same(e.u,e.v)){
            dsu.join(e.u,e.v);
            mst += e.w;
            g[e.u].emplace_back(p.size());
            g[e.v].emplace_back(p.size());
            p.emplace_back(e);
        }else q.emplace_back(e);
    }
    if(p.size() != V-1) return puts("-1 -1"),0;
    if(q.size() == 0) return printf("%lld -1\n",mst),0;
    dfs();
    LCA_init(V);
    smst = 1e18;
    for(auto &e:q){
        ll dif = e.w - query(e.u,e.v);
        //assert(dif >= 0);
        if(smst > mst+dif) smst = mst+dif;
    }
    printf("%lld %lld\n",mst,smst);

}

