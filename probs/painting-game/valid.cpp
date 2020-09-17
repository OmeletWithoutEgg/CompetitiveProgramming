#include <bits/stdc++.h>

using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}
void test(string filename) {
    ifstream fin(filename);
    int n, m, t, d;
    int64_t k;
    assert(fin >> n >> m >> k >> t >> d);
    vector<int> w(n);
    for(int &x: w) assert(fin >> x);
    if(set<int>(w.begin(), w.end()).size() != n) cerr << "NOT";
    cerr << filename << " ok\n";
}
signed main() {
    for(int i = 3; i < 6; i++) test(format("%02d.in", i));
}
