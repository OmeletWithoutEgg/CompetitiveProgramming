
#include <bits/stdc++.h>
#define pb emplace_back
#define all(v) begin(v), end(v)
#define debug(x...) qqbx(#x, x)
template <typename ...T> void qqbx(const char *s, T ...args) {
    std::cerr << "(" << s << ") = (";
    int cnt = sizeof...(T);
    ( (std::cerr << args << (--cnt ? ", " : ")\n"), 0), ..., void() );
}

using namespace std;
using ll = long long;
using ld = long double;
const int N = 200025, MOD = 1000000007;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
}
