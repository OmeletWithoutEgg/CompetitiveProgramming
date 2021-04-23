// #define _GLIBCXX_DEBUG
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#ifdef local
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define pary(a...) danb(#a, a)
#define debug(a...) qqbx(#a, a)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\033[1;32m(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\033[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\033[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\033[0m\n";
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#define pary(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define pb emplace_back

using namespace std;
using ll = int_fast64_t;
using ld = long double;
template <typename T> using max_heap = priority_queue<T, vector<T>, less<T>>;
const int maxn = 200025, maxq = 100025, inf = 1e9;

/*
struct Fraction {
    ll a, b;
    Fraction(ll _a = 0, ll _b = 1) : a(_a), b(_b) {
        if (b < 0)
            b = -b, a = -a;
        if (b == 0)
            a = (a == 0 ? 0 : (a < 0 ? -1 : 1));
        ll g = __gcd(a, b);
        if (g < 0) g = -g;
        a /= g;
        b /= g;
    }
    friend Fraction operator+(const Fraction &lhs, const Fraction &rhs) {
        return { lhs.a * rhs.b + rhs.a * lhs.b, lhs.b * rhs.b };
    }
    friend Fraction operator-(const Fraction &lhs, const Fraction &rhs) {
        return { lhs.a * rhs.b - rhs.a * lhs.b, lhs.b * rhs.b };
    }
    friend Fraction operator*(const Fraction &lhs, const Fraction &rhs) {
        return { lhs.a * rhs.a, lhs.b * rhs.b };
    }
    friend Fraction operator/(const Fraction &lhs, const Fraction &rhs) {
        return { lhs.a * rhs.b, lhs.b * rhs.a };
    }
#define REFOP(type) Fraction & operator type##=(const Fraction &rhs) { return *this = *this type rhs, *this; }
    REFOP(+) REFOP(-) REFOP(*) REFOP(/)
    Fraction operator-() const { return { -a, b }; }

    friend bool operator<(const Fraction &x, const Fraction &y) {
        if (x.b == 0 && y.b == 0)
            return x.a < y.a;
        if (x.b == 0 || y.b == 0) {
            if (x.b == 0)
                return x.a == -1;
            else
                return y.a == 1;
        }
        return x.a * y.b < y.a * x.b;
    }
    friend bool operator>(const Fraction &x, const Fraction &y) { return y < x; }
    friend bool operator>=(const Fraction &x, const Fraction &y) { return !(x < y); }
    friend bool operator<=(const Fraction &x, const Fraction &y) { return !(y < x); }
    friend bool operator==(const Fraction &x, const Fraction &y) { return !(x < y) && !(y < x); }
    friend bool operator!=(const Fraction &x, const Fraction &y) { return (x < y) || (y < x); }

    friend istream & operator>>(istream &I, Fraction &f) {
        ll x;
        I >> x;
        f = x;
        return I;
    }
    friend ostream & operator<<(ostream &O, Fraction f) {
        return O << f.a / ld(f.b);
    }
};

*/

const ld eps = 1e-4;
struct Fraction {
    ld x;
    Fraction() : x() {}
    template <typename U> Fraction(U u) : x(u) {}
    ld operator()() const { return x; }
#define REFOP(type) Fraction & operator type(const Fraction &rhs){ return x type rhs.x, *this; }
    REFOP(+=) REFOP(-=) REFOP(*=) REFOP(/=)
#define VALOP(type) friend Fraction operator type(const Fraction &a, const Fraction &b){ return a.x type b.x; }
    VALOP(+) VALOP(-) VALOP(*) VALOP(/)
    Fraction operator-() { return -x; }
#define CMPOP(caneq, type) friend bool operator type(const Fraction &a, const Fraction &b) { \
        return abs(a.x - b.x) < eps ? caneq : a.x type b.x; \
    }
    CMPOP(false, <) CMPOP(false, >) CMPOP(true, ==) CMPOP(true, <=) CMPOP(true, >=) CMPOP(false, !=)
    friend istream & operator>>(istream &I, Fraction &f) {
        return I >> f.x;
    }
    friend ostream & operator<<(ostream &O, Fraction f) {
        return O << f.x;
    }
};
// using Fraction = ld;

