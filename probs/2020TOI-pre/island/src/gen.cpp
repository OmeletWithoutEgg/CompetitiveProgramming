#include "jngen.h"
#include <cassert>
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

void gen(string filename, int maxn, int maxw) {
    int n = rnd.next(3, maxn);
    bool policy = rnd.next(0, 99) < 70;
    auto T = policy ? Tree::random(n) : Tree::randomPrim(n, rnd.next(1, max(1, n / 10)));
    T.setEdgeWeights(Array::random(n-1, 1, maxw));
    ofstream fout(filename);
    fout << T.shuffled().printN() << '\n';
}

void specialGen(string filename, int n, int w) {
    auto T = Tree::star(n-3).link(0, Tree::bamboo(3), 1);
    T.setEdgeWeights(Array(n-4, w) + Array(2, w-1) + Array(1, 1));
    ofstream(filename) << T.shuffled().printN() << '\n';
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    string prefix = getOpt("o");

    for(int i = 0; i < 10; i++)
        gen(prefix + format("%02d.in", i), 100, 100);
    for (int i = 10; i < 20; i++)
        gen(prefix + format("%02d.in", i), 100000, 1);
    for(int i = 20; i < 40; i++) {
        if (i % 5 == 0) {
            specialGen(prefix + format("%02d.in", i), rnd.wnext(3, 100000, 20), rnd.next(5, 99));
        } else {
            gen(prefix + format("%02d.in", i), 100000, 100);
        }
    }
    specialGen(prefix + "07.in", 6, 5);
    specialGen(prefix + "08.in", 87, 39);
}
