#include "jngen.h"
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

using ld = long double;
const int inf = 1e9;

struct Line {
    ld a, b; // ax+b
    array<int,2> s, t;
    Line(int a, int b) : a(a), b(b) {}
    Line(array<int,2> A, array<int,2> B) {
        a = (A[1] - B[1]) / ld(A[0] - B[0]);
        b = A[1] - A[0] * a;
        s = A;
        t = B;
    }
    friend array<ld,2> operator&(const Line &l1, const Line &l2) {
        // l1.a * x + l1.b = l2.a * x + l2.b
        ld x = (l2.b - l1.b) / ld(l1.a - l2.a);
        ld y = l1.a * x + l1.b;
        return {x, y};
    }
    friend bool operator<(const Line &lhs, const Line &rhs) {
        return lhs.a < rhs.a;
    }
    friend ostream & operator<<(ostream &O, const Line &L) {
        return O << "y = " << L.a << "x + " << L.b;
    }
    void draw(Drawer &d) {
        d.segment(s[0], s[1], t[0], t[1]);
    }
};

int ori(array<int,2> a, array<int,2> b, array<int,2> c) {
    // AB ^ AC
    b[0] -= a[0], b[1] -= a[1];
    c[0] -= a[0], c[1] -= a[1];
    long long cross = 1LL * b[0] * c[1] - 1LL * b[1] * c[0];
    return cross ? (cross < 0 ? -1 : 1) : 0;
}
vector<array<int,2>> convexHull(vector<array<int,2>> sorted) {
    vector<array<int,2>> L, U;
    for(auto p: sorted) {
        while(L.size() >= 2 && ori(L[L.size()-2], L.back(), p) <= 0) L.pop_back();
        L.pb(p);
    }
    reverse(sorted.begin(), sorted.end());
    for(auto p: sorted) {
        while(U.size() >= 2 && ori(U[U.size()-2], U.back(), p) <= 0) U.pop_back();
        U.pb(p);
    }
    L.pop_back();
    U.pop_back();
    for(auto p: U) L.pb(p);
    return L;
}
Polygon toPolygon(vector<array<int,2>> &v) {
    Polygon p(v.size());
    for(size_t i = 0; i < v.size(); i++)
        p[i] = {v[i][0], v[i][1]};
    return p;
}

signed main(int argc, char *argv[]) {
    parseArgs(argc, argv);
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
            return a[0] < b[0];
        }), B.end());


    Line mn(inf, 0), mx(-inf, 0);
    for(int i = 0, j = 0; i < A.size(); i++) {
        while(j+1 < B.size() && ori(A[i], B[j], B[j+1]) >= 0) ++j;
        mx = max(mx, Line(A[i], B[j]));
    }

    reverse(A.begin() + 1, A.end());
    reverse(B.begin() + 1, B.end());

    for(int i = 0, j = 0; i < A.size(); i++) {
        while(j+1 < B.size() && ori(A[i], B[j], B[j+1]) <= 0) ++j;
        mn = min(mn, Line(A[i], B[j]));
    }

    string output = getOpt("o");
    Drawer d;
    mx.draw(d);
    mn.draw(d);
    d.setColor("green");
    d.polygon(toPolygon(A));
    d.polygon(toPolygon(B));
    d.dumpSvg(output);
}
