#include <bits/stdc++.h>
using namespace std;
#define debug(x) std::cerr<<#x<<" = "<<x<<'\n'

#define TIME Timer __timer(__PRETTY_FUNCTION__)
class Timer {
private:
    std::string title;
    chrono::high_resolution_clock::time_point start;
public:
    Timer(std::string t) :
        title(t), start(chrono::high_resolution_clock::now()) {}
    ~Timer() {
        auto finish = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
        double ms = double(duration) * 0.001;
        std::cerr << "Timer: " << title << " takes " << ms << " ms to finish.\n";
    }
};

int modpow(int e, int p, int mod) {
    int r = 1;
    while(p) {
        if(p & 1) r = 1LL*r*e%mod;
        e = 1LL*e*e%mod;
        p >>= 1;
    }
    return r;
}
signed main() {
    TIME;
    int n, mod;
    cin >> n >> mod;
    vector<int> v(n);
    vector<vector<int>> A(n, vector<int>(n));
    for(int i = 0; i < n; i++) cin >> v[i];
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> A[j][i];
    // Ax = v, solve x
    bool swapped = false;
    for(int k = 0; k < n; k++) {
        if(A[k][k] == 0) {
            swapped = true;
            int t = k;
            for(int i = k+1; i < n; i++) if(A[i][k] > A[t][k]) t = i;
            for(int j = 0; j < n; j++) swap(A[k][j], A[t][j]);
            swap(v[t], v[k]);
        }
        assert(A[k][k]);
        for(int i = 0; i < n; i++) if(i != k) {
            int r = 1LL * (mod - A[i][k]) * modpow(A[k][k], mod-2, mod) % mod;
            for(int j = 0; j < n; j++) A[i][j] = (A[i][j] + 1LL * r * A[k][j]) % mod;
            v[i] = (v[i] + 1LL * r * v[k]) % mod;
        }
    }
    debug(swapped);
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) assert(i == j ? A[i][j] > 0 : A[i][j] == 0);
    for(int i = 0; i < n; i++) cout << 1LL * v[i] * modpow(A[i][i], mod-2, mod) % mod << (i+1==n ? '\n' : ' ');
}
