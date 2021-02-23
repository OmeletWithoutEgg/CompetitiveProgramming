#include <bits/stdc++.h>
#ifdef local
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(a...) qqbx(#a, a)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local

using namespace std;
using ll = long long;
using ld = long double;
using point = complex<ld>;
const ll INF = 9e18;
const int maxn = 5025;

int DP[2][maxn][maxn];
int a[maxn], b[maxn];
void calc(int dp[][maxn], int n) {
    for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) dp[i][j] = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i && j && a[i] == b[j]) {
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
            }
            if (i)
                dp[i][j] = max(dp[i][j], dp[i-1][j]);
            if (j)
                dp[i][j] = max(dp[i][j], dp[i][j-1]);
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int T, type;
    cin >> T >> type;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int j = 1; j <= n; j++) cin >> b[j];

        calc(DP[0], n);
        reverse(a+1, a+n+1);
        reverse(b+1, b+n+1);
        calc(DP[1], n); // reversed
        reverse(a+1, a+n+1);
        reverse(b+1, b+n+1);

        int pa = 1;
        for (int i = 2; i <= n; i++) if (a[i] > a[i-1]) pa= i;
        int ans = 0;
        for (int i = 1, j = n, l = 1, r = n; i <= pa; i++) {
            while (j >= 1 && a[j] < a[i]) --j;
            while (l <= n && b[l] < a[i]) ++l;
            while (r >= 1 && b[r] < a[i]) --r;
            if (l <= n && b[l] == a[i]) {
                debug(i, j, l, r);
                ans = max(ans, DP[0][i-1][l-1] + DP[1][n-j][n-r] + 2);
            }
            if (r >= 1 && b[r] == a[i]) {
                debug(i, j, l, r);
                ans = max(ans, DP[0][i-1][l-1] + DP[1][n-j][n-r] + 2);
            }
        }
        debug(ans);
        cout << n * 2 - ans << '\n';
    }
}
