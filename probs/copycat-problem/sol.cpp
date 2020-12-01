#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll INF = 1e18;

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

signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> p(m+1);
    for(int i = 1; i <= m; i++) cin >> p[i];
    vector<tuple<int,int,int>> a(n);
    for(auto &[d, q, oj]: a) cin >> q >> d >> oj;
    sort(a.begin(), a.end());
    auto cost = [&](int i, int j) -> int {
        int ojI = get<2>(a[i]), ojJ = get<2>(a[j]);
        if(ojI == 0 || ojJ == 0 || ojI != ojJ) return 0;
        return p[ojI];
    };
    vector<ll> dp(n);
    ll best = 0;
    for(int i = 0; i < n; i++) {
        auto [d, q, oj] = a[i];
        dp[i] = q;
        for(int j = 0; j < i; j++) dp[i] = max(dp[i], dp[j] + q - cost(i, j));
        best = max(best, dp[i]);
    }
    cout << best << '\n';
    cerr << best << '\n';
}
