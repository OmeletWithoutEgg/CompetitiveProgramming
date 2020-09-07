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
    set<tuple<int,int,int>> s;
    for(int i = 0; i < n; i++) {
        int x, y, z;
        do {
            x = uniform_int_distribution<int>(-maxc, maxc)(rng);
            y = uniform_int_distribution<int>(-maxc, maxc)(rng);
            z = uniform_int_distribution<int>(-maxc, maxc)(rng);
        } while(s.count({x,y,z}));
        s.insert({x,y,z});
        fout << x << ' ' << y << ' ' << z << '\n';
    }
    fout.close();
}
void genChain(string filename, int maxn, int maxc) {
    ofstream fout(filename);
    int n = uniform_int_distribution<int>(1, maxn)(rng);
    vector<int> X(n);
    set<int> s;
    for(int i = 0; i < n; i++) {
        do {
            X[i] = uniform_int_distribution<int>(-maxc, maxc)(rng);
        } while(s.count(X[i]));
        s.insert(X[i]);
    }
    fout << n << '\n';
    for(int i = 0; i < n; i++) fout << X[i] << ' ' << 0 << ' ' << 0 << '\n';
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

void specialGen(string filename, int a, int b, int offset, int maxr) {
    ofstream fout(filename);
    fout << a+b << '\n';
    set<tuple<int,int,int>> s;
    int sgnx = uniform_int_distribution<int>(0, 1)(rng) ? 1 : -1;
    int sgny = uniform_int_distribution<int>(0, 1)(rng) ? 1 : -1;
    int sgnz = uniform_int_distribution<int>(0, 1)(rng) ? 1 : -1;
    for(int i = 0; i < a; i++) {
        int x, y, z;
        do {
            x = uniform_int_distribution<int>(-maxr, maxr)(rng) + offset * sgnx;
            y = uniform_int_distribution<int>(-maxr, maxr)(rng) + offset * sgny;
            z = uniform_int_distribution<int>(-maxr, maxr)(rng) + offset * sgnz;
        } while(s.count({x,y,z}));
        s.insert({x,y,z});
        fout << x << ' ' << y << ' ' << z << '\n';
    }
    for(int i = 0; i < b; i++) {
        int x, y, z;
        do {
            x = uniform_int_distribution<int>(-maxr, maxr)(rng) - offset * sgnx;
            y = uniform_int_distribution<int>(-maxr, maxr)(rng) - offset * sgny;
            z = uniform_int_distribution<int>(-maxr, maxr)(rng) - offset * sgnz;
        } while(s.count({x,y,z}));
        s.insert({x,y,z});
        fout << x << ' ' << y << ' ' << z << '\n';
    }
    fout.close();
}

void GG(string filename, int n, int maxc) {
    ofstream fout(filename);
    int ori = uniform_int_distribution<int>(0, 2)(rng);
    fout << n << '\n';
    set<tuple<int,int,int>> s;
    int offset = uniform_int_distribution<int>(-maxc+n, maxc-n)(rng);
    for(int i = 0; i < n; i++) {
        int x, y, z;
        x = offset + i;
        do {
            y = uniform_int_distribution<int>(-maxc, maxc)(rng);
            z = uniform_int_distribution<int>(-maxc, maxc)(rng);
        } while(s.count({x,y,z}));
        s.insert({x,y,z});
        vector<int> axis{x,y,z};
        rotate(axis.begin(), axis.begin() + ori, axis.end());
        fout << axis[0] << ' ' << axis[1] << ' ' << axis[2] << '\n';
    }
    fout.close();
    /* cerr << format("GG, n = %d, ori = %d", n, ori) << '\n'; */
}

signed main() {
    rng.seed(7122);
    /* rng.seed(chrono::steady_clock::now().time_since_epoch().count()); */
    ios_base::sync_with_stdio(0);
    for(int i = 0; i < 5; i++)
        gen(format("%02d.in", i), 4, 10);
    for(int i = 5; i < 10; i++)
        gen(format("%02d.in", i), 100, 100000);
    genChain("10.in", 50, 1000);
    genChain("11.in", 500, 100000);
    genChain("12.in", 5000, 30000);
    genChain("13.in", 5000, 100000);
    genChain("14.in", 5000, 100000);
    for(int i = 15; i < 20; i++)
        gen(format("%02d.in", i), 5000, 300);
    for(int i = 20; i < 30; i++)
        gen(format("%02d.in", i), 5000, 100000);
    for(int i = 30; i < 35; i++)
        genCube(format("%02d.in", i), 5000, 100000);
    specialGen("35.in", 4000, 1, 1000, 10);
    specialGen("36.in", 4000, 80, 50000, 1000);
    specialGen("37.in", 1, 2000, 100, 1000);
    specialGen("38.in", 3000, 2000, 30000, 10000);
    specialGen("39.in", 3000, 2000, 30000, 10000);
    specialGen("40.in", 2500, 2500, 70000, 200);
    specialGen("41.in", 2500, 2500, 90000, 200);
    specialGen("42.in", 2500, 2500, 50000, 10000);
    for(int i = 43; i < 50; i++)
        GG(format("%02d.in", i), 5000 - uniform_int_distribution<int>(0, 100)(rng), 100000);
    for(int i = 35; i < 50; i++) {
        string command = format("./sol <%02d.in >%02d.out && ./sub2 <%02d.in >%02d-T.out && diff %02d.out %02d-T.out", i, i, i, i, i, i);
        /* string command = format("./sol <%02d.in >%02d.out", i, i); */
        int code = system(command.c_str());
        cerr << format("testdata = %d, code = %d", i, code) << '\n';
    }
}
