#include <bits/stdc++.h>

using namespace std;
typedef int ll;
const ll MOD = 11;

ll t,n;
ll frac[MOD]={1};
ll inv(ll x){
    ll r = x;
    x=x*x, x=x*x, x=x*x;
    return r*x%MOD;
}
inline ll C(ll n, ll m){
    //cout << "n = " << n << ", m = " << m << '\n';
    if(n-m < 0) return 0;
    return frac[n]*inv(frac[n-m]*frac[m]%MOD)%MOD;
}
ll Lucas(ll n, ll m){
    ll res = 1;
    while(m) {
        res = res*C(n%MOD,m%MOD)%MOD;
        n/=MOD, m/=MOD;
    }
    return res;
}
signed main(){
    for(int i = 1; i < MOD; i++) frac[i] = frac[i-1]*i%MOD;
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n,  n>>=1;
        cout << (Lucas(n*2,n)-Lucas(n*2,n+1)+MOD)%MOD << '\n';
    }
}
