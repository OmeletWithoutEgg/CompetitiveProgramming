#include <bits/stdc++.h>

using namespace std;
const int inf = 1e9;

int seed = 20217122;
mt19937_64 rng(seed);

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

vector<int> genDistinct(int n, int minc, int maxc) {
    if(maxc - minc + 1 <= n * 2) {
        vector<int> s(maxc - minc + 1);
        iota(s.begin(), s.end(), minc);
        vector<int> res(n);
        sample(s.begin(), s.end(), res.begin(), n, rng);
        return res;
    } else {
        unordered_set<int> s;
        do {
            int x = uniform_int_distribution<int>(minc, maxc)(rng);
            s.insert(x);
        } while(s.size() < n);
        vector<int> res(s.begin(), s.end());
        shuffle(res.begin(), res.end(), rng);
        return res;
    }
}

void gen(string filename, int minn, int maxn, int maxc) {
    int n = uniform_int_distribution<int>(minn/2, maxn/2)(rng) * 2;
    vector<int> x = genDistinct(n, -maxc, maxc);
    vector<int> y = genDistinct(n, -maxc, maxc);
    // vector<int> y(n);
    // for(int &c: y) c = uniform_int_distribution<int>(-maxc, maxc)(rng);

    ofstream fout(filename);
    fout << n << '\n';
    for(int i = 0; i < n; i++)
        fout << x[i] << ' ' << y[i] << '\n';
    fout.close();
}

signed main(int argc, char **argv) {
    // gen("00.in", 6, 3000, 10000);
    for(int i = 0; i < 10; i++)
        gen(format("%02d.in", i), 60000, 100000, 1000000000);

    /*
    const int samples[3] = {0, 1, 2};
    for(int i = 0; i < 3; i++) {
        string command = format("cat sample-%d.in >%02d.in", i+1, samples[i]);
        int code = system(command.c_str());
        cerr << code << ' ';
        cerr << samples[i] << '\n';
    }
    */

    for(int i = 0; i < 10; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        /* string command = format("./sol <%02d.in >%02d.out && ./bal <%02d.in >%02d-T.out && diff %02d.out %02d-T.out 2>/dev/null", i, i, i, i, i, i); */
        int code = system(command.c_str());
        cerr << format("testdata = %d, code = %d", i, code) << '\n';
    }
    /* int code = system("rm *-T.out"); */
    /* cerr << code << '\n'; */
}

