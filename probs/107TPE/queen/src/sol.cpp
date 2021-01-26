#include <bits/stdc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
#define TAK(args...) std::ostream& operator<<(std::ostream &O, args)
#define NIE(STL, BEG, END, OUT) template <typename ...T> TAK(std::STL<T...> v) \
    { O << BEG; int f=0; for(auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }
NIE(deque, "[", "]", e) ; NIE(vector, "[", "]", e)
NIE(set, "{", "}", e) ; NIE(multiset, "{", "}", e) ; NIE(unordered_set, "{", "}", e)
NIE(map , "{", "}", e.first << ":" << e.second)
NIE(unordered_map , "{", "}", e.first << ":" << e.second)
template <typename ...T> TAK(std::pair<T...> p) { return O << '(' << p.first << ',' << p.second << ')'; }
template <typename T, size_t N> TAK(std::array<T,N> a) { return O << std::vector<T>(a.begin(), a.end()); }
template <typename ...T> TAK(std::tuple<T...> t) {
    return O << "(", std::apply([&O](T ...s){ int f=0; (..., (O << (f++ ? ", " : "") << s)); }, t), O << ")";
}
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    if(!cnt) return std::cerr << "\033[1;32m() = ()\033\[0m\n", void();
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
}
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
    Line(int a, int b) : a(a), b(b) {}
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
    friend bool operator<(const Line &lhs, const Line &rhs) {
        return lhs.a < rhs.a;
    }
    friend ostream & operator<<(ostream &O, const Line &L) {
        return O << "y = " << L.a << "x + " << L.b;
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
            return a[0] < b[0];
        }), B.end());

    debug(A.size(), B.size());

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
    auto p = mx & mn;
    cout << fixed << setprecision(2) << p[0] << ' ' << p[1] << '\n';
    cerr << fixed << setprecision(2) << p[0] << ' ' << p[1] << '\n';
}
