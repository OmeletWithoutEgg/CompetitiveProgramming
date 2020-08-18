#include "lib2078.h"
#include <cinttypes>
#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define ff first
#define ss second

using namespace std;
typedef __int128 ll;
typedef pair<ll,ll> pll;

inline ll modpow(ll e,ll p,ll m) {
    ll r = 1;
    for(e%=m; p; p>>=1) (p&1)&&(r=r*e%m), e=e*e%m;
    return r;
}
pll extgcd(ll a,ll b, ll m) {
    if(!b) return pll(1,0);
    pll V = extgcd(b,a%b,m);
    return pll(V.ss, (V.ff + m - (a/b)*V.ss%m)%m);
}
inline ll invmod(ll x,ll m) {
    // xx^-1 + am = 1;
    ll res = extgcd(x%m,m,m).ff%m;
    return res<0 ? res+m : res;
}
inline ll getPhi(ll n,ll k) {
    ll s = 1;
    while(s*s <= n) s *= 2;
    while(PhiOracle(s) == s%k) s *= 2;
    ll x = s;
    while(s/=2) if(PhiOracle(x-s) != (x-s)%k) x-=s;
    return x;
}
inline ll findFactor(ll n,ll k) {
    //for(int i = 2; i <= 100; i++) if(n%i==0) return i;
    if(n%2 == 0) return 2;
    ll S = ((n+1) - getPhi(n,k))/2;
    return (S*S>=n ? S - round(sqrt(1.0*S*S-n)) : round(sqrt(1.0*n)));
}
uint64_t decrypt( uint64_t e, uint64_t n, uint64_t c, uint64_t k ) {
    if(e == 1) return c;
    ll x = findFactor(n,k), y = n/x;
    if(x == y) {
        // p = ax+b, p^e = e*ab^{e-1}x + b^e(mod x^2)
        ll dx = invmod(e,x-1);
        ll b = modpow(c,dx,x);
        ll a = ((c*invmod(modpow(b,e-1,n),n)+n-b)%n*invmod(e,n)%n)/x;
        ll p = a*x + b;
        return p;
    }else {
        ll px = modpow(c,invmod(e,x-1),x); // p%x
        ll py = modpow(c,invmod(e,y-1),y); // p%y
        ll p = (x*invmod(x,y)%n * py + y*invmod(y,x)%n * px)%n;
        return p;
    }
}

