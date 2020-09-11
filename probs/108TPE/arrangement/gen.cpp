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
void gen(string filename, int maxn, int maxk) {
    int n = uniform_int_distribution<int>(1, maxn)(rng);
    int k = uniform_int_distribution<int>(1, min(n, maxk))(rng);
    ofstream fout(filename);
    fout << n << ' ' << k << '\n';
    fout.close();
}
signed main() {
    for(int i = 0; i < 5; i++)
        gen(format("%02d.in", i), 10, 1);
    for(int i = 5; i < 10; i++)
        gen(format("%02d.in", i), 10, 10);
    for(int i = 10; i < 20; i++)
        gen(format("%02d.in", i), 100, 100);
    for(int i = 20; i < 30; i++)
        gen(format("%02d.in", i), 10000, 10000);
    const int samples[3] = {0, 5, 6};
    for(int i = 0; i < 3; i++) {
        string command = format("cat sample-%d.in >%02d.in", i+1, samples[i]);
        int code = system(command.c_str());
        cerr << command << ' ' << format("code = %d", code) << '\n';
    }
    for(int i = 0; i < 30; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        int code = system(command.c_str());
        cerr << format("code = %d", code) << '\n';
    }
}

