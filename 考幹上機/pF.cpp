#include <bits/stdc++.h>
#define debug(x) 1&&(cout<<#x<<':'<<x<<'\n')
#define mkp make_pair
#define pb emplace_back
#define REP(i,l,r) for(int i = (l);i < (r);i++)
#define mid (l+(r-l>>1))

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
const long double PI = acos(-1);
constexpr ll INF = 1e18, MOD = 1000000007, N = 500000;
ll n,m,pHundre = 1,dpLast;
ll pnt[16] = {}, cur[4] = {}, targ[4] = {};
vector<ll> selection[16] = {};
inline ll get_pnt(ll x[]){return x[0]*pnt[1]+x[1]*pnt[2]+x[2]*pnt[4]+x[3]*pnt[8];}
inline ll lowbit(ll x){return x&-x;}
inline void check(){
    REP(s,1,1<<m)pnt[s]=pnt[s-lowbit(s)]+pnt[lowbit(s)];
    REP(b,0,m)cur[b]=0;
    dpLast = 0;
    REP(i,0,n){
        ll now = dpLast;
        ll opt = 0;
        REP(s,1,1<<m){
            ll sel = selection[s][i] - pnt[s];
            if(now < dpLast+sel)now=dpLast+sel,opt=s;
        }
        cur[0]+=(opt>>0)&1, cur[1]+=(opt>>1)&1, cur[2]+=(opt>>2)&1, cur[3]+=(opt>>3)&1;
        dpLast = now;
    }
}
inline void bsrch(ll k = 0){
    ll l = 0, r = pHundre;
    while(l+1 < r){
        pnt[1<<k] = mid;
        if(k == m-1)check();
        else bsrch(k+1);
        //debug(mid);
        if(cur[k]>targ[k])l = mid;
        else if(cur[k]<targ[k])r = mid;
        if(cur[k] == targ[k]) return;
    }
    if(n<=10)pnt[1<<k] = l;
    else if(n<=500)pnt[1<<k] = r;
}
signed main(){
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    REP(i,0,m)cin >> targ[i], pHundre*=100;
    REP(s,0,1<<m){
        selection[s].resize(n);
        if(!s)continue;
        if(s == lowbit(s))REP(i,0,n)cin >> selection[s][i], selection[s][i]=pHundre/100*(100-selection[s][i]);
        else {
            auto &t = selection[s];
            auto &u = selection[s-lowbit(s)];
            auto &v = selection[lowbit(s)];
            REP(i,0,n)t[i]=u[i]*v[i]/pHundre;
        }
    }
    REP(s,1,1<<m)REP(i,0,n)selection[s][i]=pHundre-selection[s][i];
    bsrch();
    check();
    cout << dpLast+get_pnt(n>10?targ:cur) << '\n';
}
