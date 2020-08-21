#include <bits/stdc++.h>

using namespace std;
int64_t nextint(int64_t lim) {
    static mt19937 rng(7122);
    return uniform_int_distribution<int64_t>(1, lim)(rng);
}
template<typename ...T> string format(const char *s, T ...args) {
    static char buf[1<<10];
    sprintf(buf, s, args...);
    return string(buf);
}
void gen(int subtask, string filename, int maxN, int maxk, int maxc, int maxt) {
    ofstream fout(filename);
    int N = nextint(maxN);
    int K = nextint(maxk);
    int W = nextint(maxk);
    int64_t C = nextint(1LL * maxc * N);
    int64_t T = nextint(1LL * maxt * N);
    fout << N << ' ' << K << ' ' << W << ' ' << C << ' ' << T << '\n';
    for(int i = 1; i <= N; i++) {
        int c = nextint(maxc);
        int t = nextint(maxt);
        fout << c << ' ' << t << '\n';
    }
    fout.close();
}
signed main() {
    for(int i = 0; i < 5; i++)
        gen(1, format("%02d.in", i), 20, 100, 100, 100);
    for(int i = 5; i < 10; i++)
        gen(2, format("%02d.in", i), 1000, 100000, 100000, 10000);
    for(int i = 10; i < 40; i++) {
        int t = nextint(4);
        if(t == 1)
            gen(3, format("%02d.in", i), 100000, 100, 100, 1000000000);
        else if(t == 2) 
            gen(3, format("%02d.in", i), 100000, 100, 1000000000, 1000000000);
        else if(t == 3)
            gen(3, format("%02d.in", i), 1000, 100, 100000, 100000);
        else if(t == 4)
            gen(3, format("%02d.in", i), 1000, 10000000, 1000000000, 100000000);
    }
    for(int i = 0; i < 40; i++)
        system(format("./sol <%02d.in >%02d.out", i, i).c_str());
}
