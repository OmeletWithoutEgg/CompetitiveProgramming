#include <bits/stdc++.h>
#ifdef local
#define debug(args...) ppbx(#args, args)
template <typename ...T> void ppbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v), end(v)
using namespace std;
using ll = long long;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cout << 80 * (60 + 40 * pow(1.2, 49 - 60)) / 100 << '\n';
}
