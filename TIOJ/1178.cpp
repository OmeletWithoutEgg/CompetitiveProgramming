#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct vec{
    ll x,y;
    vec(ll x = 0,ll y = 0):x(x),y(y){}
    bool operator<(vec b){return x!=b.x?x<b.x:y<b.y;}
    vec operator-(vec b){return vec(x-b.x,y-b.y);}
    static ll wedge(vec a,vec b){return a.x*b.y-a.y*b.x;}
    static int checkConv(vec a,vec b,vec c){
        ll w = wedge(c-a,b-a);
        return (w>0)-(w<0);
    }
};

signed main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int v;
    cin >> v;
    if(v < 3) return cout << v << '\n',0;
    vector<vec> g(v);
    for(int i = 0;i < v;i++) cin >> g[i].x >> g[i].y;
    sort(g.begin(), g.end());
    //for(auto p:g)cout << p.x << ' ' << p.y << '\n';
    vec lh[100000] = {};
    vec uh[100000] = {};
    int lsz = 0, usz = 0;
    for(auto p:g){
        while(lsz >= 2 && vec::checkConv(lh[lsz-2],lh[lsz-1],p) >= 0)--lsz;
        while(usz >= 2 && vec::checkConv(uh[usz-2],uh[usz-1],p) <= 0)--usz;
        lh[lsz++] = uh[usz++] = p;
    }
    cout << lsz + usz - 2 << '\n';
}
