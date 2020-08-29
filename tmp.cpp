#include <bits/stdc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> void qqbx(const char*s, const H &h, T ...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr (sizeof...(T)) qqbx(++s, args...);
}
#define pb emplace_back

using namespace std;
typedef long long ll;
const int N = 2500025;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
}
