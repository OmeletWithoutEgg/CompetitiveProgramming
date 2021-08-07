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
    int n = 4;
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << rand() << (j+1==n ? '\n' : ' ');
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cout << rand() << (j+1==n ? '\n' : ' ');
}
