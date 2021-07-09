#include "sorting.h"
#include <bits/stdc++.h>
#ifdef local
#define debug(a...) qqbx(#a, a)
#define pary(a...) danb(#a, a)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\e[1;32m(" << s << ") = ("), ..., (std::cerr << a << (--cnt ? ", " : ")\e[0m\n")));
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

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
    if (is_sorted(S, S+N)) return 0;
    vector<pair<int,int>> best(M, pair<int,int>(-1, -1));

    auto go = [&](int R) {
        vector<int> targ(N);
        for (int i = 0; i < N; i++) targ[i] = i;
        for (int i = R-1; i >= 0; i--)
            swap(targ[X[i]], targ[Y[i]]);

        vector<int> s(S, S+N);
        vector<int> pos(N);
        for (int i = 0; i < N; i++)
            pos[s[i]] = i;
        vector<pair<int,int>> ans;
        for (int i = 0, it = 0; i < R; i++) {
            {
                int a = X[i], b = Y[i];
                swap(targ[a], targ[b]);
                swap(pos[s[a]], pos[s[b]]);
                swap(s[a], s[b]);
            }
            {
                while (it < N && pos[it] == pos[targ[pos[it]]]) ++it;
                if (it == N) {
                    ans.emplace_back(0, 0);
                } else {
                    ;
                    int a = pos[it];
                    int b = pos[targ[a]];
                    swap(pos[s[a]], pos[s[b]]);
                    swap(s[a], s[b]);
                    ans.emplace_back(a, b);
                }
            }
        }
        // pary(all(s));
        if (is_sorted(all(s))) {
            if (best.size() > ans.size())
                best = ans;
            return true;
        } else {
            return false;
        }
    };

    int ans = 0;
    for (int s = 1<<20; s; s>>=1)
        if (ans + s <= M && !go(ans + s))
            ans += s;
    ++ans;
    go(ans);
    for (size_t i = 0; i < best.size(); i++)
        tie(P[i], Q[i]) = best[i];
    return best.size();
}
