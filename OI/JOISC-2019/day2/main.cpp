#include <bits/stdc++.h>
#ifdef local
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(a...) qqbx(#a, a)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
 
using namespace std;
const int maxn = 200025;
 
int H[maxn], A[maxn], B[maxn];

int ans[2005][2005];
 
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> H[i] >> A[i] >> B[i];
    memset(ans, -1, sizeof ans);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (max(A[i], A[j]) <= (i-j) && (i-j) <= min(B[i], B[j]))
                ans[j][i] = abs(H[i] - H[j]);
        }
    }
    for (int l = n; l >= 1; l--) {
        for (int r = 1; r <= n; r++)
            ans[l][r] = max({ ans[l][r], ans[l+1][r], ans[l][r-1] });
    }
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << ans[l][r] << '\n';
    }
}
