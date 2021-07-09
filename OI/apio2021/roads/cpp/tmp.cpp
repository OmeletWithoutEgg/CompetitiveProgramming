#include "roads.h"

#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
#define pary(x...) danb(#x, x)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\033[1;32m(" << s << ") = ("), ..., (std::cerr << a << (--cnt ? ", " : ")\033[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\033[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\033[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)
using namespace std;
using ll = long long;
const int maxn = 100025;

signed main() {
    int n = 100000;
    int H = 50000;
    cout << n << '\n';
    for (int i = 1; i < H; i++) {
        cout << 0 << ' ' << i << ' ' << rand() % 10 + 1 << '\n';
    }
    for (int i = H; i < n; i++) {
        cout << i << ' ' << rand() % H << ' ' << rand() % 10 + 1 << '\n';
    }
}
