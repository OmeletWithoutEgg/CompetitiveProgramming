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
const ll INF = 1e18, MOD = 1000000007;

constexpr ll N = 500000;
ll n,m,pHundre = 1;
ll a[N+1] = {}, p[4][N+1] = {};
ll dp[N+1] = {};
//vector<ll> selection[16] = {};
ll pnt[4] = {}, cur[4] = {};
inline ll dot(ll x[],ll y[]){ll res=0;REP(b,0,m)res+=x[b]*y[b];return res;}
inline int selects(int s,int i){
    //return selection[s][i];
    int res = 1;
    REP(b,0,m) res *= (((s>>b)&1) ? (100-p[b][i]) : 100);
    return pHundre - res;
}
inline void check(){
    ll penalty[16] = {};
    REP(s,1,1<<m)REP(b,0,m)if((s>>b)&1)penalty[s]+=pnt[b];
    REP(b,0,m)cur[b]=0;
    dp[0] = 0;
    REP(i,1,n+1){
        dp[i]=dp[i-1];
        ll opt = 0;
        REP(s,1,1<<m){
            ll sel = selects(s,i-1) - penalty[s];
            if(dp[i] < dp[i-1]+sel)dp[i]=dp[i-1]+sel,opt=s;
        }
        REP(b,0,m)if((opt>>b)&1)++cur[b];
        debug(dp[i]);
    }
}
inline void bsrch(ll k = 0){
    ll l = 0, r = pHundre;
    while(l+1 < r){
        pnt[k] = mid;
        if(k == m-1)check();
        else bsrch(k+1);

        if(cur[k] == a[k]) return;
        if(cur[k]>a[k])l = mid;
        else if(cur[k]<a[k])r = mid;
    }
    pnt[k] = r;
}
signed main(){
    cin >> n >> m;
    REP(i,0,m)cin >> a[i], pHundre*=100;
    REP(i,0,m)REP(j,0,n)cin >> p[i][j];
    /*REP(s,1,1<<m){
        selection[s].resize(n);
        REP(i,0,n){
            ll res = 1;
            REP(b,0,m) res *= ((s>>b)&1) ? (100-p[b][i]) : 100;
            selection[s][i] = pHundre - res;
        }
    }*/
    REP(s,1,1<<m)REP(i,0,n)debug(selects(s,i));
    bsrch();
    check();
    cout << dp[n]+dot(pnt,a) << '\n';
}
