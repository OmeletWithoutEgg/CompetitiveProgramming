#include "jngen.h"
#include <cassert>
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

void gen(int maxn, int maxq, int C) {
    const int maxc = (1<<C) - 1;
    const int n = maxn;
    auto a = Array::random(n, 0, maxc-1);
    const int q = maxq;
    cout << n << ' ' << q << ' ' << C << '\n';
    cout << a << '\n';
    const int K = 100;
    for (int i = 0; i < q; i++) {
        int t = rnd.next(1, 10000) == 1 ? 2 : 1;
        cout << t << ' ';
        if (t == 1) {
            int l = rnd.next(1, K);
            int r = rnd.next(n - K + 1, n);
            assert (l <= r);
            cout << l << ' ' << r << '\n';
        } else {
            int p = rnd.next(1, n);
            int x = rnd.next(0, maxc-1);
            cout << p << ' ' << x << '\n';
        }
    }
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    int maxnq = getOpt(0);
    int C = getOpt(2);
    gen(maxnq, maxnq, C);
}
