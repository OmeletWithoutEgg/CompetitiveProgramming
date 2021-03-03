#include <bits/stdc++.h>

using namespace std;
const int maxn = 500025;

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

struct Point {
    int x, y;
    friend bool operator<(const Point &a, const Point &b) {
        int qa = (a.y == 0 ? (a.x > 0 ? 0 : 2) : (a.y > 0 ? 1 : 3));
        int qb = (b.y == 0 ? (b.x > 0 ? 0 : 2) : (b.y > 0 ? 1 : 3));
        if (qa != qb) return qa < qb;
        int64_t C = 1LL * a.x * b.y - 1LL * b.x * a.y;
        return C > 0;
    }
};

signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    map<Point, int64_t> mp;
    int64_t sum = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        if (x < 0 || (x == 0 && y < 0))
            x = -x, y = -y;
        mp[Point{x, y}] += w;
        sum += w;
    }
    int64_t mn = 0, mx = 0;
    for (auto [_, w]: mp) {
        mx = max<int64_t>(0, mx + w);
        mn = min<int64_t>(0, mn + w);
        ans = max({ ans, mx, sum - mn });
    }
    cout << ans << '\n';
}
