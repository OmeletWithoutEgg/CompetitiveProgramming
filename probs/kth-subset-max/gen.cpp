#include <bits/stdc++.h>

using namespace std;
template<typename ...T> string format(const char *s, T ...args) {
    static char buf[1<<10];
    sprintf(buf, s, args...);
    return string(buf);
}
mt19937 rng(7122);
void gen(string filename, int maxn, int maxc) {
    ofstream fout(filename);
    int n = uniform_int_distribution<int>(1, maxn)(rng);
    int c = -1;
    switch(uniform_int_distribution<int>(0, 3)(rng)) {
        case 0:
            c = sqrt(maxn);
            break;
        case 1:
            c = maxn * log(n);
            break;
        case 2:
            c = sqrt(maxc);
            break;
        default:
            c = maxc;
    }
    fout << n << '\n';
    for(int i = 0; i < n; i++) fout << uniform_int_distribution<int>(0, c)(rng) << (i+1==n ? '\n' : ' ');
    fout.close();
}
signed main() {
    for(int i = 0; i < 10; i++)
        gen(format("%02d.in", i), 20, 1000);
    for(int i = 10; i < 20; i++)
        gen(format("%02d.in", i), 1000, 1000);
    for(int i = 20; i < 40; i++)
        gen(format("%02d.in", i), 500000, 1000000000);
    for(int i = 0; i < 40; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        int code = system(command.c_str());
        cerr << i << ' ' << code << '\n';
    }
}
