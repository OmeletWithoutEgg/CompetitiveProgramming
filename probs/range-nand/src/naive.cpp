#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(a) a.begin(), a.end()

using namespace std;

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count)

#ifdef wiwihorz
#define print(a...) cerr << "Line " << __LINE__, kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2>void kout(T1 a, T2 ... e){cerr<<a<<" ",kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif

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
namespace solver {
    int C, n;
    int nand(int x, int y) {
        const int mask = (1 << C) - 1;
        int ret = ~(x & y);
        return ret & mask;
    }
    vector<int> a;
    void init_(int _n, int _c) {
        n = _n, C = _c;
        a.assign(n + 1, 0);
    }
    int query(int l, int r) {
        int cur = a[l];
        rep(i, l + 1, r) cur = nand(cur, a[i]);
        return cur;
    }
};
using namespace solver;
signed main() {
    TIME;
    ios::sync_with_stdio(false), cin.tie(0);
    int n, q, c;
    cin >> n >> q >> c;
    init_(n, c);
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, q) {
        int tp, x, y;
        cin >> tp >> x >> y;
        if(tp == 1) cout << query(x, y) << "\n";
        else a[x] = y;
    }
    return 0;
}


