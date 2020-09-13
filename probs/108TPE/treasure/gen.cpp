#include <bits/stdc++.h>

using namespace std;

const int seed = 7122;
mt19937 rng(seed);
template <typename ...T> string format(const char *F, T ...args) {
    const int B = 1<<10;
    char buf[B] = {};
    sprintf(buf, F, args...);
    return string(buf);
}
bool dice(int n) { return uniform_int_distribution<int>(0, n-1)(rng) == 0; }
void gen(string filename, int minn, int maxn, int maxk) {
    ofstream fout(filename);
    int n = uniform_int_distribution<int>(minn, maxn)(rng);
    int m = uniform_int_distribution<int>(minn, maxn)(rng);
    int k = uniform_int_distribution<int>(1, maxk)(rng);
    int O = uniform_int_distribution<int>(0, n+m<10 ^ dice(5) ? n+m : 3*(n+m))(rng);
    vector<int> B(n*m);
    for(int i = 0; i < k; i++) {
        int id = uniform_int_distribution<int>(0, n*m-1)(rng);
        B[id] = 1;
    }
    for(int i = 0; i < O; i++) {
        int id;
        do {
            id = uniform_int_distribution<int>(0, n*m-1)(rng);
        } while(id == 0 || id == n*m-1);
        B[id] = -1;
    }
    fout << n << ' ' << m << '\n';
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            fout << B[i*m+j] << (j+1==m ? '\n' : ' ');
        }
    }
    fout.close();
    cerr << n << ' ' << m << '\n';
}
signed main() {
    for(int i = 0; i < 8; i++)
        gen(format("%02d.in", i), 2, 6, 36);
    for(int i = 8; i < 15; i++)
        gen(format("%02d.in", i), 10, 100, 2);
    for(int i = 15; i < 20; i++)
        gen(format("%02d.in", i), 10, 100, 10000);
    for(int i = 20; i < 30; i++)
        gen(format("%02d.in", i), 95, 100, 10000);
    const int samples[3] = {3, 5, 6};
    for(int i = 0; i < 3; i++) {
        string command = format("cat sample-%d.in >%02d.in", i+1, samples[i]);
        int code = system(command.c_str());
        cerr << "code = " << code << '\n';
    }
    for(int i = 0; i < 30; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        /* string command = format("./sol <%02d.in >%02d.out && ./fake <%02d.in >%02d-T.out && diff %02d.out %02d-T.out", i, i, i, i, i, i); */
        int code = system(command.c_str());
        cerr << format("testdata = %d, code = %d", i, code) << '\n';
    }
}

