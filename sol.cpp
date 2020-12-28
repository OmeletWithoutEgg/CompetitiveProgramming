#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define pb emplace_back

using namespace std;
const int N = 24;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> m >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vector<int> dp(1<<n);
    dp[0] = true;
    for(int s = 1; s < (1<<n); s++) {
        int i = __lg(s & -s);
        dp[s] = dp[s ^ (1<<i)] && 0;
    }
}
