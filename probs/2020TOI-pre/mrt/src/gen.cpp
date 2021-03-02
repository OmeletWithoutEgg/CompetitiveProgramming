#include "jngen.h"
#include <cassert>
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

long long modpow(long long a, long long p, long long m) {
    assert (p >= 0);
    long long res = 1;
    while (p) {
        if (p & 1)
            res = res * a % m;
        a = a * a % m;
        p >>= 1;
    }
    return res;
}

void gen(string filename, int maxT, long long maxM, long long maxTM) {
    int T = rnd.next(1, maxT);
    maxM = rnd.next(3LL, max((long long)3, min(maxTM / T, maxM)));
    ofstream fout(filename);
    fout << T << '\n';
    for (int i = 0; i < T; i++) {
        int M = rndm.randomPrime(maxM);
        long long a, b, x1, x2, y1, y2;
        auto det = [&]() { return (4 * a % M * a % M * a % M + 27 * b % M * b % M) % M; };
        int attempt = 0;
        do {
            tie(x1, x2) = rnd.nextp(M, dpair);
            tie(y1, y2) = rnd.nextp(M);
            // y^2 = x^3 + ax + b
            long long c1 = (modpow(y1, 2, M) - modpow(x1, 3, M) + M) % M;
            long long c2 = (modpow(y2, 2, M) - modpow(x2, 3, M) + M) % M;
            a = (c2 - c1 + M) * modpow(x2 - x1 + M, M-2, M) % M;
            b = (c1 - a * x1 % M + M) % M;
            if (++attempt % 10 == 0)
                cerr << M << ' ' << "10 attempt\n";
            if (++attempt >= 50)
                throw string("Sad cannot generate.");
        } while (det() == 0);
        fout << M << ' ' << a << ' ' << b << ' ' << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
    }
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    string prefix = getOpt("o");

    const long long INF = 1e18;
    const long long inf = 1LL << 31;
    for(int i = 0; i < 10; i++)
        gen(prefix + format("%02d.in", i), 100, 100, 10000);
    for (int i = 10; i < 20; i++)
        gen(prefix + format("%02d.in", i), 10000, inf, 100000);
    for(int i = 20; i < 40; i++)
        gen(prefix + format("%02d.in", i), 100000, inf, INF);
}