struct Point {
    Fraction x, y;
    friend bool operator<(const Point &a, const Point &b) {
        int qa = (a.y == 0 ? (a.x > 0 ? 0 : 2) : (a.y > 0 ? 1 : 3));
        int qb = (b.y == 0 ? (b.x > 0 ? 0 : 2) : (b.y > 0 ? 1 : 3));
        if (qa != qb)
            return qa < qb;
        return a.x * b.y > b.x * a.y;
    }
    Point operator-() {
        return { -x, -y };
    }
    friend int ori(Point a, Point b, Point c) {
        b.x -= a.x, b.y -= a.y;
        c.x -= a.x, c.y -= a.y;
        Fraction f1 = b.x * c.y;
        Fraction f2 = c.x * b.y;
        return f1 == f2 ? 0 : (f1 < f2 ? -1 : 1);
    }
    friend ostream & operator<<(ostream &O, Point p) {
        return O << '(' << p.x << ',' << p.y << ')';
    }
};

struct Line {
    int vert;
    Fraction a, b; // ax+b
    Line() {}
    Line(Point A, Point B) {
        if (A.x != B.x) {
            a = (A.y - B.y) / (A.x - B.x);
            b = A.y - A.x * a;
            vert = 0;
        } else {
            assert(A.y != B.y);
            a = 0;
            b = A.x;
            vert = 1;
        }
    }
    friend pair<Fraction,Fraction> operator&(const Line &l1, const Line &l2) {
        if (l1.vert || l2.vert) {
            if (l1.vert && l2.vert) {
                return { -7122, -7122 };
            }
            assert(!l1.vert || !l2.vert);
            Fraction x = (l1.vert ? l1.b : l2.b);
            Fraction y = (l1.vert ? l2.a * x + l2.b : l1.a * x + l1.b);
            return { x, y };
        }
        if (l1.a == l2.a) {
            return { -7122, -7122 };
        }
        // l1.a * x + l1.b = l2.a * x + l2.b
        Fraction x = (l2.b - l1.b) / (l1.a - l2.a);
        Fraction y = l1.a * x + l1.b;
        return { x, y };
    }
    friend bool operator<(const Line &lhs, const Line &rhs) {
        if (lhs.vert != rhs.vert) return lhs.vert < rhs.vert;
        return lhs.a < rhs.a;
    }
    friend ostream & operator<<(ostream &O, const Line &L) {
        return O << "y = " << L.a << "x + " << L.b;
    }
};

