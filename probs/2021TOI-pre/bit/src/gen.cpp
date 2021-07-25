#include "jngen.h"
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

void gen(string filename, int maxn, int maxc) {
    int n = rnd.next(1, min(maxn, maxc));
    auto a = Array::randomUnique(n, 1, maxc);
    ofstream fout(filename);
    fout << a.printN() << '\n';
    fout.close();
    cerr << n << '\n';
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    string prefix = getOpt("o");

    for(int i = 0; i < 10; i++)
        gen(prefix + format("%02d.in", i), 1000, 7);
    for (int i = 10; i < 30; i++)
        gen(prefix + format("%02d.in", i), 1000, 1024);
}
