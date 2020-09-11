#include <bits/stdc++.h>

using namespace std;

template <typename ...T> string format(const char *F, T ...args) {
    const int B = 1<<10;
    char buf[B] = {};
    sprintf(buf, F, args...);
    return string(buf);
}
const int N = 100025;
struct DSU {
    int pa[N], rk[N];
    void init(int n) {
        for(int i = 0; i < n; i++) pa[i] = i, rk[i] = 0;
    }
    int anc(int x) { return x==pa[x] ? x : pa[x]=anc(pa[x]); }
    bool join(int x, int y) {
        if((x=anc(x)) == (y=anc(y))) return false;
        if(rk[x] < rk[y]) swap(x, y);
        return pa[y] = x, rk[x]!=rk[y]||++rk[x];
    }
} dsu;
void test(string filename, int maxn, int maxq) {
    ifstream fin(filename);
    int n, q;
    assert(fin >> n >> q);
    assert(1 <= n && n <= maxn);
    assert(1 <= q && q <= maxq);
    dsu.init(n);
    for(int i = 1; i < n; i++) {
        int a, b;
        assert(fin >> a >> b);
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        assert(dsu.join(a, b));
    }
    for(int i = 0; i < q; i++) {
        int a, b;
        assert(fin >> a >> b);
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
    }
    cerr << filename << " OK!\n";
}
signed main() {
    for(int i = 0; i < 10; i++)
        test(format("%02d.in", i), 500, 700000);
    for(int i = 10; i < 15; i++)
        test(format("%02d.in", i), 2000, 2000);
    for(int i = 15; i < 20; i++)
        test(format("%02d.in", i), 15000, 1000000);
    for(int i = 20; i < 35; i++)
        test(format("%02d.in", i), 100000, 2500000);
}
