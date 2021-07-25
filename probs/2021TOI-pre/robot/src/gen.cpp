#include "jngen.h"
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

void gen(ofstream &&fout, int minn, int maxn, int maxm) {
    int maxs, maxd;
    {
        vector<int> lim {1, 5, 10, 1000, 100000, 1000000000};
        auto [a, b] = rnd.nextp(lim.size(), opair);
        maxs = lim[b];
        maxd = lim[a];
    }
    int n = rnd.next(minn, maxn);
    int m = rnd.next(1, maxm);
    auto t = n==1 ? Array() : rndm.partition(rnd.next()&1 ? rnd.next(m*2) : rnd.next(1000000000), n-1);
    auto s = Array::random(n, 1, maxs);
    auto d = Array::random(n, 0, maxd);
    fout << n << ' ' << m << '\n';
    fout << t << '\n' << s << '\n' << d << '\n';
    fout.close();

    cerr << n << ' ' << m << '\n';
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    string prefix = getOpt("o");
    auto testcase = [&prefix](int tc) {
        return ofstream(prefix + format("%02d.in", tc));
    };

    for (int i = 0; i < 15; i++) {
        gen(testcase(i), 1, 1000, 1000);
    }
    for (int i = 15; i < 50; i++) {
        gen(testcase(i), 1, 1000, 1000000000);
    }
}
