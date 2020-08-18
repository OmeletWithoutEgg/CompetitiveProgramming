#include <bits/stdc++.h>
#define pb emplace_back
#define debug(x) cerr<<#x<<" = "<<x<<'\n'
#define int ll
using namespace std;
typedef long long ll;
const int MOD = 1000000007;

void fail() {
    cout << -1 << '\n';
    exit(0);
}
int fp(ll x, ll a, ll b, ll n) {
    while(n) {
        if(n&1) x = (a*x+b)%MOD;
        //a(ax+b)+b
        b = b*(a+1)%MOD;
        a = a*a%MOD;
        n >>= 1;
    }
    return x;
}
int solve(vector<ll> v) {
    //for(ll x: v) cout << x << ' '; cout << '\n';
    for(ll x: v) if(x <= 0) fail();
    if(v.size() == 2) {
        if(v[0] == 1 && v[1] == 1) return 0;
        if(v[0] == 0 || v[1] == 0) fail();
        if(v[1] == 1)
          return fp(0, 2, 2, v[0]-1);
        if(v[0] == 1)
          return fp(0, 2, 1, v[1]-1);
              /*if(v[0] > v[1])
            return (solve({v[0]-v[1], v[1]}) * 2 + 2) % MOD;
        else
            return (solve({v[0], v[1]-v[0]}) * 2 + 1) % MOD;*/
        if(v[0] > v[1])
            return fp(solve({v[0]%v[1], v[1]}), 2, 2, v[0]/v[1]);
        else
            return fp(solve({v[0], v[1]%v[0]}), 2, 1, v[1]/v[0]);
    }
    vector<ll> u;
    if (v[0] > v[1]) {
        if(v.size() == 3) {
            ll k = v[1] == 1 ? v[0]-1 : v[0] / v[1];
            return fp(solve({v[0]-k*v[1], v[1], v[2]-k*v[1]}), 2, 2, k);
        }
        u.pb(v[0]-v[1]);
        for(int i = 1; i < v.size(); i+=2) u.pb(v[i]);
        if(v.size() % 2 == 1) u.pb(v.back() - u.back());
        for(int i = 2; i+1 < v.size(); i+=2) if(v[i-1]+v[i+1] != v[i]) fail();
        return (solve(u) * 2 + 2) % MOD;
    } else if(v[0] < v[1]) {
        for(int i = 0; i < v.size(); i+=2) u.pb(v[i]);
        if(v.size() % 2 == 0) u.pb(v.back() - u.back());
        for(int i = 1; i+1 < v.size(); i+=2) if(v[i-1]+v[i+1] != v[i]) fail();
        return (solve(u) * 2 + 1) % MOD;
    } else {
        if(v[0]!=1 || v[1]!=1) fail();
        for(int i = 2; i < v.size(); i++) {
            ll x = v[i>>1] + (~i&1) * (v[i-1>>1]);
            if(v[i] != x) fail();
        }
        return 0;
    }
}
signed main () {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<ll> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    cout << solve(v) << '\n';
}
/*
3
100000000 1 100000000

3
1 1 2
*/
