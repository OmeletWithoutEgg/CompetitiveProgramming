#include <bits/stdc++.h>
#define pb emplace_back

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

/* struct Line { */
/*     int a, b; // y = ax+b */
/*     friend bool operator<(const Line &x, const Line &y) { */
/*         return x.a < y.a; */
/*     } */
/* }; */

vector<array<int,2>> convexHull(vector<array<int,2>> sorted) {
    auto ok = [](array<int,2> a, array<int,2> b, array<int,2> c) -> bool {
        // AB ^ AC
        b[0] -= a[0], b[1] -= a[1];
        c[0] -= a[0], c[1] -= a[1];
        return 1LL * b[0] * c[1] - 1LL * b[1] * c[0] > 0;
    };
    vector<array<int,2>> L, U;
    for(auto p: sorted) {
        while(L.size() >= 2 && ok(L[L.size()-2], L.back(), p)) L.pop_back();
        L.pb(p);
    }
    reverse(sorted.begin(), sorted.end());
    for(auto p: sorted) {
        while(U.size() >= 2 && ok(U[U.size()-2], U.back(), p)) U.pop_back();
        U.pb(p);
    }
    L.pop_back();
    U.pop_back();
    for(auto p: U) L.pb(p);
    return L;
}

signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<array<int,2>> v(n);
    for(int i = 0; i < n; i++) for(int j = 0; j < 2; j++) cin >> v[i][j];
    sort(v.begin(), v.end());
    int h = n / 2;
    auto A = convexHull(vector<array<int,2>>(v.begin(), v.begin() + h));
    auto B = convexHull(vector<array<int,2>>(v.begin() + h, v.end()));
    rotate(B.begin(), max_element(B.begin(), B.end(), [](array<int,2> a, array<int,2> b){
            return a[1] < b[1];
        }), B.end());
    int i = 0, j = 0;
}
