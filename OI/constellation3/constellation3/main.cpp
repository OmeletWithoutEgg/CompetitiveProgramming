
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
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
const int mod = 1000000007;
const int inf = 1e9;
const ll INF = 1e18;
const int maxn = 200025;

void chmax(ll &x, ll v) {
    if (x < v) x = v;
}
bool alive[maxn];

int pa[maxn];
int anc(int x) { return x==pa[x] ? x : pa[x]=anc(pa[x]); }
map<int,ll> top[maxn];
ll tag[maxn];
ll dp[maxn];
void join(int a, int b, int h) {
    a = anc(a);
    b = anc(b);
    assert (a != b);
    while (top[a].size() && top[a].begin()->first <= h) {
        chmax(dp[a], top[a].begin()->second + tag[a]);
        top[a].erase(top[a].begin());
    }
    while (top[b].size() && top[b].begin()->first <= h) {
        chmax(dp[b], top[b].begin()->second + tag[b]);
        top[b].erase(top[b].begin());
    }
    ll tmpdp = dp[b] + dp[a];
    tag[a] += dp[b];
    tag[b] += dp[a];
    if (top[a].size() > top[b].size()) {
        for (auto [y, val]: top[b])
            chmax(top[a][y], val + tag[b] - tag[a]);
        swap(top[a], top[b]);
        swap(tag[a], tag[b]);
    } else {
        for (auto [y, val]: top[a])
            chmax(top[b][y], val + tag[a] - tag[b]);
    }
    dp[b] = tmpdp;
    pa[a] = b;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    iota(pa, pa+n, 0);
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int m;
    cin >> m;
    ll tot = 0, ans = 0;
    for (int i = 0; i < m; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        --x;
        chmax(top[x][y], c);
        tot += c;
    }
    map<int, vector<int>> mp;
    for (int i = 0; i < n; i++) mp[A[i]].push_back(i);
    for (const auto &[h, indices]: mp) {
        for (int i: indices) {
            if (i > 0 && alive[i-1]) {
                join(i-1, i, h);
            }
            if (i+1 < n && alive[i+1]) {
                join(i, i+1, h);
            }
            alive[i] = true;
        }
    }
    int root = anc(0);
    for (auto [y, val]: top[root]) chmax(ans, val + tag[root]);
    chmax(ans, dp[root]);
    cout << tot - ans << '\n';
}
