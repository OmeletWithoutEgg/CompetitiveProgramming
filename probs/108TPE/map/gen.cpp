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
vector<int> prs;
void buildPrimes() {
    const int N = 65538;
    vector<int> sv(N);
    for(int i = 2; i < N; i++) {
        if(!sv[i]) prs.push_back(i);
        for(int p: prs) {
            if(i*p >= N) break;
            sv[i*p] = true;
            if(i%p == 0) break;
        }
    }
}
int modpow(int e, int p, int mod) {
    int r = 1;
    while(p) {
        if(p & 1) r = 1LL*r*e%mod;
        e = 1LL*e*e%mod;
        p >>= 1;
    }
    return r;
}
bool independent(const vector<vector<int>> &A, vector<int> b, int mod) {
    int n = b.size();
    for(const vector<int> &v: A) {
        int pos = -1;
        for(int i = 0; i < n; i++) {
            if(v[i] > 0 && b[i] > 0) {
                pos = i;
                break;
            }
        }
        if(pos != -1) {
            int r = 1LL * (mod - b[pos]) * modpow(v[pos], mod-2, mod) % mod;
            for(int i = 0; i < n; i++) b[i] = (b[i] + 1LL * r * v[i]) % mod;
        }
    }
    for(int i = 0; i < n; i++) if(b[i] > 0) return true;
    return false;
}
void gen(string filename, int minn, int maxn) {
    ofstream fout(filename);
    const int n = uniform_int_distribution<int>(minn, maxn)(rng);
    const int mod = prs[uniform_int_distribution<int>(1, prs.size()-1)(rng)]; // does not contain 2
    vector<int> v(n);
    for(int &x: v) x = uniform_int_distribution<int>(0, mod-1)(rng);
    vector<vector<int>> A;
    cerr << n << ' ' << mod << '\n';
    for(int i = 0; i < n; i++) {
        vector<int> b(n);
        int cnt = 0;
        do {
            for(int &x: b) x = uniform_int_distribution<int>(0, mod-1)(rng);
            if(i == 0 && uniform_int_distribution<int>(0, 5)(rng) == 0) b[0] = 0;
            if(cnt++ > 100) cerr<<"Too many attempt!\n", exit(3);
        } while(!independent(A, b, mod));
        A.push_back(b);
    }
    fout << n << ' ' << mod << '\n';
    for(int i = 0; i < n; i++) fout << v[i] << (i+1==n ? '\n' : ' ');
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            fout << A[j][i] << (j+1==n ? '\n' : ' ');
        }
    }
    fout.close();
}
void specialGen(string filename, int n) {
    ofstream fout(filename);
    const int mod = prs[uniform_int_distribution<int>(1, prs.size()-1)(rng)]; // does not contain 2
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    shuffle(p.begin(), p.end(), rng);
    fout << n << ' ' << mod << '\n';
    for(int i = 0; i < n; i++) fout << uniform_int_distribution<int>(0, mod-1)(rng) << (i+1==n ? '\n' : ' ');
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        if(i==p[j] || uniform_int_distribution<int>(0, n*2-1)(rng) == 0) {
            fout << uniform_int_distribution<int>(1, mod-1)(rng) << (j+1==n ? '\n' : ' ');
        } else {
            fout << 0 << (j+1==n ? '\n' : ' ');
        }
    }
    fout.close();
}
signed main() {
    buildPrimes();
    for(int i = 0; i < 5; i++)
        gen(format("%02d.in", i), 2, 2);
    for(int i = 5; i < 10; i++)
        gen(format("%02d.in", i), 3, 3);
    for(int i = 10; i < 20; i++)
        gen(format("%02d.in", i), 1, 100);
    gen("20.in", 100, 100);
    gen("21.in", 100, 100);
    specialGen("08.in", 3);
    specialGen("23.in", 97);
    specialGen("24.in", 100);
    const int samples[3] = {0, 1, 6}, special[2] = {4, 6};
    for(int i = 0; i < 3; i++) {
        string command = format("cat sample-%d.in >%02d.in", i+1, samples[i]);
        int code = system(command.c_str());
        cerr << format("code = %d", code) << '\n';
    }
    for(int i = 0; i < 2; i++) {
        string command = format("cat special-%d.in >%02d.in", i+1, special[i]);
        int code = system(command.c_str());
        cerr << format("code = %d", code) << '\n';
    }
    for(int i = 0; i < 25; i++) {
        string command = format("./sol <%02d.in >%02d.out", i, i);
        int code = system(command.c_str());
        cerr << format("code = %d", code) << '\n';
    }
}

