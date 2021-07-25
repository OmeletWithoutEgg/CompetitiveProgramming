#include <bits/stdc++.h>

using namespace std;

int readInt(int l, int r) {
    int x;
    assert (cin >> x && l <= x && x <= r);
    return x;
}
struct Dsu {
    vector<int> pa;
    Dsu (int n) : pa(n) { iota(pa.begin(), pa.end(), 0); }
    int anc(int x) {
        return x==pa[x] ? x : pa[x]=anc(pa[x]);
    }
    bool join(int x, int y) {
        if ((x=anc(x))==(y=anc(y))) return false;
        return pa[y] = x, true;
    }
};
signed main() {
    int n = readInt(1, 50000);
    int q = readInt(1, 200000);
    Dsu dsu(n);
    for (int i = 0; i < n-1; i++) {
        int u, v, w, a, b, p;
        u = readInt(1, n);
        v = readInt(1, n);
        w = readInt(1, 1000);
        a = readInt(0, 5);
        b = readInt(0, 5);
        p = readInt(1, 6);
        assert (0 <= a && a < p);
        assert (0 <= b && b < p);
        --u, --v;
        assert (dsu.join(u, v));
    }
    for (int i = 0; i < q; i++) {
        int h, m, s, t;
        h = readInt(0, 23);
        m = readInt(0, 59);
        s = readInt(1, n);
        t = readInt(1, n);
        assert (s != t);
    }
    // cerr << "valid testcase!\n";
}
