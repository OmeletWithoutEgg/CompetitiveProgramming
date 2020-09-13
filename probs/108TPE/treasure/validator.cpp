#include <bits/stdc++.h>

using namespace std;

template <typename ...T> string format(const char *F, T ...args) {
    const int B = 1<<10;
    char buf[B] = {};
    sprintf(buf, F, args...);
    return string(buf);
}
void test(string filename, int minn, int maxn, int maxk) {
    ifstream fin(filename);
    int n, m;
    assert(fin >> n >> m);
    assert(minn <= n && n <= maxn);
    assert(minn <= m && m <= maxn);
    int treasure = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int v;
            assert(fin >> v);
            if((i == 0 && j == 0) || (i == n-1 && j == m-1)) assert(v != -1);
            if(v == 1) ++treasure;
        }
    }
    assert(treasure <= maxk);
    cerr << filename << " OK!\n";
}
signed main() {
    for(int i = 0; i < 8; i++)
        test(format("%02d.in", i), 2, 6, 36);
    for(int i = 8; i < 15; i++)
        test(format("%02d.in", i), 10, 100, 2);
    for(int i = 15; i < 30; i++)
        test(format("%02d.in", i), 10, 100, 10000);
}
