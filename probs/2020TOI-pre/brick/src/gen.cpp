#include "jngen.h"
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

const int maxSum = 2000, maxw = 20, maxk = 100;
const int maxAttempt = 10;

void gen(string filename, int maxn, int maxc, bool hasx) {
    int n = rnd.next(1, maxn);
    string T = rnds.random(n, hasx ? "rgbx" : "rgb");

    maxc = min(maxc, n * 2);
    int k;
    vector<string> c;
    bool succ = false;
    for (int i = 0; i < maxAttempt && !succ; i++) {
        succ = true;
        try {
            k = rnd.next(1, maxk);
            int sum = rnd.next(k, min(maxc * k, maxSum));
            auto sz = rndm.partition(sum, k, 1, maxc);
            c.resize(k);
            map<int, vector<int>> mp;
            for (int i = 0; i < k; i++) mp[sz[i]].push_back(i);
            for (const auto &[len, idxs]: mp) {
                auto cs = TArray<string>::randomfUnique(idxs.size(), [len](){ return rnds.random(len, "rgb"); });
                int j = 0;
                for (int id: idxs)
                    c[id] = cs[j++];
            }
        } catch(...) {
            succ = false;
            cerr << "Fail #" << i << ".\n";
        }
    }
    auto w = Array::random(n, 1, maxw);

    ofstream fout(filename);
    fout << n << ' ' << k << '\n';
    for (int i = 0; i < k; i++)
        fout << c[i] << ' ' << w[i] << '\n';
    fout << T << '\n';
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    string prefix = getOpt("o");

    for (int i = 0; i < 10; i++)
        gen(prefix + format("%02d.in", i), 8, 2000, true);
    for (int i = 10; i < 20; i++)
        gen(prefix + format("%02d.in", i), 10000, 2000, false);
    for (int i = 20; i < 30; i++)
        gen(prefix + format("%02d.in", i), 10000, 7, true);
    for (int i = 30; i < 40; i++)
        gen(prefix + format("%02d.in", i), 10000, 2000, true);
}
