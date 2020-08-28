#include <bits/stdc++.h>

using namespace std;
const int inf = 1e9;

int seed = 52920319;
mt19937_64 rng(seed);
int64_t gi(int64_t l, int64_t r){ return uniform_int_distribution<int64_t>(l, r)(rng); };

vector<int> primes {2, 3, 17, 14699, 65537, 880301, 104857601, 998244353, 1000000007, 1000000009 };
int tot;
template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}
void gen(int subtask, int maxN, int maxT, int maxW, int64_t maxK) {
    if(subtask) {
        string filename = format("%02d.in", tot++);
        freopen(filename.c_str(), "w", stdout);
    }
    int N = gi(1, maxN);
    int M = gi(1, min(maxT-1, maxN));
    int64_t K = gi(1, subtask == 3 ? min<int64_t>(1LL*N*M, maxK) : maxK);

    assert(M < maxT);
    vector<int> t;
    if(maxT >= 1000000) {
        set<int> ts;
        for(int i = 0; i < M+1; i++) {
            int c;
            do c = gi(0, maxT); while(ts.count(c));
            ts.insert(c);
        }
        t = vector<int>(ts.begin(), ts.end());
    } else {
        t = vector<int>(maxT+1);
        iota(t.begin(), t.end(), 0);
        shuffle(t.begin(), t.end(), rng);
        t.resize(M+1);
        sort(t.begin(), t.end());
    }
    int T = t.back(); t.pop_back();
    shuffle(t.begin(), t.end(), rng);

    vector<int> w(N), a(M), b(M);
    for(int &x: w) x = gi(0, maxW);
    for(int &x: a) x = gi(0, maxW);
    if(subtask == 2)
        b = a;
    else
        for(int &x: b) x = gi(0, maxW);
    for(int i = 0; i < M; i++) if(a[i] > b[i]) swap(a[i], b[i]);
    int D = primes[gi(0, primes.size()-1)];

    cout << N << ' ' << M << ' ' << K << ' ' << T << ' ' << D << '\n';
    for(int i = 0; i < N; i++) cout << w[i] << (i+1 != N ? ' ' : '\n');
    for(int i = 0; i < M; i++) cout << t[i] << ' ' << a[i] << ' ' << b[i] << '\n';
    cerr << N << ' ' << M << ' ' << K << ' ' << T << ' ' << D << '\n';
    cerr << "No. " << tot << " ok.\n";
}
signed main(int argc, char **argv) {
    gen(1, 3, 9, 9, 3);
    gen(1, 8, 10, 10, 10);
    gen(1, 20, 500, 500, 500);

    gen(2, 1000, 100, 100, 1e5);
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
    for(int i = 0; i < tot; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        system(command.c_str());
        cerr << command << '\n';
        cerr << "Solution to No. " << i << " ok.\n";
    }
    freopen("sample-1.in", "w", stdout);
    gen(0, 3, 9, 9, 3);
    freopen("sample-2.in", "w", stdout);
    gen(0, 5, 5, inf, 100);
    freopen("sample-3.in", "w", stdout);
    gen(0, 10, 100, 100, 100);
    for(int i = 1; i <= 3; i++) {
        string command = format("./sol <sample-%d.in >sample-%d.out", i, i);
        system(command.c_str());
        cerr << command << '\n';
        cerr << "Solution to sample No. " << i << " ok.\n";
    }
}

