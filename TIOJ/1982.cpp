#include <cstdio>
#include <utility>
#define ff first
#define ss second
typedef __int128 ll;
typedef std::pair<ll,ll> pll;

pll v[6];
ll abs(ll x){return x<0?-x:x;}
ll rdiv(ll x, ll L) {
    ll y = cdiv(x, L), z = y-1;
    return (abs(L-x*y) > abs(L-x*z)) ? z : y;
}
pll calc(pll a, pll b) {
    ll L = b.ff*b.ff+b.ss*b.ss;
    pll q{a.ff*b.ff+a.ss*b.ss, a.ss*b.ff-a.ff*b.ss};
    q.ff = rdiv(q.ff, L), q.ss = rdiv(q.ss, L);
    // debug(res.ff), debug(res.ss);
    // if(res!=a && res!=b)
    return {a.ff-b.ff*q.ff+b.ss*q.ss, a.ss-b.ff*q.ss-b.ss*q.ff};
    // return {a.ff-b.ff, a.ss-b.ss};
}
pll gcd(pll a, pll b) {
    while(b.ff || b.ss) {
        pll t = calc(a,b);
        a = b;
        b = t;
        // cout << a.ff << ' ' << a.ss << '\n';
        // cout << b.ff << ' ' << b.ss << '\n';
    }
    // 19, -i; 19, 8i
    return a;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    for(int i = 0; i < 6; i++) {
        long long x, y;
        cin >> x >> y;
        v[i] = {x,y};
    }
    pll g{0, 0};
    for(int i = 1; i < 6; i++) g = gcd(g, v[i]);
    // cout << g.ff << ' ' << g.ss << '\n';
    cout << long long(abs(g.ff)+abs(g.ss));
}

