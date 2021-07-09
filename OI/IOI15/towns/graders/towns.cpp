#include "towns.h"
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

map<pair<int,int>,int> asked;
int ask(int a, int b) {
    if (a == b) return 0;
    if (a > b) swap(a, b);
    if (asked.count({ a, b })) return asked[{ a, b }];
    return asked[{ a, b }] = getDistance(a, b);
}
int hubDistance(int N, int sub) {
    asked.clear();
    assert (1 <= sub && sub <= 6);
    int A = 0, B = 0;
    for (int i = 0; i < N; i++) {
        if (ask(0, i) > ask(0, A)) {
            A = i;
        }
    }
    for (int i = 0; i < N; i++) {
        if (ask(A, i) > ask(A, B)) {
            B = i;
        }
    }
    int R = ask(A, B);
    debug(A, B, R);
    vector<tuple<int,int,int>> leaf(N);
    for (int i = 0; i < N; i++) {
        int AB = ask(A, B);
        int AI = ask(A, i);
        int BI = ask(B, i);
        assert ((AB + abs(AI - BI)) % 2 == 0);
        R = min(R, (AB + abs(AI - BI)) / 2);
        leaf[i] = { (AB + AI - BI) / 2, (AB + abs(AI - BI)) / 2, i };
    }
    debug(asked.size(), N * 3 - 6);
    sort(all(leaf));
    if (sub <= 2) return R;
    bool bal = false;
    for (int i = 0, j = 0; i < N; i = j) {
        for (j = i; j < N; j++) if (get<0>(leaf[i]) != get<0>(leaf[j])) break;
        int RR = get<1>(leaf[i]);
        if (i <= N / 2 && N - j <= N / 2 && RR == R) {
            if (j - i <= N / 2) {
                bal = true;
                break;
            }
            vector<int> ids;
            for (int t = i; t < j; t++)
                ids.push_back(get<2>(leaf[t]));

            auto sameSubtree = [&](int x, int y) {
                int Lx = (ask(A, x) + ask(x, B) - ask(A, B)) / 2;
                int Ly = (ask(A, y) + ask(y, B) - ask(A, B)) / 2;
                return ask(x, y) != Lx + Ly;
            };
            vector<int> stk;
            for (int x: ids) {
                if (stk.empty()) {
                    stk.push_back(x);
                } else {
                    if (sameSubtree(x, stk.back()))
                        stk.push_back(x);
                    else
                        stk.pop_back();
                }
            }
            if (stk.empty()) {
                bal = true;
            } else {
                vector<bool> inStk(N);
                for (int x: stk) inStk[x] = true;
                int cnt = stk.size();
                if (cnt > N / 2) break;
                for (int x: ids)
                    if (!inStk[x] && sameSubtree(x, stk.back())) {
                        ++cnt;
                        if (cnt > N / 2) break;
                    }
                if (cnt <= N / 2)
                    bal = true;
            }
            break;
        }
    }
    debug(bal);
    debug(asked.size());
    return bal ? R : -R;
}
