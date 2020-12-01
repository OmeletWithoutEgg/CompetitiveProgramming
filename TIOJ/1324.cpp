#include <bits/stdc++.h>
#define debug(x) 1&&(cout<<#x<<':'<<x<<'\n')
#define REP(i,l,r) for(int i=(l);i<(r);i++)
#define ff first
#define ss second
#define pb emplace_back

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
const ll N = 1000000, M = 500000;

ll n,k,x[M+1];
pll re[M+1] = {};
ll eq(ll x,pll r){return x<r.ss?x:(x-r.ff)%(r.ss-r.ff)+r.ff;}
int appear[N+1] = {};
pll rec(ll e,pll r){
    memset(appear,-1,sizeof appear);
    e = eq(e,r);
    ll x = e;
    REP(i,0,r.ss){
        if(appear[x] != -1){
            return pll(appear[x],i);
        }else appear[x] = i;
        x = eq(x*e,r);
    }
    assert(1);
}
ll modpow(ll e,ll p,pll r){
    ll res = 1;
    e = eq(e,r);
    while(p){
        if(p&1)res = eq(res*e,r);
        e = eq(e*e,r), p>>=1;
    }
    return res;
}
signed main(){
    while(cin >> n){
        REP(i,0,n) cin >> x[i];
        cin >> k;
        re[0] = pll(0,k);
        REP(i,0,n-1)x[i] = eq(x[i],re[i]), re[i+1] = rec(x[i],re[i]);
        x[n] = 1;
        for(int i = n-1;i >= 0;i--)
            x[i] = modpow(x[i],x[i+1],re[i]);
        cout << x[0] << '\n';
    }
}
