#include <iostream>
using namespace std;

struct Edge {
    int w;
    int a, b;
    int p;
    friend ostream & operator<<(ostream &O, const Edge &e) {
        return O << e.w << ' ' << e.a << ' ' << e.b << ' ' << e.p;
    }
};
#define JNGEN_EXTRA_WEIGHT_TYPES Edge
#include "jngen.h"

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

Tree give_me_a_tree(int n) {
    int policy = rnd.next(3);
    if (policy == 0)
        return Tree::random(n).shuffled();
    else if (policy == 1)
        return Tree::star(n).shuffled();
    else
        return Tree::randomPrim(n, rnd.next(-1000, 1000)).shuffled();
}

void gen(ofstream &&fout, int minn, int maxn, bool pIsOne, bool isBamboo) {
    const int maxw = 1000;
    const int maxp = 6;
    const int maxh = 24;
    const int maxm = 60;
    const int maxq = 200000;
    int n = rnd.next(minn, maxn);
    int q = rnd.next(1, maxq);
    auto T = isBamboo ? Tree::bamboo(n) : give_me_a_tree(n);
    auto weight = TArray<Edge>::randomf(n-1, [&]() -> Edge {
        int w = rnd.next(1, maxw);
        int p = pIsOne ? 1 : rnd.next(1, maxp);
        int a = rnd.next(p), b = rnd.next(p);
        return { w, a, b, p };
    });
    T.setEdgeWeights(weight);
    fout << n << ' ' << q << '\n';
    fout << T.add1() << '\n';
    for (int i = 0; i < q; i++) {
        int h = rnd.next(maxh);
        int m = rnd.next(maxm);
        auto [s, t] = rnd.nextp(1, n, dpair);
        fout << h << ' ' << m << ' ' << s << ' ' << t << '\n';
    }
    fout.close();

    cerr << n << '\n';
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    string prefix = getOpt("o");
    auto testcase = [&prefix](int tc) {
        return ofstream(prefix + format("%02d.in", tc));
    };

    for (int i = 0; i < 10; i++) {
        gen(testcase(i), 1, 500, false, false);
    }
    for (int i = 10; i < 20; i++) {
        gen(testcase(i), 20000, 50000, true, false);
    }
    for (int i = 20; i < 30; i++) {
        gen(testcase(i), 20000, 50000, false, true);
    }
    for (int i = 30; i < 45; i++) {
        gen(testcase(i), 20000, 50000, false, false);
    }
}
