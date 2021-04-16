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
using ll = int64_t;
template <typename T> using max_heap = priority_queue<T, vector<T>, less<T>>;
const int maxn = 500025, maxq = 100025;
const ll INF = 3e18;

struct Point {
    int x, y, id;
} p[maxn];
int u[maxn];

void buildConvexHull(vector<int> &v) {
    static const auto check = [](int a, int b, int c) {
        ll x1 = p[b].x - p[a].x, y1 = p[b].y - p[a].y;
        ll x2 = p[c].x - p[b].x, y2 = p[c].y - p[b].y;
        return x1 * y2 - x2 * y1 >= 0;
    };
    size_t j = 0;
    for (size_t i = 0; i < v.size(); i++) {
        while (j >= 2 && check(v[j-2], v[j-1], v[i]))
            --j;
        v[j++] = v[i];
    }
    v.resize(j);
}

tuple<ll,int,int> queryConvexHull(vector<int> &v, int w, int h) {
    tuple<ll,int,int> ans(-INF, 0, -1);
    if (v.empty()) return ans;
    auto f = [&](int i) {
        auto [x, y, id] = p[i];
        return tuple<ll,int,int>(1LL * w * y - 1LL * h * x, x, id);
    };
    while (v.size() >= 2 && f(v.rbegin()[0]) <= f(v.rbegin()[1])) v.pop_back();
    return f(v.back());
}

struct Segtree {
    int n;
    vector<int> st[maxn * 2];
    void build(int _n) {
        n = _n;
        for (int i = 0; i < n; i++)
            st[i+n].push_back(i);
        for (int i = n-1; i > 0; i--) {
            st[i].resize(st[i<<1].size() + st[i<<1|1].size());
            merge(all(st[i<<1]), all(st[i<<1|1]), st[i].begin(), [](int a, int b){ return a < b; });
            buildConvexHull(st[i]);
        }
    }
    int query(int l, int r, int w, int h) {
        tuple<ll,int,int> res(-INF, 0, -1);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, queryConvexHull(st[l++], w, h));
            if (r & 1) res = max(res, queryConvexHull(st[--r], w, h));
        }
        return get<2>(res);
    }
} sgt;

struct Query {
    int l, r, w, h;
    int qid;
} qs[maxq];

int ans[maxq];

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> p[i].x >> p[i].y, p[i].id = i+1;
    sort(p, p+n, [](Point a, Point b){ return a.x < b.x; });

    {
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (!i || p[i].x != p[i-1].x) {
                p[j++] = p[i];
            } else if (p[j-1].y < p[i].y) {
                p[j-1] = p[i];
            }
        }
        n = j;
    }
    for (int i = 0; i < n; i++) u[i] = p[i].x;

    sgt.build(n);

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, w, h;
        cin >> a >> w >> h;
        int l = lower_bound(u, u+n, a) - u;
        int r = lower_bound(u, u+n, a+w+1) - u;
        qs[i] = { l, r, w, h, i };
    }
    sort(qs, qs+q, [](Query a, Query b) {
        return 1LL * a.w * b.h > 1LL * a.h * b.w;
    });
    for (int i = 0; i < q; i++) {
        auto [l, r, w, h, qid] = qs[i];
        ans[qid] = sgt.query(l, r, w, h);
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}
