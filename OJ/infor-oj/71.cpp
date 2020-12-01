#pragma gcc optimze("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define debug(x) 1&&(cout<<#x<<':'<<(x)<<'\n')
#define mkp make_pair
#define pb emplace_back
#define ff first
#define ss second
#define siz(v) (ll(v.size()))
#define all(v) begin(v),end(v)
#define rep(i,n) for(int i=0;i<(n);i++)
#define mid (l+(r-l>>1))

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
constexpr long double PI = acos(-1),eps = 1e-8;
constexpr ll N = 200100, INF = 1e18, MOD = 1000000007;

int V,E;
vector<int> g[N];
struct Edge{
    int u,v,x,y;
} edges[N];
double p = 1;
double mst(){ // y/x >= p -> y-xp >= 0
    ll A = 0, B = 0, id;
    struct cmp{bool operator()(int a,int b){return edges[a].y-edges[b].y>(edges[a].x-edges[b].x)*p;}};
    priority_queue<int,vector<int>,cmp> pq;
    bitset<N> inMst;
    for(auto id:g[0]) pq.push(id);
    inMst[0] = true;
    for(int i = 0; i < V-1 && pq.size(); i++){
        do id=pq.top(),pq.pop(); while(inMst[edges[id].u] && inMst[edges[id].v]);
        A += edges[id].x, B += edges[id].y;
        int cur = inMst[edges[id].u] ? edges[id].v : edges[id].u;
        inMst[cur] = true;
        for(auto nxt:g[cur]) pq.push(nxt);
    }
    p = double(B)/A;
}
signed main(){
    scanf("%d%d",&V,&E);
    rep(i,E){
        auto &e = edges[i];
        scanf("%d%d%d%d",&e.u,&e.v,&e.x,&e.y), --e.u, --e.v;
        g[e.u].pb(i),g[e.v].pb(i);
    }
    mst(),mst(),mst();
    printf("%.10f",p);
}
