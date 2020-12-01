#include <bits/stdc++.h>

using namespace std;
using ll = long long;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    ll n, L, R;
    cin >> n >> L >> R;
    --L, --R;
    vector<ll> pre(R-L+1);
    auto add = [&](ll d, ll l, ll r) {
        if(d*l < L) {
            ll nl = (L + d-1) / d;
            pre[0] += (nl - l);
            l = nl;
        }
        for(ll i = l; i <= r && i*d <= R; i++) pre[i*d-L] += 1;
    };
    for(ll i = 1, j; i <= n; i = j) {
        j = n/(n/i) + 1;
        add(n/i, i, j);
    }
    for(int i = 1; i < R-L+1; i++) pre[i] += pre[i-1];
    cout << pre[0];
    for(int i = 1; i < int(pre.size()); i++) cout << ' ' << pre[i];
    cout << '\n';
}
