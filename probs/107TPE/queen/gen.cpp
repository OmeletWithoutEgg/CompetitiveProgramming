#include "jngen.h"
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

void randomGen(string filename, int minn, int maxn, int maxc) {
    int n = rnd.next(minn/2, maxn/2) * 2;
    auto X = Array::randomUnique(n, -maxc, maxc);
    auto Y = Array::random(n, -maxc, maxc);
    ofstream fout(filename);
    fout << n << '\n';
    for(int i = 0; i < n; i++)
        fout << X[i] << ' ' << Y[i] << '\n';
    fout.close();
    cerr << filename << ' ' << n << " ok\n";
}

void genBigPolygon(string filename, int minn, int maxn, int maxc) {
    int n = rnd.next(minn/2, maxn/2);
    auto P1 = rndg.convexPolygon(n, -maxc / 2, maxc / 2);
    auto P2 = rndg.convexPolygon(n, -maxc / 2, maxc / 2);
    auto S1 = rndg.point(-maxc, -maxc, -maxc/2, maxc);
    auto S2 = rndg.point(maxc/2, -maxc, maxc, maxc);

    /*
    Drawer d;
    d.polygon(P1.shift(S1));
    d.polygon(P2.shift(S2));
    d.dumpSvg("polygon.svg");
    */
    ofstream fout(filename);
    fout << (P1.shift(S1) + P2.shift(S2)).shuffled().printN() << '\n';
    fout.close();
    cerr << filename << ' ' << n*2 << " ok\n";
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    // parseArgs(argc, argv);

    for(int i = 0; i < 5; i++)
        randomGen(format("%02d.in", i), 6, 3000, 100000);
    for(int i = 5; i < 20; i++)
        genBigPolygon(format("%02d.in", i), 6, 3000, 100000000);
    for(int i = 20; i < 30; i++)
        randomGen(format("%02d.in", i), 20000, 50000, 100000000);
    for(int i = 30; i < 40; i++)
        randomGen(format("%02d.in", i), 60000, 100000, 100000000);
}
