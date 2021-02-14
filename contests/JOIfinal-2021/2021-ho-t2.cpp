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
const int maxn = 200025;
const ll INF = 1e18;

ll W[maxn], X[maxn];
ll preMx[maxn], preMn[maxn];
ll ans[maxn];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> X[i];
    for (int i = 0; i < q; i++) cin >> W[i];
    for (int i = 1; i < q; i++) W[i] += W[i-1];

    preMx[0] = max<ll>(0, W[0]);
    preMn[0] = min<ll>(0, W[0]);
    for (int i = 1; i < q; i++) {
        preMx[i] = max(preMx[i-1], W[i]);
        preMn[i] = min(preMn[i-1], W[i]);
    }

    X[0] = -INF;
    X[n+1] = INF;
    for (int i = 0; i <= n; i++) {
        ll len = X[i+1] - X[i];
        ll mx = 0, mn = 0;
        if (abs(preMx[q-1]) + abs(preMn[q-1]) < len) {
            ans[i] += abs(preMx[q-1]);
            ans[i+1] += abs(preMn[q-1]);
            continue;
        }
        int j = -1;
        for (int s = 1 << 20; s; s >>= 1) if (j + s < q && abs(preMx[j+s]) + abs(preMn[j+s]) < len) j += s;
        ++j;
        // debug(j, abs(preMx[j])+abs(preMn[j]), len);
        if (W[j] < 0) {
            ans[i] += abs(preMx[j]);
            ans[i+1] += len - abs(preMx[j]);
        } else if (W[j] > 0) {
            ans[i] += len - abs(preMn[j]);
            ans[i+1] += abs(preMn[j]);
        } else
            throw;
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
}

/*
4 3
-2 3 5 8
2
-4
7
 */
