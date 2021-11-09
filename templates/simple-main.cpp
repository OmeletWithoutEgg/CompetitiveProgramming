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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}
