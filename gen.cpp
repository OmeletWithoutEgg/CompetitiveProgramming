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
    ios_base::sync_with_stdio(0), cin.tie(0);
    int T = 10;
    cout << T << '\n';
    int n = 2000;
    for (int i = 0; i < T; i++) {
        cout << n << '\n';
        for (int i = 0; i < n; i++)
            cout << 1 << (i+1==n ? '\n' : ' ');
    }
}
