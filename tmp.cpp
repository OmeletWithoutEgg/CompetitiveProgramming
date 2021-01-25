#include <bits/stdc++.h>
#ifdef local
#define debug(a...) qqbx(#a, a)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\n")));
}
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define pb emplace_back

using namespace std;
using ll = long long;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
const int MOD = 1000000007, N = 100025;
const ll INF = 1e18;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
}
