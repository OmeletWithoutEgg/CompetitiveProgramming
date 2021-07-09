#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
#define pary(x...) danb(#x, x)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\e[1;32m(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\e[0m\n")));
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
const int maxn = 300025;
const int K = 200;
const int inf = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, D;
    cin >> n >> D;
    vector<int> A(n);
    for (int &x: A) cin >> x;
    int ans = 0;
    vector<pair<int,int>> stk;
    for (int i = n-1; i >= 0; i--) {
        while (stk.size() && stk.back().first <= A[i]) stk.pop_back();
        int dp = stk.empty() ? 1 : stk.back().second+1;
        stk.emplace_back(A[i], dp);
        ans = max(ans, dp);
    }
    cout << ans;
}
