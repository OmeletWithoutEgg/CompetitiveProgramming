#include "monster.h"
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
#define pary(x...) danb(#x, x)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\e[1;32m(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\e[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\e[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\e[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)

using namespace std;

std::vector<int> Solve(int N) {
    vector<int> cnt(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            cnt[Query(i, j) ? i : j] += 1;
        }
    }
    pary(all(cnt));
    vector<int> id(N);
    iota(all(id), 0);
    sort(all(id), [&](int a, int b){ return cnt[a] < cnt[b]; });
    if (Query(id[1], id[0])) {
        swap(id[0], id[1]);
    }
    if (!Query(id[N-2], id[N-1])) {
        swap(id[N-2], id[N-1]);
    }
    pary(all(id));
    vector<int> T(N);
    for (int i = 0; i < N; i++) T[id[i]] = i;
    pary(all(T));
    return T;
}
// 4 1 3 0 2
