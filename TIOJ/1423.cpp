#include <bits/stdc++.h>
#define debug(x) cout << #x << ':' << x << '\n'

using namespace std;
typedef long long ll;

struct vec{
    ll x,y;
    vec(ll x = 0,ll y = 0):x(x),y(y){}
    bool operator<(vec b){return x!=b.x?x<b.x:y<b.y;}
    vec operator-(vec b){return vec(x-b.x,y-b.y);}
    static ll wedge(vec a,vec b){return a.x*b.y-a.y*b.x;}
};

signed main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int v;
    cin >> v;
    vector<vec> g(v);
    for(int i = 0;i < v;i++)cin >> g[i].x >> g[i].y;
    ll res = 0;
    for(int i = 0;i < v;i++)
        for(int j = i+1;j < v;j++){
            ll l = 0,r = 0;
            vec d = g[j]-g[i];
            for(int k = 0;k < v;k++)if(k!=i&&k!=j){
                ll w = vec::wedge(g[k]-g[i],d);
                //debug(w);
                if(w>0)l++;
                else if(w<0)r++;
            }
            res += l*r;
        }
    cout << res << '\n';
}
