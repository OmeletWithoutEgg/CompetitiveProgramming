#include <bits/stdc++.h>
#ifdef local
#define debug(a...) qqbx(#a, a)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local

using namespace std;
using ll = long long;
const int maxn = 5025;
const ll INF = 1e18;

int pos[maxn];
struct {
    int sum[maxn];
    void add(int p) {
        for (; p < maxn; p += p & -p) sum[p] += 1;
    }
    int qry(int p) {
        int r = 0;
        for (; p > 0; p -= p & -p) r += sum[p];
        return r;
    }
    void clear() {
        for (int i = 0; i < maxn; i++) sum[i] = 0;
    }
} bit;
ll dp[maxn], pref[maxn];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        pos[x] = i;
    }

    for (int i = 1; i <= n; i++) for (int j = 1; j < i; j++) if (pos[j] > pos[i]) ++pref[i];
    for (int i = 1; i <= n; i++)
        cerr << pref[i] << (i == n ? '\n' : ' ');
    for (int i = 1; i <= n; i++) {
        bit.clear();
        ll cost = 0;
        dp[i] = INF;
        for (int j = i; j >= 1; j--) {
            cost -= bit.qry(pos[j]);
            cost += bit.qry(maxn-1) - bit.qry(pos[j]);
            bit.add(pos[j]);
            debug(j, i, cost);
            dp[i] = min(dp[i], dp[j-1] + cost);
        }
    }
    ll ans = dp[n];
    for (int i = 1; i <= n; i++) ans += pref[i];
    cout << ans << '\n';
    // dp[i] = min(dp[j-1] + cost(j, i))
}

/*
5
3 2 1 5 4

9
6 1 3 4 9 5 7 8 2
*/
