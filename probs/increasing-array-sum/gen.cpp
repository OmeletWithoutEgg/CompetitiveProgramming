#include <bits/stdc++.h>

using namespace std;
template<typename ...T> string format(const char *s, T ...args) {
    static char buf[1<<10];
    sprintf(buf, s, args...);
    return string(buf);
}
mt19937 rng(597122);
bool dice(int x) { return uniform_int_distribution<int>(0, x-1)(rng) == 0; }
vector<int> getIncreasingArray(int n) {
    vector<int> res;
    int type = uniform_int_distribution<int>(0, 2)(rng);
    if(type == 0) {
        res.resize(n);
        res[0] = uniform_int_distribution<int>(0, 3)(rng);
        for(int i = 1; i < n; i++) res[i] = res[i-1] + uniform_int_distribution<int>(1, 3)(rng);
    } else if(type == 1) {
        set<int> s;
        while(s.size() < n) s.insert(uniform_int_distribution<int>(0, 1e9)(rng));
        for(int x: s) res.emplace_back(x);
    } else if(type == 2) {
        set<int> s;
        while(s.size() < n) s.insert(uniform_int_distribution<int>(0, n*2)(rng));
        for(int x: s) res.emplace_back(x);
    }
    return res;
}
void gen(string filename, int maxn, int maxq, int maxs) {
    ofstream fout(filename);
    int n = uniform_int_distribution<int>(1, maxn)(rng);
    int q = uniform_int_distribution<int>(1, maxq)(rng);
    vector<int> a = getIncreasingArray(n);
    vector<int> b(q);
    for(int &x: b) {
        int lim = maxs;
        if(dice(4)) lim = min(lim, int(sqrt(maxs)));
        if(dice(4)) lim = min(lim, n*2);
        x = uniform_int_distribution<int>(0, lim)(rng);
    }
    fout << n << '\n';
    for(int i = 0; i < n; i++) fout << a[i] << (i+1==n ? '\n' : ' ' );
    fout << q << '\n';
    for(int i = 0; i < q; i++) fout << b[i] << '\n';
    fout.close();
    cerr << n << ' ' << a.front() << ' ' << a.back() << '\n';
}
void genMax(string filename, int n) {
    ofstream fout(filename);
    fout << n << '\n';
    for(int i = 0; i < n; i++) fout << i << (i+1==n ? '\n' : ' ');
    fout << n << '\n';
    for(int i = 0; i < n; i++)
        fout << i << '\n';
    fout.close();
}
signed main() {
    for(int i = 0; i < 5; i++)
        gen(format("%02d.in", i), 20, 100, 100);
    for(int i = 5; i < 15; i++)
        gen(format("%02d.in", i), 2000, 500000, 500000);
    for(int i = 15; i < 20; i++)
        gen(format("%02d.in", i), 500000, 5, 500000);
    for(int i = 20; i < 25; i++)
        gen(format("%02d.in", i), 500000, 500000, 2000);
    for(int i = 25; i < 40; i++)
        gen(format("%02d.in", i), 500000, 500000, 500000);
    genMax("06.in", 2000);
    genMax("39.in", 500000);
    const int sample[] = {2, 3};
    for(int i = 0; i < 2; i++) {
        string command = format("cat <sample-%d.in >%02d.in", i+1, sample[i]);
        int code = system(command.c_str());
        cerr << i << ' ' << code << '\n';
    }
    for(int i = 0; i < 40; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        int code = system(command.c_str());
        cerr << i << ' ' << code << '\n';
        if(code) break;
    }
}
