#include <bits/stdc++.h>

using namespace std;

template <typename ...T> string format(const char *F, T ...args) {
    const int B = 1<<10;
    char buf[B] = {};
    sprintf(buf, F, args...);
    return string(buf);
}
mt19937 rng;
void gen(string filename, int maxn, int maxc) {
    ofstream fout(filename);
    int n = uniform_int_distribution<int>(1, maxn)(rng);
    fout << n << '\n';
    for(int i = 0; i < n; i++) {
        int x = uniform_int_distribution<int>(-maxc, maxc)(rng);
        int y = uniform_int_distribution<int>(-maxc, maxc)(rng);
        int z = uniform_int_distribution<int>(-maxc, maxc)(rng);
        fout << x << ' ' << y << ' ' << z << '\n';
    }
    fout.close();
}
void genCube(string filename, int maxn, int maxc) {
    ofstream fout(filename);
    int n = uniform_int_distribution<int>(1, cbrt(maxn))(rng);
    vector<int> X(n), Y(n), Z(n);
    for(int i = 0; i < n; i++) X[i] = uniform_int_distribution<int>(-maxc, maxc)(rng);
    for(int i = 0; i < n; i++) Y[i] = uniform_int_distribution<int>(-maxc, maxc)(rng);
    for(int i = 0; i < n; i++) Z[i] = uniform_int_distribution<int>(-maxc, maxc)(rng);
    fout << n*n*n << '\n';
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) for(int k = 0; k < n; k++) fout << X[i] << ' ' << Y[j] << ' ' << Z[k] << '\n';
    fout.close();
}
void specialGen(string filename, int a, int b, int maxo, int maxr) {
    ofstream fout(filename);
    fout << a+b << '\n';
    for(int i = 0; i < a; i++) {
        int x = uniform_int_distribution<int>(-maxr, maxr)(rng) - maxo;
        int y = uniform_int_distribution<int>(-maxr, maxr)(rng) - maxo;
        int z = uniform_int_distribution<int>(-maxr, maxr)(rng) - maxo;
        fout << x << ' ' << y << ' ' << z << '\n';
    }
    for(int i = 0; i < b; i++) {
        int x = uniform_int_distribution<int>(-maxr, maxr)(rng) + maxo;
        int y = uniform_int_distribution<int>(-maxr, maxr)(rng) + maxo;
        int z = uniform_int_distribution<int>(-maxr, maxr)(rng) + maxo;
        fout << x << ' ' << y << ' ' << z << '\n';
    }
    fout.close();
}
signed main() {
    rng.seed(7122);
    /* rng.seed(chrono::steady_clock::now().time_since_epoch().count()); */
    ios_base::sync_with_stdio(0);
    for(int i = 0; i < 5; i++)
        gen(format("%02d.in", i), 4, 10);
    for(int i = 5; i < 10; i++)
        gen(format("%02d.in", i), 100, 100000);
    for(int i = 10; i < 20; i++)
        gen(format("%02d.in", i), 5000, 100);
    for(int i = 20; i < 30; i++)
        gen(format("%02d.in", i), 5000, 100000);
    for(int i = 30; i < 35; i++)
        genCube(format("%02d.in", i), 5000, 100000);
    specialGen("35.in", 4000, 1, 1000, 10);
    specialGen("36.in", 4000, 80, 50000, 1000);
    specialGen("37.in", 1, 2000, 100, 1000);
    specialGen("38.in", 3000, 2000, 30000, 10000);
    specialGen("39.in", 3000, 2000, 30000, 10000);
    for(int i = 0; i < 40; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        int code = system(command.c_str());
        cerr << command << ' ' << " successfully ends with return value " << code << '\n';
    }
}
