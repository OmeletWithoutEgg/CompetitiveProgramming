#include "jngen.h"
#include <iostream>
#include <queue>
#include <cassert>
using namespace std;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
const int inf = 1e9;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

ostream & operator<<(ostream &O, pair<int,int> p) {
    return O << p.first << ' ' << p.second;
}

void gen(string picname, string filename, int n, int C) {
    auto cv = rndg.convexPolygon(n, C);
    Drawer d;
    d.polygon(cv);
    d.dumpSvg(picname);
    ofstream fout(filename);
    fout << cv.printN() << '\n';
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    string prefix = getOpt("o");
    int n = getOpt("n", 10);
    int c = getOpt("c", 10000);

    cout << "n = " << n << "; c = " << c << '\n';
    for(int i = 0; i < 1000; i++) {
        cout << "generating " << i << '\n';
        gen(prefix + format("/pics/%03d.svg", i), prefix + format("%03d.in", i), n, c);
    }
}
