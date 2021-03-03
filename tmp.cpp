#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#ifdef local
#define debug(a...) qqbx(#a, a)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\n")));
}
#define TAK(STL, BEG, END, OUT) template <typename ...T> std::ostream & operator<<(std::ostream &O, std::STL<T...> v) \
    { O << BEG; int f = 0; for (auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }
TAK(vector, "[", "]", e)
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
const int maxn = 500025, mod = 1000000007, base = 880301;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
using ll = long long;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
}
