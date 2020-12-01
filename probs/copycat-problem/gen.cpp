#include <bits/stdc++.h>

using namespace std;
const int inf = 1e9;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

const int seed = 712222;
mt19937_64 rng(seed);
vector<int> distinct_numbers(int n, int lim) {
    if(lim >= n*2) {
        set<int> ts;
        for(int i = 0; i < n; i++) {
            int c;
            do c = uniform_int_distribution<int>(0, lim)(rng); while(ts.count(c));
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

bool dice(int x) { return uniform_int_distribution<int>(0, x-1)(rng) == 0; }

void gen(string filename, int maxn, int maxc, int policy = 0) {
    int n = dice(10) ? maxn : uniform_int_distribution<int>(1, maxn)(rng);
    int m = uniform_int_distribution<int>(1, maxn)(rng);
    int co = dice(3) ? m : dice(2) ? int(sqrt(m)) : uniform_int_distribution<int>(2, 5)(rng);
    int c = dice(3) ? 1e9 : dice(2) ? 1e4 : 100;
    co = min(co, m);
    c = min(c, maxc);
    vector<int> Q(n), p(m);
    vector<int> D(n);
    vector<int> OJ(n);
    for(int i = 0; i < n; i++) Q[i] = uniform_int_distribution<int>(-c, c)(rng);
    for(int i = 0; i < m; i++) p[i] = uniform_int_distribution<int>(0, c)(rng);
    if(policy == 1) {
        iota(D.begin(), D.end(), 1);
        fill(OJ.begin(), OJ.end(), 0);
    } else {
        D = distinct_numbers(n, 10000);
        for(int i = 0; i < n; i++) OJ[i] = uniform_int_distribution<int>(0, co)(rng);
    }
    ofstream fout(filename);
    fout << n << ' ' << m << '\n';
    for(int i = 0; i < m; i++) fout << p[i] << (i+1==m ? '\n' : ' ');
    for(int i = 0; i < n; i++) fout << Q[i] << ' ' << D[i] << ' ' << OJ[i] << '\n';
    fout.close();
    cerr << n << ' ' << m << '\n';
}

signed main(int argc, char **argv) {
    for(int i = 0; i < 5; i++)
        gen(format("%02d.in", i), 10, 1e9, 1);
    for(int i = 5; i < 15; i++)
        gen(format("%02d.in", i), 10, 1e9);
    for(int i = 15; i < 30; i++)
        gen(format("%02d.in", i), 5000, 1e9);

    const int samples[3] = {0, 6, 13};
    for(int i = 0; i < 3; i++) {
        string command = format("cat sample-%d.in >%02d.in", i+1, samples[i]);
        int code = system(command.c_str());
        cerr << code << ' ';
        cerr << samples[i] << '\n';
    }
    for(int i = 0; i < 30; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        /* string command = format("./sol <%02d.in >%02d.out && ./bal <%02d.in >%02d-T.out && diff %02d.out %02d-T.out 2>/dev/null", i, i, i, i, i, i); */
        int code = system(command.c_str());
        cerr << format("testdata = %d, code = %d", i, code) << '\n';
    }
}

