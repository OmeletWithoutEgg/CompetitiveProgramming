#include <bits/stdc++.h>

using namespace std;

template <typename ...T> string format(const char *F, T ...args) {
    const int B = 1<<10;
    char buf[B] = {};
    sprintf(buf, F, args...);
    return string(buf);
}
void test(string filename) {
    ifstream fin(filename);
    int n;
    fin >> n;
    set<tuple<int,int,int>> s;
    bool ok = true;
    for(int i = 0; i < n; i++) {
        int x, y, z;
        fin >> x >> y >> z;
        if(s.count({x,y,z})) ok = 0;
        s.insert({x, y, z});
    }
    cerr << filename << ' ';
    if(ok)
        cerr << "Success.\n";
    else
        cerr << "Fail.\n";
}
signed main() {
    for(int i = 0; i < 40; i++) test(format("%02d.in", i));
}
