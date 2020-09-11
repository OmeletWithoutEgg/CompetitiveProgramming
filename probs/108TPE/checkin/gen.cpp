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
bool dice(int x) {
    return uniform_int_distribution<int>(0, x-1)(rng) == 0;
}
// random, lonely island, all odd, all even
vector<pair<int,int>> genGraph(int A, int B, int K) {
    // i * B + j -> (i, j)
    vector<pair<int,int>> res;
    vector<int> eid(A*B);
    iota(eid.begin(), eid.end(), 0);
    shuffle(eid.begin(), eid.end(), rng);
    for(int i = 0; i < K; i++) {
        int id = eid[i];
        int a = id / B, b = id % B;
        ++a, ++b;
        res.pb(a, b);
    }
    return res;
}
const int maxc = 9487122;
void gen(string filename, int minn, int maxn, int maxk) {
    ofstream fout(filename);
    int A = uniform_int_distribution<int>(minn, maxn)(rng);
    int B = uniform_int_distribution<int>(minn, maxn)(rng);
    int S = uniform_int_distribution<int>(1, maxc)(rng);
    int M = uniform_int_distribution<int>(1, maxc)(rng);
    int K = (A*B%2==1 && dice(3)
                ? A*B
                : (dice(3) ? uniform_int_distribution<int>(1, min({maxk, A+B, A*B}))(rng)
                           : uniform_int_distribution<int>(1, min(maxk, A*B))(rng)));
    cerr << A << ' ' << B << ' ' << K << '\n';
    fout << A << ' ' << B << ' ' << S << ' ' << M << ' ' << K << '\n';
    vector<pair<int,int>> edges = genGraph(A, B, K);
    for(auto [a, b]: edges) fout << a << ' ' << b << ' ' << uniform_int_distribution<int>(1, maxc)(rng) << '\n';
    fout.close();
}
signed main() {
    for(int i = 0; i < 5; i++)
        gen(format("%02d.in", i), 2, 2, 4);
    for(int i = 5; i < 30; i++)
        gen(format("%02d.in", i), 3, 5, 25);
    for(int i = 30; i < 35; i++)
        gen(format("%02d.in", i), 6, 100, 10000);
    for(int i = 35; i < 40; i++)
        gen(format("%02d.in", i), 101, 500, 250000);
    const int samples[2] = {6, 8};
    for(int i = 0; i < 2; i++) {
        string command = format("cat sample-%d.in >%02d.in", i+1, samples[i]);
        int code = system(command.c_str());
        cerr << "code = " << code << '\n';
    }
    for(int i = 0; i < 40; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        int code = system(command.c_str());
        cerr << format("testdata = %d, code = %d", i, code) << '\n';
    }
}

