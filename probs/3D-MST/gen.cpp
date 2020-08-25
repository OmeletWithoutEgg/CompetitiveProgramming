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
signed main() {
    rng.seed(7122);
    /* rng.seed(chrono::steady_clock::now().time_since_epoch().count()); */
    ios_base::sync_with_stdio(0);
    for(int i = 0; i < 5; i++)
        gen(format("%02d.in", i), 10, 10);
    for(int i = 5; i < 10; i++)
        gen(format("%02d.in", i), 100, 100000);
    for(int i = 10; i < 20; i++)
        gen(format("%02d.in", i), 5000, 100);
    for(int i = 20; i < 30; i++)
        gen(format("%02d.in", i), 5000, 100000);
    for(int i = 0; i < 30; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        system(command.c_str());
    }
}
