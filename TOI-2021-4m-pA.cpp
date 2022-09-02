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
using ll = long long;
using ld = long double;
const int inf = 1e9;
const ll INF = 1e18;
const int maxn = 300;

template <typename T, typename U> bool chmin(T &t, const U &u) { return t < u ? false : (t=u, true); }
template <typename T, typename U> bool chmax(T &t, const U &u) { return t > u ? false : (t=u, true); }

struct Vec {
    int x, y;
    void rot(Vec &v) {
        int nx = v.y * x - v.x * y;
        int ny = -(v.x * x + v.y * y);
        x = nx, y = ny;
    }
    friend Vec operator-(const Vec &lhs, const Vec &rhs) {
        return { lhs.x - rhs.x, lhs.y - rhs.y };
    }
    friend istream & operator>>(istream &I, Vec &v) {
        return I >> v.x >> v.y;
    }
    ll norm() const {
        return 1LL * x * x + 1LL * y * y;
    }
};

using Polygon = vector<Vec>;
Vec v[maxn];
Polygon P[maxn];

ld intersection(Vec a, Vec b, int x, int init) {
    if (a.x > b.x) swap(a, b);
    if (x < a.x || x > b.x) return init;
    if (a.x == b.x)
        return abs(a.y - init) > abs(b.y - init) ? a.y : b.y;
    return (1LL * a.y * (b.x - x) + 1LL * b.y * (x - a.x)) / ld(b.x - a.x);
}
pair<ld,ld> calc(Polygon A, Polygon B, Vec v) {
    if (v.norm() != 0) {
        for (auto &p: A) p.rot(v);
        for (auto &p: B) p.rot(v);
        // fix A, and rotate s.t. B moving down with velocity (0, -1)
    }

    vector<int> xs;
    for (auto p: A) xs.push_back(p.x);
    for (auto p: B) xs.push_back(p.x);
    sort(all(xs)), xs.erase(unique(all(xs)), xs.end());
    pary(all(xs));
    ld lt = inf, rt = -inf;
    for (int x: xs) {
        ld la = inf, ra = -inf;
        ld lb = inf, rb = -inf;
        for (int i = 0; i < A.size(); i++) {
            int j = i ? i-1 : A.size() - 1;
            chmin(la, intersection(A[i], A[j], x, inf));
            chmax(ra, intersection(A[i], A[j], x, -inf));
        }
        for (int i = 0; i < B.size(); i++) {
            int j = i ? i-1 : B.size() - 1;
            chmin(lb, intersection(B[i], B[j], x, inf));
            chmax(rb, intersection(B[i], B[j], x, -inf));
        }
        chmin(lt, lb - ra);
        chmax(rt, rb - la);
    }
    debug(lt, rt);
    if (lt > rt || rt < 0)
        return { inf, -inf };
    if (v.norm() == 0)
        return { -inf, inf };
    if (lt < 0) lt = 0;
    lt /= v.norm(), rt /= v.norm();
    return { lt, rt };
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        int sz;
        cin >> sz;
        P[i].resize(sz);
        for (auto &p: P[i]) cin >> p;
    }

    cout << fixed << setprecision(10);
    for (int i = 0; i < n; i++) {
        vector<pair<ld,int>> evt;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                auto [l, r] = calc(P[i], P[j], v[j] - v[i]);
                if (l < r) {
                    evt.emplace_back(l, 1);
                    evt.emplace_back(r, -1);
                }
            }
        }
        sort(all(evt));
        int cnt = 0;
        ld ans = 0;
        for (int l = 0, r = 0; l < evt.size(); l = r) {
            for (r = l; r < evt.size(); r++) {
                if (evt[l].first != evt[r].first) break;
                cnt += evt[r].second;
            }
            if (r == evt.size()) continue;
            if (cnt) {
                ans += evt[r].first - evt[l].first;
            }
        }
        if (ans >= inf)
            cout << "infinity\n";
        else
            cout << ans << '\n';
    }
}
