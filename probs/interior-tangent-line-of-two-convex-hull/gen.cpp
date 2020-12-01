#include <bits/stdc++.h>

using namespace std;
const int inf = 1e9;

int seed = 7122;
mt19937_64 rng(seed);

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

signed main(int argc, char **argv) {
    return 0;
    const int samples[3] = {0, 1, 2};
    for(int i = 0; i < 3; i++) {
        string command = format("cat sample-%d.in >%02d.in", i+1, samples[i]);
        int code = system(command.c_str());
        cerr << code << ' ';
        cerr << samples[i] << '\n';
    }
    for(int i = 0; i < 0; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        /* string command = format("./sol <%02d.in >%02d.out && ./bal <%02d.in >%02d-T.out && diff %02d.out %02d-T.out 2>/dev/null", i, i, i, i, i, i); */
        int code = system(command.c_str());
        cerr << format("testdata = %d, code = %d", i, code) << '\n';
    }
    /* int code = system("rm *-T.out"); */
    /* cerr << code << '\n'; */
}

