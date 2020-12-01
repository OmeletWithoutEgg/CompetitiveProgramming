#include <bits/stdc++.h>
#define debug(x) 0&&(cout<<#x<<':'<<x<<'\n')
#include "lib1164.h"
#define ff first
#define ss second
#define N 1000000
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
constexpr ll INF = 1e18;

vector<pll> g[N+1] = {};
ll len[N+1] = {};
int diameter(MAP mp){
    int v = mp.m, e = mp.k;
    //g.resize(v);
    for(int i = 0;i < v;i++)g[i].clear();
    debug(v),debug(e);
    for(int i = 0;i < e;i++){
        int x = mp.x[i], y = mp.y[i], w = mp.len[i];// --x, --y;
        debug(x),debug(y),debug(w);
        g[x].push_back(pll(w,y)), g[y].push_back(pll(w,x));
    }
    int furthest = 0;
    stack<pll> pq,qp;
    pq.push(pll(0,0));
    fill(len,len+v,INF);
    len[0] = 0;
    while(!pq.empty()){
        pll cur = pq.top() ; pq.pop();
        for(auto p:g[cur.ss])if(cur.ff+p.ff<len[p.ss])
            pq.push(pll(len[p.ss]=cur.ff+p.ff,p.ss));
    }
    furthest=max_element(len,len+v)-len;
    qp.push(pll(0,furthest));
    fill(len,len+v,INF);
    len[furthest] = 0;
    while(!qp.empty()){
        pll cur = qp.top() ; qp.pop();
        for(auto p:g[cur.ss])if(cur.ff+p.ff<len[p.ss])
            qp.push(pll(len[p.ss]=cur.ff+p.ff,p.ss));
    }
    return *max_element(len,len+v);
}
int v[N+1] = {};
signed main(){
    int n = init();
    iota(v,v+n,0);
    auto p = minmax_element(v,v+n,query);
    MAP MX = getct(*p.ff), MI = getct(*p.ss);
    //cout << diameter(MX) << '\n';
    //cout << diameter(MI) << '\n';
    answer(diameter(MX),diameter(MI));
}
