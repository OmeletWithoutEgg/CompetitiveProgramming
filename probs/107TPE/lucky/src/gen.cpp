#include "jngen.h"
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

void gen(string filename, int minn, int maxn, bool eq, bool small) {
    int n = rnd.next(minn, maxn);
    int m = eq ? n : rnd.next(minn, maxn);
    Array2d a(n);
    int minc = -100, maxc = 100;
    if(small)
        minc = rnd.next(-1000, -150), maxc = rnd.next(-20, 20);
    for(int i = 0; i < n; i++)
        a[i] = Array::random(m, minc, maxc);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            a[i][j] = clamp(a[i][j], -100, 100);

    ofstream fout(filename);
    fout << n << ' ' << m << endl;
    fout << a << endl;
    fout.close();
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    string prefix = getOpt("o");

    for(int i = 0; i < 5; i++)
        gen(prefix + format("%02d.in", i), 2, 2, true, i % 4 == 0);
    for(int i = 5; i < 20; i++)
        gen(prefix + format("%02d.in", i), 3, 5, true, i % 4 == 0);
    for(int i = 20; i < 30; i++)
        gen(prefix + format("%02d.in", i), 6, 100, true, i % 4 == 0);
    for(int i = 30; i < 40; i++)
        gen(prefix + format("%02d.in", i), 6, 1000, false, i % 4 == 0);
}
