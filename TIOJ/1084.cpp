#include <bits/stdc++.h>
#define REP(i,l,r) for(int i=(l);i<(r);++i)
#define pb emplace_back
#define ff first
#define ss second
#define all(v) begin(v),end(v)
#define SZ(v) (int(v.size()))
#define N 500
#define M 1024

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

map<int,vector<pll> > g = {};
bitset<M+1> eVis;
vector<ll> ans;
int e,x,y;
void dfs(int cur){
    for(auto e:g[cur])if(!eVis[e.ss]){
        eVis[e.ss] = true;
        dfs(e.ff);
    }
    ans.pb(cur);
}
signed main(){
    while(cin >> e,e){
        g.clear(), eVis.reset(), ans.clear();
        REP(i,0,e) cin >> x >> y, g[x].pb(y,i),g[y].pb(x,i);
        for(auto &p:g)sort(all(p.ss));
        int odd = 0;
        for(auto p:g)if(p.ss.size()&1){dfs(p.ff),odd=1;break;}
        if(!odd)dfs(g.begin()->ff);
        reverse(all(ans));
        for(auto x:ans)cout << x << '\n';
        cout << '\n';
    }
}
