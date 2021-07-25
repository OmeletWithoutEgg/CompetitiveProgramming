#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#ifdef local
#define debug(a...) qqbx(#a, a)
#define pary(a...) danb(#a, a)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr<<"\e[1;32m("<<s<<") = ("), ..., (std::cerr<<a<<(--cnt?", ":")\e[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr<<"\e[1;32m[ "<<s<<" ] = [ ";
    for (int f=0; L!=R; ++L) std::cerr<<(f++?" ":"")<<*L;
    std::cerr<<" ]\e[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)

using namespace std;

const int maxn = 1025, inf = 1e9;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
}
