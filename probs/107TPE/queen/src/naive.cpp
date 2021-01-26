#include <bits/stdc++.h>
#define pb emplace_back
#define all(v) begin(v),end(v)

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

using ld = long double;

struct Line {
    ld a, b; // ax+b
    Line(array<int,2> A, array<int,2> B) {
        a = (A[1] - B[1]) / ld(A[0] - B[0]);
        b = A[1] - A[0] * a;
    }
    friend array<ld,2> operator&(const Line &l1, const Line &l2) {
        // l1.a * x + l1.b = l2.a * x + l2.b
        ld x = (l2.b - l1.b) / ld(l1.a - l2.a);
        ld y = l1.a * x + l1.b;
        return {x, y};
    }
    friend ostream & operator<<(ostream &O, const Line &L) {
        return O << "y = " << L.a << "x + " << L.b;
    }
};

signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    if(n > 4000)
        return cout << "MLE/TLE.\n", 0;
    vector<array<int,2>> v(n);
    for(int i = 0; i < n; i++) for(int j = 0; j < 2; j++) cin >> v[i][j];
    sort(all(v));
    vector<Line> lines;
    for(int i = 0; i < n/2; i++) {
        for(int j = n/2; j < n; j++) {
            lines.pb(v[i], v[j]);
            // cerr << v[i][0] << ',' << v[i][1] << " -- " << v[j][0] << ',' << v[j][1] << ": " << lines.back() << '\n';
        }
    }
    auto [mxit, mnit] = minmax_element(lines.begin(), lines.end(), [](const Line &l1, const Line &l2) { return l1.a < l2.a; });
    auto p = *mxit & *mnit;
    cerr << *mxit << ' ' << *mnit << '\n';
    cout << fixed << setprecision(2);
    cout << p[0] << ' ' << p[1] << '\n';
}
