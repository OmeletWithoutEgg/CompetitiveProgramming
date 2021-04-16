#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define pb emplace_back

using namespace std;
const int maxn = 100025, mod = 998244353, inf = 1e9, maxc = 100025;
const int64_t INF = 1e18;

signed main() {
    freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n = 100000;
    int q = 200000;
    const int k = 0;
    cout << n << '\n';
    int slope = n / 2;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cout << i + k << ' ' << sum << '\n';
        sum += slope;
        slope -= 1;
    }
    cout << q << '\n';
    const int inf = 5000;
    mt19937 rng;
    for (int i = 0; i < q; i++) {
        cout << rng() % 400 + k << ' ' << n - rng() % 400 << ' ' << rand() % inf - inf/2 << '\n';
    }
}