struct ConvexHull : vector<Point> {
    ConvexHull (iterator l, iterator r) {
        if (r - l <= 2) {
            for (auto it = l; it != r; ++it) push_back(*it);
            return;
        }
        vector<Point> L, U;
        for (auto it = l; it != r; ++it) {
            while (L.size() >= 2 && ori(L.rbegin()[1], L.rbegin()[0], *it) <= 0) L.pop_back();
            L.emplace_back(*it);
        }
        reverse(l, r);
        for (auto it = l; it != r; ++it) {
            while (U.size() >= 2 && ori(U.rbegin()[1], U.rbegin()[0], *it) <= 0) U.pop_back();
            U.emplace_back(*it);
        }
        reverse(l, r);
        L.pop_back();
        U.pop_back();
        L.insert(L.end(), U.begin(), U.end());
        // for(auto p: U) L.pb(p);
        assign(L.begin(), L.end());
    }
    friend pair<Fraction, Fraction> commonTangent(ConvexHull A, ConvexHull B) {
        debug(A.size(), B.size());
        rotate(B.begin(), max_element(B.begin(), B.end(), [](Point a, Point b){
            return a.x < b.x;
        }), B.end());
        bool foundMx = false;
        bool foundMn = false;
        Line mn, mx;
        for (int i = 0, j = 0; i < A.size(); i++) {
            while (j+1 < B.size() && ori(A[i], B[j], B[j+1]) >= 0) ++j;
            debug(i, j);
            if (foundMx)
                mx = max(mx, Line(A[i], B[j]));
            else
                mx = Line(A[i], B[j]), foundMx = true;
        }

        reverse(A.begin() + 1, A.end());
        reverse(B.begin() + 1, B.end());

        for (int i = 0, j = 0; i < A.size(); i++) {
            while (j+1 < B.size() && ori(A[i], B[j], B[j+1]) <= 0) ++j;
            if (foundMn)
                mn = min(mn, Line(A[i], B[j]));
            else
                mn = Line(A[i], B[j]), foundMn = true;
        }
        debug(mn.a, mn.b, mx.a, mx.b);
        if (!(mn < mx)) {
            assert(mn.b == mx.b);
            auto dist = [&](Point p){
                Fraction dx = p.x - B[0].x;
                Fraction dy = p.y - B[0].y;
                return dx*dx+dy*dy;
            };
            auto it = min_element(A.begin(), A.end(), [&](Point a, Point b){ return dist(a) < dist(b); });
            return { it->x, it->y };
        }
        auto p = mx & mn;
        debug(p.first, p.second);
        return p;
    }
};

bool check(vector<Point> p, Fraction x, Fraction y) {
    int n = p.size();
    for (int i = 0; i < n; i++)
        p[i].x -= x, p[i].y -= y;
    int origin = 0;
    for (int i = 0; i < n; i++)
        if (p[i].x == 0 && p[i].y == 0) {
            if (i != n-1)
                swap(p[i], p[n-1]);
            origin = 1;
            --n;
            p.pop_back();
            break;
        }
    sort(all(p));
    for (int i = 0; i < n; i++) {
        Point L = p[i];
        Point R = -p[i];
        int l1 = lower_bound(all(p), L) - p.begin();
        int l2 = upper_bound(all(p), L) - p.begin();
        int r1 = lower_bound(all(p), R) - p.begin();
        int r2 = upper_bound(all(p), R) - p.begin();

        int lcnt = l2 - l1;
        int rcnt = r2 - r1;
        int up = r1 >= l2 ? r1 - l2 : r1 - l2 + n;
        int dn = l1 >= r2 ? l1 - r2 : l1 - r2 + n;

        if (up + lcnt > dn + rcnt + origin || dn + lcnt > up + rcnt + origin) {
            debug(i, up, lcnt, rcnt, up, dn);
            return false;
        }
    }
    return true;
}

void solve() {
    int n;
    cin >> n;
    // if (n > 10 || n % 2 == 1) exit(3);
    vector<Point> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i].x >> p[i].y;

    if (n % 2 == 1) {
        vector<Fraction> xs, ys;
        xs.reserve(n), ys.reserve(n);
        for (int i = 0; i < n; i++) xs.emplace_back(p[i].x);
        for (int i = 0; i < n; i++) ys.emplace_back(p[i].y);
        int half = n / 2;
        nth_element(xs.begin(), xs.begin() + half, xs.end());
        nth_element(ys.begin(), ys.begin() + half, ys.end());
        if (check(p, xs[half], ys[half]))
            cout << xs[half] << ' ' << ys[half] << '\n';
        else
            cout << "x\n";
    } else {
        sort(all(p), [](Point a, Point b){ return a.x != b.x ? a.x < b.x : a.y < b.y; });
        int half = n / 2;
        ConvexHull L(p.begin(), p.begin()+half), R(p.begin()+half, p.end());

        pary(all(L));
        pary(all(R));

        auto [x, y] = commonTangent(L, R);
        if (check(p, x, y))
            cout << x << ' ' << y << '\n';
        else
            cout << "x\n";
    }
}
signed main() {
    cout << fixed << setprecision(10);
    cerr << fixed << setprecision(10);
    ios_base::sync_with_stdio(0), cin.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
}
