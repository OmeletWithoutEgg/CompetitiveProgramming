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

int A[maxn];

ll pre[maxn], suf[maxn];

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = n; i >= 1; i--) A[i] -= A[i-1];

    for (int i = 2; i <= n; i++) pre[i] = max(0, 1 - A[i]); // plus ? > 0
    for (int i = 2; i <= n; i++) suf[i] = max(0, A[i] + 1); // minus ? < 0

    // for (int i = 1; i <= n; i++) cerr << A[i] << (i==n ? '\n' : ' ');
    // for (int i = 1; i <= n; i++) cerr << pre[i] << (i==n ? '\n' : ' ');
    // for (int i = 1; i <= n; i++) cerr << suf[i] << (i==n ? '\n' : ' ');

    for (int i = 1; i <= n; i++) pre[i] += pre[i-1];
    for (int i = n; i >= 1; i--) suf[i] += suf[i+1];
    
    ll ans = 1e18;
    for (int i = 0; i <= n; i++)
        ans = min(ans, max(pre[i], suf[i+1]));
    cout << ans << '\n';

}
