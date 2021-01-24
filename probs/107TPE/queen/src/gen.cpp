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

Polygon randomPolygon(int n, int C) {
    int dx = rnd.next(C / 5, C / 2);
    int dy = rnd.next(C / 5, C / 2);
    return rndg.convexPolygon(n, -dx, -dy, dx, dy);
}
void genBigPolygon(string filename, int minn, int maxn, int maxc) {
    int n = rnd.next(minn/2, maxn/2);
    auto P1 = randomPolygon(n, maxc);
    auto P2 = randomPolygon(n, maxc);
    auto S1 = rndg.point(-maxc, -maxc, -maxc/2, maxc);
    auto S2 = rndg.point(maxc/2, -maxc, maxc, maxc);

    /*
    Drawer d;
    d.polygon(P1.shift(S1));
    d.polygon(P2.shift(S2));
    d.dumpSvg("polygon.svg");
    */
    auto P = (P1.shift(S1) + P2.shift(S2)).sorted();
    P.erase(unique(P.begin(), P.end(), [](Point a, Point b){ return a.x == b.x; }), P.end());
    ofstream fout(filename);
    fout << P.choice(P.size() / 2 * 2).shuffle().printN() << '\n';
    fout.close();
    cerr << filename << ' ' << n*2 << " ok\n";
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    string prefix = getOpt("o");

    for(int i = 0; i < 5; i++)
        randomGen(prefix + format("%02d.in", i), 6, 3000, 100000);
    for(int i = 5; i < 20; i++)
        genBigPolygon(prefix + format("%02d.in", i), 6, 3000, 100000000);
    for(int i = 20; i < 30; i++)
        randomGen(prefix + format("%02d.in", i), 20000, 50000, 100000000);
    for(int i = 30; i < 40; i++)
        genBigPolygon(prefix + format("%02d.in", i), 60000, 100000, 100000000);
}
