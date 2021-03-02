#include <bits/stdc++.h>

using namespace std;
const int maxn = 100025;

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


using ll = long long;

ll modpow(ll a, ll p, ll m) {
    // a^p % m
    ll res = 1;
    a %= m;
    while (p) {
        if (p & 1)
            res = res * a % m;
        a = a * a % m;
        p >>= 1;
    }
    return res;
}
signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        long long M;
        long long a, b, x1, y1, x2, y2;
        cin >> M >> a >> b >> x1 >> y1 >> x2 >> y2;
        assert(M < (1LL << 31));
        long long m = 1LL * (y2 - y1 + M) * modpow(x2 - x1 + M, M - 2, M) % M;
        long long x3 = (1LL * m * m % M - x1 - x2 + M + M) % M;
        long long y3 = (y2 - 1LL * ((y1 - y2 + M) % M) * ((x2 - x3 + M) % M) % M * modpow(x1 - x2 + M, M - 2, M) % M + M) % M;
        cout << x3 << ' ' << y3 << '\n';
    }
}
