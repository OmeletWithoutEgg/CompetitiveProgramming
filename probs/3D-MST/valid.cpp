#include <bits/stdc++.h>

using namespace std;

template <typename ...T> string format(const char *F, T ...args) {
    const int B = 1<<10;
    char buf[B] = {};
    sprintf(buf, F, args...);
    return string(buf);
}
signed main() {
    ios_base::sync_with_stdio(0);
    for(int i = 0; i < 5; i++) {
        ifstream fin(format("%02d.in", i));
        int n, x, y, z;
        fin >> n;
        assert(n <= 3);
        while(n--) {
            fin >> x >> y >> z;
            assert(max({abs(x),abs(y),abs(z)}) <= 10);
        }
        fin.close();
    }
    for(int i = 0; i < 10; i++) {
        ifstream fin(format("%02d.in", i));
        int n;
        fin >> n;
        assert(n <= 100);
        fin.close();
    }
    for(int i = 10; i < 15; i++) {
        ifstream fin(format("%02d.in", i));
        int n, x, y, z;
        fin >> n;
        while(n--) {
            fin >> x >> y >> z;
            assert(y == 0 && z == 0);
        }
        fin.close();
    }
    for(int i = 0; i < 40; i++) {
        set<tuple<int,int,int>> s;
        ifstream fin(format("%02d.in", i));
        int n, x, y, z;
        assert(fin >> n);
        assert(1 <= n && n <= 5000);
        while(n--) {
            assert(fin >> x >> y >> z);
            assert(max({abs(x),abs(y),abs(z)}) <= 100000);
            assert(!s.count({x,y,z}));
            s.insert({x,y,z});
        }
        assert(!(fin >> n));
        fin.close();
    }
    cerr << "Perfect!\n";
}
