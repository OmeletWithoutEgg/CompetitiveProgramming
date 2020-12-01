#pragma GCC optimize ("Ofast")
#pragma loop_opt(on)
#pragma code
#include <bits/stdc++.h>
#define INF 1e9
#define REP(i,l,r) for(int i = l;i < r;i++)
#define ff first
#define ss second

using namespace std;

struct query{
    int from,to,idx,grd;
    query(int g = 0,int f = 0,int t = 0,int i = 0):grd(g),from(f),to(t),idx(i){}
    bool operator<(query &b){return grd < b.grd;}
} qs[200000] = {};
int guard[500] = {};
int ans[200000] = {};
int g[500][500] = {};
int v,e,q;
int f,t,w;

int dis[500][500] = {};
int dijkstra(int f,int t){
    if(dis[f][t])return dis[f][t];
    else REP(i,0,v) dis[i][f] = dis[f][i] = -1;
    priority_queue<pair<int,int> > pq;
    pq.push({0,f}); dis[f][f] = 0;
    while(!pq.empty()){
        pair<int,int> cur = pq.top(); pq.pop();
        for(int i = 0;i < v;i++)
            if(g[cur.ss][i] && (dis[f][i] == -1 || dis[f][i] > cur.ff+g[cur.ss][i]))
                pq.push({dis[f][i] = dis[i][f] = cur.ff+g[cur.ss][i], i});
    }
    return dis[f][t];
}
main(){
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> v >> e >> q;
    REP(i,0,v) cin >> guard[i];
    REP(i,0,e){
        cin >> f >> t >> w; f--,t--;
        if(g[f][t] > w || g[f][t] == 0)g[f][t] = w;
        if(g[t][f] > w || g[t][f] == 0)g[t][f] = w;
    }
    REP(i,0,q){
        cin >> w >> f >> t; f--,t--;
        qs[i] = query(w,f,t,i);
    }
    sort(qs,qs+q);
    REP(i,0,q){
        if(i>0 && qs[i-1].grd < qs[i].grd)REP(j,0,v) if(guard[j] < qs[i].grd) REP(k,0,v)
            g[j][k] = g[k][j] = dis[j][k] = dis[k][j] = 0;
        ans[qs[i].idx] = dijkstra(qs[i].from,qs[i].to);
    }
    REP(i,0,q) cout << ans[i] << '\n';
    return 0;
}
