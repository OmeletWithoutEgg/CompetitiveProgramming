#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
}
