#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
const int N = 1025;
const ll INF = 1e18;

signed main() {
#ifndef local
    freopen("landscape.in", "r", stdin);
    freopen("landscape.out", "w", stdout);
#endif // local
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    ll x, y, z;
    cin >> n >> x >> y >> z;
    if(n > 5000) return 3;
    vector<int> dif(n);
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        dif[i] = a - b;
    }
    vector<tuple<int,int,int>> E;
    for(int i = 0; i < n; i++) {
        int d = dif[i];
        if(d > 0) ans += y*d;
        else if(d < 0) ans += x*(-d);
        for(int j = i-1; j >= 0; j--) {
            if(z * (i-j) >= x + y) break;
            if((dif[i] ^ dif[j]) < 0) E.pb(z * (i-j) - x - y, i, j);
        }
        // earn: Z * |i - j| - (X + Y)
    }
    sort(all(E));
    for(auto e: E) {
        ll c;
        int i, j;
        tie(c, i, j) = e;
        int mn = min(abs(dif[i]), abs(dif[j]));
        ans += c * mn;
        if(dif[i] < 0 && dif[j] > 0) {
            dif[i] += mn;
            dif[j] -= mn;
        } else if(dif[i] > 0 && dif[j] < 0) {
            dif[i] -= mn;
            dif[j] += mn;
        }
    }
    cout << ans << '\n';
}
