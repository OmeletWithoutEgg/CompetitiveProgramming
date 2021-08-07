#include <bits/stdc++.h>
#ifdef local
#define debug(a...) qqbx(#a, a)
#define pary(a...) danb(#a, a)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\e[1;32m(" << s << ") = ("), ..., (std::cerr << a << (--cnt ? ", " : ")\e[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\e[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\e[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
using namespace std;
const int maxn = 200025;
using ll = long long;


ostream & operator<<(ostream &O, pair<int,int> P) {
    return O << '(' << P.first << ',' << P.second << ')';
}
struct Fenwick {
    int sum[maxn * 2];
    int n;
    void init(int sz) {
        n = sz;
        for (int i = 1; i <= sz; i++) sum[i] = 0;
    }
    void add(int x) {
        for (x = n - x; x <= n; x += x & -x) {
            sum[x] += 1;
        }
    }
    int query(int x) {
        int res = 0;
        for (x = n - x; x > 0; x -= x & -x) {
            res += sum[x];
        }
        return res;
    }
} fwt;

int a[maxn];
vector<int> g[maxn];
bool vis[maxn];
int sz[maxn], mxs[maxn];
vector<int> tmp;
void dfsSize(int i) {
    vis[i] = true;
    sz[i] = 1;
    mxs[i] = 0;
    for (int j: g[i])
        if (!vis[j]) {
            dfsSize(j);
            sz[i] += sz[j];
            mxs[i] = max(mxs[i], sz[j]);
        }
    tmp.push_back(i);
}
// { max weight from cent, sum of weight from cent }
vector<pair<int,ll>> sub, allSub;
void dfsDist(int cid, int i, int mx = 0, ll sum = 0) {
    mx = max(mx, a[i]);
    sum += a[i];
    vis[i] = true;
    sub.emplace_back(mx, sum);
    for (int j: g[i]) {
        if (!vis[j]) {
            dfsDist(cid, j, mx, sum);
        }
    }
}

ll calc(vector<pair<int,ll>> &s, int root) {
    pary(all(s));
    debug(root);
    ll res = 0;
    vector<ll> lisan;
    for (auto [mx, sum]: s) lisan.push_back(sum);
    sort(lisan.begin(), lisan.end());

    sort(s.begin(), s.end());
    fwt.init(lisan.size() + 1);
    for (auto [mx, sum]: s) {
        mx = max(mx, a[root]);
        res += fwt.query(upper_bound(all(lisan), mx * 2 - sum - a[root]) - lisan.begin());
        fwt.add(lower_bound(all(lisan), sum) - lisan.begin());
    }
    return res;
}

ll ans = 0;
void centDecomp(int x) {
    tmp.clear();
    dfsSize(x);
    int N = tmp.size();
    int cent = -1;
    for (int x: tmp) {
        if (max(N - sz[x], mxs[x]) * 2 <= N)
            cent = x;
        vis[x] = false;
    }
    // mx * 2 < sum + a[root] + sum' -> sum' > mx * 2 - sum - a[root]
    // cerr << "cent = " << cent << endl;
    allSub.clear();
    allSub.emplace_back(0, 0);
    vis[cent] = true;
    for (int j: g[cent]) {
        if (!vis[j]) {
            sub.clear();
            dfsDist(j, j);
            ans -= calc(sub, cent);
            for (auto [f, s]: sub) allSub.emplace_back(f, s);
        }
    }
    ans += calc(allSub, cent);
    for (int x: tmp) vis[x] = false;
    vis[cent] = true;
    for (int j: g[cent]) {
        if (vis[j]) continue;
        centDecomp(j);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) g[i].clear();
        for (int i = 1; i < n; i++) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            g[x].emplace_back(y);
            g[y].emplace_back(x);
        }

        for (int i = 0; i < n; i++) vis[i] = false;
        ans = 0;
        centDecomp(0);
        cout << ans << '\n';
    }
}
