#include "jngen.h"
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

const int maxc = 100000, maxw = 1000;

Array randomWeight(int n) {
    int dice = rnd.next(1, 6);
    if (dice <= 2) {
        int param = rnd.next(-20, 20);
        return Array::randomf(n, [param](){ return rnd.wnext(-maxw, maxw, param); });
    } else {
        return Array::random(n, -maxw, maxw);
    }
}

void gen(string filename, int maxn) {
    int n = rnd.next(1, maxn);
    int range = max((int)sqrt(n), rnd.next(maxc));
    auto pos = Arrayp::randomfUnique(n, [range](){
        pair<int,int> p;
        do
            p = rnd.nextp(-range, range);
        while (p.first == 0 && p.second == 0);
        return p;
    });
    auto w = randomWeight(n);

    ofstream fout(filename);
    fout << n << '\n';
    for (int i = 0; i < n; i++)
        fout << pos[i].first << ' ' << pos[i].second << ' ' << w[i] << '\n';
}

void genSameY(string filename, int maxn, int Y) {
    int n = rnd.next(1, maxn);
    int range = max((int)sqrt(n), rnd.next(maxc));
    auto X = Array::randomfUnique(n, [range](){
        int x;
        do x = rnd.next(-range, range); while (x == 0);
        return x;
    });
    auto w = randomWeight(n);

    ofstream fout(filename);
    fout << n << '\n';
    for (int i = 0; i < n; i++)
        fout << X[i] << ' ' << Y << ' ' << w[i] << '\n';
}

void genMaxSubArray(string filename, Array weight) {
    int n = weight.size();
    int cx = rnd.choice({-1, 1});
    int cy = rnd.choice({-1, 1});
    auto p = Array::id(n).shuffled();

    ofstream fout(filename);
    fout << n << '\n';
    for (int i = 0; i < n; i++)
        fout << (p[i]+1) * cx << ' ' << (n-p[i]) * cy << ' ' << weight[p[i]] << '\n';
}


int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    string prefix = getOpt("o");

    for (int i = 0; i < 10; i++) {
        if (i % 3 == 2) {
            genSameY(prefix + format("%02d.in", i), 100, 0);
        } else {
            genSameY(prefix + format("%02d.in", i), 100, rnd.next(-1000, 1000));
        }
    }
    for (int i = 10; i < 20; i++) {
        if (i % 3 == 2) {
            genSameY(prefix + format("%02d.in", i), 10000, 0);
        } else {
            genSameY(prefix + format("%02d.in", i), 1000, rnd.next(-10000, 10000));
        }
    }
    for (int i = 20; i < 40; i++)
        gen(prefix + format("%02d.in", i), 10000);
    for (int i = 40; i < 50; i++) {
        auto p = rndm.partition(rnd.next(3, 10000), 3, 1);
        genMaxSubArray(prefix + format("%02d.in", i), Array::random(p[0], 999) + Array::random(p[1], -1000, -200) + Array::random(p[2], 999));
    }
    for (int i = 50; i < 60; i++)
        gen(prefix + format("%02d.in", i), 300000);
}
