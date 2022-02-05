#include "aliens.h"
#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
#define pary(x...) danb(#x, x)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\e[1;32m(" << s << ") = ("), ..., (std::cerr << a << (--cnt ? ", " : ")\e[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\e[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\e[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
const ll INF = 1e18;
ll sq(ll x) { return x * x; }
void chmin(ll &x, ll v) {
    if (x > v)
        x = v;
}
long long take_photos(int n, int m, int k, std::vector<int> row, std::vector<int> col) {
    vector<int> s = row;
    sort(all(s));
    s.erase(unique(all(s)), s.end());
    n = s.size();
    vector<vector<ll>> dp(n+1, vector<ll>(k+1, INF));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j <= n; j++) {
            for (int c = 0; c < k; c++) {
                chmin(dp[j][c+1], dp[i][c] + sq(s[j-1] - s[i] + 1));
            }
        }
    }
    return *min_element(all(dp[n]));
}
