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
    // (-1, 0) and (1, 0) be the closest
    vector<pair<int,int>> v;
    v.emplace_back(-49, 0);
    v.emplace_back(49, 0);

    const int K = 201;
    const int C = 45000 / K;
    for (int i = -C; i <= C; i++)
        for (int j = 1; j <= K; j++)
            v.emplace_back(i*(100 + j), 100 * j);
    for (int i = -C; i <= C; i++)
        for (int j = 1; j <= K; j++)
            v.emplace_back(i*(100 + j), -100 * j);
    // (x, y) 

    cout << v.size() << '\n';
    for (auto [x, y]: v)
        cout << x << ' ' << y << '\n';
}
