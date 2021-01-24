#include "jngen.h"
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

void gen(string filename, int mina, int maxa, int minn, int maxn) {
    int n = rnd.next(minn, maxn);
    int a = rnd.next(mina, maxa);
    ofstream fout(filename);
    fout << a << ' ' << n << '\n';
    for(int i = 0; i < n; i++) {
        int x = rnd.next(1, 100);
        int y = rnd.next(1, min(a + 5, 100));
        fout << x << ' ' << y << '\n';
    }
    fout.close();
    cerr << a << ' ' << n << '\n';
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    string prefix = getOpt("o");

    for(int i = 0; i < 20; i++)
        gen(prefix + format("%02d.in", i), 5, 10, 1, 10);
    for(int i = 20; i < 30; i++)
        gen(prefix + format("%02d.in", i), 5, 1000, 1, 1000);
    for(int i = 30; i < 40; i++)
        gen(prefix + format("%02d.in", i), 900, 1000, 900, 1000);
}
