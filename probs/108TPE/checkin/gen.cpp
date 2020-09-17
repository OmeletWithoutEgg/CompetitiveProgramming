#include <bits/stdc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
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
vector<pair<int,int>> genGraph(int A, int B, int lim) {
    int type = uniform_int_distribution<int>(0, 2)(rng);
    // complete, cycles, random(sparse), random(dense)
    cerr << "type = " << type << '\n';
    vector<pair<int,int>> res;
    if(type == 0) {
        for(int i = 0; i < A; i++) for(int j = 0; j < B; j++) res.pb(i, j);
    } else if(type == 1) {
        // generate cycles;
        int now = 0;
        while(now < A && now < B) {
            int c = uniform_int_distribution<int>(1, min({A-now, B-now, int(pow(A+B, 0.6))}))(rng);
            for(int i = 0; i < c; i++) {
                int j = i ? i-1 : c-1;
                res.pb(now+i, now+i);
                res.pb(now+i, now+j);
            }
            now += c;
        }
    } else {
        const int n = A+B;
        const double pr[] = {0.7, 1, 1.2, 0.7 * log(n), log(n), 1.2*log(n), 0.5 * n, 0.8 * n};
        const double p = pr[uniform_int_distribution<int>(0, sizeof(pr) / sizeof(double) - 1)(rng)] / n;
        cerr << "p = " << p << '\n';
        for(int i = 0; i < A; i++) for(int j = 0; j < B; j++) if(bernoulli_distribution(p)(rng)) res.pb(i, j);
    }
    vector<int> pa(A), pb(B);
    iota(pa.begin(), pa.end(), 1), iota(pb.begin(), pb.end(), 1);
    shuffle(pa.begin(), pa.end(), rng), shuffle(pb.begin(), pb.end(), rng);
    for(auto &[a, b]: res) a = pa[a], b = pb[b];
    return res;
}
const int maxc = 948712222;
void gen(string filename, int minn, int maxn, int maxk) {
    int A = uniform_int_distribution<int>(minn, maxn)(rng);
    int B = uniform_int_distribution<int>(minn, maxn)(rng);
    int S = uniform_int_distribution<int>(1, maxc)(rng);
    int M = uniform_int_distribution<int>(1, maxc)(rng);
    vector<pair<int,int>> edges = genGraph(A, B, maxk);
    int K = edges.size();
    ofstream fout(filename);
    cerr << A << ' ' << B << ' ' << K << '\n';
    fout << A << ' ' << B << ' ' << S << ' ' << M << ' ' << K << '\n';
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
        /* string command = format("./sol <%02d.in >%02d.out && ./bad <%02d.in >%02d-T.out && diff %02d.out %02d-T.out", i, i, i, i, i, i); */
        int code = system(command.c_str());
        cerr << format("testdata = %d, code = %d", i, code) << '\n';
    }
    /* int code = system("rm *-T.out"); */
    /* cerr << "code = " << code << '\n'; */
}

