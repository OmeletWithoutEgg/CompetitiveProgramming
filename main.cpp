// An AC a day keeps the doctor away.
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#ifdef local
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
#define orange(args...) danb(#args, args)
using std::cerr;
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((cerr << "\e[1;32m(" << s << ") = ("), ..., (cerr << args << (--cnt ? ", " : ")\e[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    cerr << "\e[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L) cerr << (f++ ? ", " : "") << *L;
    cerr << " ]\e[0m\n";
}
#else
#define safe ((void)0)
#define debug(...) ((void)0)
#define orange(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)

using namespace std;

int lowbit(int x) {
    return x & -x;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, R;
    cin >> n >> R;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int xor_sum = 0;
    for (int i = 0; i < n; i++)
        xor_sum ^= a[i];

    if (xor_sum == 0 || lowbit(xor_sum) > R)
        return cout << 0 << '\n', 0;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int newA = a[i];
        for (int j = 0; j < 30; j++) {
            // assume 1 << j as highbit of R'
            // lowbit(xor_sum ^ a[i] ^ (a[i] - R')) > R'
            if ((xor_sum ^ a[i] ^ newA) >> j & 1) {
                if (newA < (1 << j))
                    break;
                newA -= 1 << j;
            }
            int newR = a[i] - newA;
            if (newR > 0 && newR <= R && (int)__lg(newR) == j) {
                ++ans;
            }
        }
    }
    cout << ans << '\n';
}
