#include "jngen.h"
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}


string prefix;
void pr(string filename, string s) {
    ofstream fout(filename);
    fout << s;
    fout.close();
}
void gen(vector<int> outs, int minn, int maxn, int maxc) {
    int n = rnd.next(minn, maxn);
    Array2d a = Array2d::randomf(n, [&](){ return Array::random(n, maxc + 1); });
    for (int x: outs) {
        string filename = prefix + format("%02d.in", x);
        ofstream fout(filename);
        fout << n << '\n' << a << '\n';
        fout.close();
    }
    pr(prefix + format("%02d.out", outs[0]), "0\n");
    pr(prefix + format("%02d.out", outs[1]), "1\n");
    cerr << n << '\n';
}

void specialGen(vector<int> outs, int n) {
    Array2d a(n, Array(n));
    Array p1 = Array::id(n).shuffled();
    Array p2 = Array::id(n).shuffled();
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (i<=j) {
                a[p1[i]][p2[j]] = 4*n*n + (j-i)*(j-i);
            } else {
                a[p1[i]][p2[j]] = rnd.next(0, n*n);
            }
        }
    }
    for (int x: outs) {
        string filename = prefix + format("%02d.in", x);
        ofstream fout(filename);
        fout << n << '\n' << a << '\n';
        fout.close();
    }
    pr(prefix + format("%02d.out", outs[0]), "0\n");
    pr(prefix + format("%02d.out", outs[1]), "1\n");
    cerr << n << '\n';
}


int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    prefix = getOpt("o");

    for(int i = 0; i < 5; i++) gen({i, i+5}, 1, 20, 1);
    for(int i = 10; i < 15; i++) gen({i, i+5}, 1, 70, 1);
    for (int i = 20; i < 30; i++) gen({i, i+10}, 1, 70, 2000000);
    for (int i = 40; i < 50; i++) gen({i, i+15}, 70, 500, 2000000);
    for (int i = 50; i < 55; i++) specialGen({i, i+15}, 500 - (i - 50));

    /*
         [0, 5) n <= 20, a = 0/1
         [5, 10) n <= 20, a = 0/1 provides r,c
         [10, 15) n <= 70, a = 0/1
         [15, 20) n <= 70, a = 0/1 provides r,c
         [20, 30) n <= 70
         [30, 40) n <= 70 provides r,c
         [40, 55) n <= 500
         [55, 70) n <= 500 provides r,c
     */
}
