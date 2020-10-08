
#include <bits/stdc++.h>
#define pb emplace_back
#define debug(x...) qqbx(#x, x)
template <typename ...T> void qqbx(const char *s, T ...args) {
    std::cerr << "(" << s << ") = (";
    int cnt = sizeof...(T);
    ( (std::cerr << args << (--cnt ? ", " : ")\n"), 0), ..., void() );
}

using namespace std;
using ll = long long;
using ld = long double;
const int N = 200025, MOD = 1000000007;

ll n, k;
ll ans[N];
ll need(ll x) {
    // test how many (i, j) such that gcd(i,j) = 1 and j <= i * x / n*n;
    for(int i = 1; i <= n; i++) ans[i] = 0;
    for(int g = 1; g <= n; g++) {
        for(int i = 1; i*g <= n; i++) {
            ans[g] += i * x / (n*n);
        }
    }
    for(int i = n; i >= 1; i--) {
        for(int j = i * 2; j <= n; j += i) {
            ans[i] -= ans[j];
        }
    }
    return ans[1];
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> k;
    ll ans = 0;
    for(ll s = 1LL << 40; s; s>>=1) if(need(ans+s) < k) ans += s;
    pair<ll,ll> best = {n, n};
    auto better = [](pair<ll,ll> a, pair<ll,ll> b) -> bool {
        return a.first * b.second < b.first * a.second;
    };
    for(int i = 1; i <= n; i++) {
        int j = ceil(i * ans / ld(n*n));
        pair<ll,ll> now = {j, i};
        if(__gcd(i, j) == 1 && better(now, best)) best = now;
    }
    cout << best.first << ' ' << best.second << '\n';
}
