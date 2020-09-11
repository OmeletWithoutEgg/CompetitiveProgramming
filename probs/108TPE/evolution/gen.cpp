#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;

const int seed = 7122;
mt19937 rng(seed);
template <typename ...T> string format(const char *F, T ...args) {
    const int B = 1<<10;
    char buf[B] = {};
    sprintf(buf, F, args...);
    return string(buf);
}
vector<int> genPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    shuffle(p.begin(), p.end(), rng);
    return p;
}
vector<pair<int,int>> genTree(int n) {
    int t = uniform_int_distribution<int>(0, 4)(rng);
    // random, bamboo, bamboo with branches, star, star with branches
    vector<pair<int,int>> res;
    int m = n;
    if(t == 0) {
        m = 1;
    } else if(t == 1) {
        for(int i = 1; i < n; i++) res.pb(i-1, i);
    } else if(t == 2) {
        m = uniform_int_distribution<int>(1, n)(rng);
        for(int i = 1; i < m; i++) res.pb(i-1, i);
    } else if(t == 3) {
        for(int i = 1; i < n; i++) res.pb(0, i);
    } else if(t == 4) {
        m = uniform_int_distribution<int>(1, n)(rng);
        for(int i = 1; i < m; i++) res.pb(0, i);
    }
    for(int i = m; i < n; i++) {
        int pa = uniform_int_distribution<int>(0, i-1)(rng);
        res.pb(i, pa);
    }
    cerr << n << '\n';
    for(auto &[a, b]: res) if(uniform_int_distribution<int>(0, 1)(rng) == 1) swap(a, b);
    return res;
}
void gen(string filename, int maxn, int maxm) {
    ofstream fout(filename);
    const int n = uniform_int_distribution<int>(1, maxn)(rng);
    const int m = uniform_int_distribution<int>(1, maxm)(rng);
    fout << n << ' ' << m << '\n';
    vector<int> perm = genPermutation(n);
    vector<pair<int,int>> edges = genTree(n);
    for(auto [a, b]: edges) fout << perm[a] << ' ' << perm[b] << '\n';
    for(int i = 0; i < m; i++) {
        int a = uniform_int_distribution<int>(0, n-1)(rng);
        int b = uniform_int_distribution<int>(0, n-1)(rng);
        fout << a << ' ' << b << '\n';
    }
    fout.close();
}
signed main() {
    for(int i = 0; i < 10; i++)
        gen(format("%02d.in", i), 500, 700000);
    for(int i = 10; i < 15; i++)
        gen(format("%02d.in", i), 2000, 2000);
    for(int i = 15; i < 20; i++)
        gen(format("%02d.in", i), 15000, 1000000);
    for(int i = 20; i < 35; i++)
        gen(format("%02d.in", i), 100000, 2500000);
    const int samples[2] = {10, 13};
    for(int i = 0; i < 2; i++) {
        string command = format("cat sample-%d.in >%02d.in", i+1, samples[i]);
        int code = system(command.c_str());
        cerr << format("code = %d", code) << '\n';
    }
    for(int i = 0; i < 35; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        int code = system(command.c_str());
        cerr << format("code = %d", code) << '\n';
    }
}

