#include "jngen.h"
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

void randomGen(string filename, int minn, int maxn, int maxc) {
    int n = rnd.next(minn/2, maxn/2);
    ofstream fout(filename);
    fout << n*2 << '\n';

    auto gen = [&](int cx, int cy, int dx, int dy) {
        int lx = cx - dx/2, rx = cx + dx/2;
        int ly = cy - dy/2, ry = cy + dy/2;
        auto X = Array::randomUnique(n, lx, rx);
        auto Y = Array::random(n, ly, ry);
        for(int i = 0; i < n; i++) {
            fout << X[i] << ' ' << Y[i] << '\n';
        }
    };
    int cx1 = rnd.next(-maxc * 0.7, -maxc * 0.3), cy1 = rnd.next(-maxc, maxc);
    int cx2 = rnd.next(maxc * 0.3, maxc * 0.7), cy2 = rnd.next(-maxc, maxc);
    int dx1 = rnd.next(maxc / 5, maxc / 3), dy1 = rnd.next(maxc / 5, maxc / 3);
    int dx2 = rnd.next(maxc / 5, maxc / 3), dy2 = rnd.next(maxc / 5, maxc / 3);
    gen(cx1, cy1, dx1, dy1);
    gen(cx2, cy2, dx2, dy2);

    fout.close();
    cerr << filename << ' ' << n*2 << " ok\n";
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
    P1.sort(), P2.sort();
    P1.erase(unique(P1.begin(), P1.end(), [](Point a, Point b){ return a.x == b.x; }), P1.end());
    P2.erase(unique(P2.begin(), P2.end(), [](Point a, Point b){ return a.x == b.x; }), P2.end());
    size_t sz = min(P1.size(), P2.size());
    ofstream fout(filename);
    fout << (P1.shift(S1).choice(sz) + P2.shift(S2).choice(sz)).shuffle().printN() << '\n';
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
