#include <bits/stdc++.h>

using namespace std;
const int inf = 1e9;

int seed = 52920319;
mt19937_64 rng(seed);
int64_t gi(int64_t l, int64_t r){ return uniform_int_distribution<int64_t>(l, r)(rng); };

vector<int> primes { 3, 17, 14699, 65537, 880301, 104857601, 998244353, 1000000007, 1000000009 };
int tot;
template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

vector<int> distinct_numbers(int n, int lim) {
    if(lim >= n*2) {
        set<int> ts;
        for(int i = 0; i < n; i++) {
            int c;
            do c = gi(0, lim); while(ts.count(c));
            ts.insert(c);
        }
        return vector<int>(ts.begin(), ts.end());
    } else {
        vector<int> t(lim+1);
        iota(t.begin(), t.end(), 0);
        shuffle(t.begin(), t.end(), rng);
        t.resize(n);
        sort(t.begin(), t.end());
        return t;
    }
}

bool dice(int x) { return gi(0, x-1) == 0; }

void gen(int subtask, int maxN, int maxT, int maxW, int64_t maxK) {
    int N = gi(1, maxN);
    int M = gi(1, min(maxT-1, maxN));
    int64_t K = gi(1, subtask == 3 ? min<int64_t>(1LL*N*M, maxK) : maxK);

    assert(M < maxT);
    vector<int> t = distinct_numbers(M+1, maxT);
    int T = t.back(); t.pop_back();
    shuffle(t.begin(), t.end(), rng);

    vector<int> w(N), a(M), b(M);
    if(subtask == 2) {
        w = distinct_numbers(N, maxW);
        for(int &x: a) x = gi(0, maxW);
        b = a;
    } else {
        for(int &x: w) x = gi(0, maxW);
        for(int &x: a) x = gi(0, maxW);
        for(int &x: b) x = gi(0, maxW);
    }
    for(int i = 0; i < M; i++) if(a[i] > b[i]) swap(a[i], b[i]);
    int D = dice(4) ? 2 : primes[gi(0, primes.size()-1)];

    string filename = format("%02d.in", tot);
    ofstream fout(filename);
    fout << N << ' ' << M << ' ' << K << ' ' << T << ' ' << D << '\n';
    for(int i = 0; i < N; i++) fout << w[i] << (i+1 != N ? ' ' : '\n');
    for(int i = 0; i < M; i++) fout << t[i] << ' ' << a[i] << ' ' << b[i] << '\n';
    fout.close();
    cerr << N << ' ' << M << ' ' << K << ' ' << T << ' ' << D << '\n';
    cerr << "No. " << tot << " ok.\n";
    tot++;
}
signed main(int argc, char **argv) {
    gen(1, 3, 9, 9, 3);
    gen(1, 8, 10, 10, 10);
    gen(1, 20, 500, 500, 500);

    gen(2, 1000, 1000, 1000, 1e5);
    gen(2, 1e5, 1e5, 1e5, 1e5);
    gen(2, 1e5, inf, inf, 1e5);

    gen(3, 100, 100, 100, 100);
    gen(3, 3000, 1e5, 1e5, 1e5);
    gen(3, 3000, inf, inf, inf);

    gen(4, 5, 5, inf, 100);
    gen(4, 20, 20, inf, 1e5);

    gen(4, 20, 20, inf, inf);

    gen(5, 1e3, 1e5, 100, 1);
    gen(5, 1e5, 1e5, 1e5, 1);
    gen(5, 1e5, 1e5, inf, 1);

    gen(6, 1e5, 7122, 7122, 1e5);
    gen(6, 1e5, inf, inf, 1e5);

    gen(7, 5e4, 100, 100, 1e12);
    gen(7, 5e5, 1e5, 1e5, 1e12);
    gen(7, 5e5, inf, inf, 1e12);
    const int samples[3] = {tot++, tot++, tot++};
    for(int i = 0; i < 3; i++) {
        string command = format("cat sample-%d.in >%02d.in", i+1, samples[i]);
        int code = system(command.c_str());
        cerr << code << ' ';
        cerr << samples[i] << '\n';
    }
    for(int i = 0; i < tot; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        /* string command = format("./sol <%02d.in >%02d.out && ./bal <%02d.in >%02d-T.out && diff %02d.out %02d-T.out 2>/dev/null", i, i, i, i, i, i); */
        int code = system(command.c_str());
        cerr << format("testdata = %d, code = %d", i, code) << '\n';
    }
    /* int code = system("rm *-T.out"); */
    /* cerr << code << '\n'; */
}

