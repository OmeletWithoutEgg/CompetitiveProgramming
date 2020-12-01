#include <bits/stdc++.h>
#define ff first
#define ss second

using namespace std;
typedef int64_t ll;
typedef pair<ll,ll> pll;

pll extgcd(ll a,ll b) {
    if(!b) return {1,0};
    pll tmp = extgcd(b,a%b);
    return {tmp.ss, tmp.ff - (a/b)*tmp.ss};
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int q,m,x;
    cin >> m >> q;
    while(q--) {
        cin >> x;
        x%=m;
        if(x == 0 || gcd(x,m) != 1) cout << "jizz\n";
        else cout << (extgcd(x,m).ff%m+m)%m << '\n';
    }
}
