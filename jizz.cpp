#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back

using namespace std;
using ll = long long;
const int MOD = 1000000007, inf = 1e9, K = 27, N = 300025;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
}
