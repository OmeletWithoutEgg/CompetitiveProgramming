#include <bits/stdc++.h>

using namespace std;

const int seed = 7122;
mt19937 rng(seed);
template <typename ...T> string format(const char *F, T ...args) {
    const int B = 1<<10;
    char buf[B] = {};
    sprintf(buf, F, args...);
    return string(buf);
}
template <typename T> T select(vector<pair<double,T>> evt) {
    assert( accumulate(evt.begin(), evt.end(), 0.0, [](double s, pair<double,T> p) { return s + p.first; }) == 1);
    double res = uniform_real_distribution()(rng);
    cerr << "res = " << res << '\n';
    double sum = 0;
    for(auto [p, v]: evt) {
        if(sum <= res && res < sum + p) return v;
        sum += p;
    }
    exit(3);
}
vector<int> fixedSumNumbers(int n, int s) {
    int policy = select<int>({ {0.8, 0}, {0.2, 1} });
    if(policy == 0) {
        // random partition point
        vector<int> p{0, s}, res;
        for(int i = 0; i < n-1; i++) p.emplace_back(uniform_int_distribution<int>(0, s)(rng));
        sort(p.begin(), p.end());
        for(int i = 1; i <= n; i++) res.emplace_back(p[i] - p[i-1]);
        return res;
    } else {
        // random increment
        vector<int> res(n, 0);
        while(s > 0) {
            int pos = uniform_int_distribution<int>(0, n-1)(rng);
            int inc = uniform_int_distribution<int>(1, s)(rng);
            res[pos] += inc;
            s -= inc;
        }
        return res;
    }
}
void gen(string filename, int maxn, int maxm) {
    const int n = uniform_int_distribution<int>(1, maxn)(rng);
    const int m =
        min({n, maxm, uniform_int_distribution<int>(1, select<int>({
            {0.25, maxm}, {0.25, int(2 * ceil(sqrt(maxm)))}, {0.5, 5}
        }))(rng)});
    vector<int> cnt = fixedSumNumbers(m, n - m);
    for(int &x: cnt) ++x; // at least 1
    ofstream fout(filename);
    fout << n << ' ' << m << '\n';
    for(int i = 0; i < m; i++) fout << cnt[i] << '\n';
    fout.close();
    cerr << "Random " << filename << ": ";
    cerr << n << ' ' << m << ' ' << *min_element(cnt.begin(), cnt.end()) << ' ' << *max_element(cnt.begin(), cnt.end()) << '\n';
}
void handMade(string filename, vector<int> v) {
    int n = accumulate(v.begin(), v.end(), 0), m = v.size();
    ofstream fout(filename);
    fout << n << ' ' << m << '\n';
    for(int i = 0; i < m; i++) fout << v[i] << '\n';
    fout.close();

    cerr << "Handmade " << filename << ": ";
    cerr << n << ' ' << m << ' ';
    int first = 0;
    for(int x: v) {
        cerr << (first++ ? ',' : '[') << x;
        if(first >= 15) {
            cerr << "...";
            break;
        }
    }
    cerr << ']' << '\n';
}
void smallHandMade() {
    handMade("10.in", {2, 1, 2});
    handMade("11.in", {2, 2, 2, 2});
    handMade("12.in", {4, 3, 1});
    handMade("13.in", {3, 1, 4});
    handMade("14.in", {1, 4, 3});
    handMade("15.in", {9, 1});
    handMade("16.in", {1, 9});
    handMade("17.in", {1});
    handMade("18.in", {4, 4, 1});
    handMade("19.in", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
}
void bigHandMade() {
    handMade("40.in", vector<int>(99998, 2));
    handMade("41.in", {100000, 7122});
    handMade("42.in", {7122, 100000});
    handMade("43.in", {200000});
    handMade("44.in", {99000, 99009, 10});
    handMade("45.in", {10, 99909, 99000});
    vector<int> inc(600);
    iota(inc.begin(), inc.end(), 1);
    handMade("46.in", inc);
    handMade("47.in", {1, 79999, 79999});
    handMade("48.in", {1, 89999, 79999});
    handMade("49.in", vector<int>(22222, 7));
}
signed main() {
#define FOR(i, l, r) for(int i = l; i < r; i++)
    /*
    FOR(i, 0, 10)
        gen(format("%02d.in", i), 100, 100);
    // [10, 20) is hand-made
    smallHandMade();
    FOR(i, 20, 25)
        gen(format("%02d.in", i), 3000, 3000);
    FOR(i, 25, 30)
        gen(format("%02d.in", i), 2e5, 100);
    FOR(i, 30, 35)
        gen(format("%02d.in", i), 2e5, 3000);
    FOR(i, 35, 40)
        gen(format("%02d.in", i), 2e5, 2e5);
    // [40, 50) is hand-made (big)
    bigHandMade();

    for(int i = 0; i < 50; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        int code = system(command.c_str());
        cerr << command << ' ' << code << '\n';
        if(code) return 3;
    }
    */
    handMade("50.in", {2, 1, 2, 2});
    {
        int code = system("./sol <50.in >50.out");
        cerr << code << '\n';
        if(code) return 3;
    }
    for(int i = 0; i < 50; i++) {
        i=50;
        string command = format("./kev <%02d.in >kev-%02d.out && diff %02d.out kev-%02d.out; rm kev-%02d.out", i, i, i, i, i, i);
        int code = system(command.c_str());
        cerr << command << ' ' << code << '\n';
        // if(code) break;
    }
}
