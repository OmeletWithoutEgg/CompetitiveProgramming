#include "jngen.h"
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

void gen(ofstream &&fout, int minn, int maxn, bool isPerm) {
    const int maxc = 1000000001;
    int n = rnd.next(minn, maxn);
    auto a = isPerm ? Array::id(n).shuffled() : Array::randomUnique(n, maxc);
    auto b = a.shuffled();
    fout << n << '\n' << a << '\n' << b << '\n';
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
        gen(testcase(i), 1, 10, true);
    }
    for (int i = 10; i < 20; i++) {
        gen(testcase(i), 1, 100, false);
    }
    for (int i = 20; i < 25; i++) {
        gen(testcase(i), 1, 200000, false);
    }
    for (int i = 25; i < 40; i++) {
        gen(testcase(i), 150000, 200000, false);
    }
}
