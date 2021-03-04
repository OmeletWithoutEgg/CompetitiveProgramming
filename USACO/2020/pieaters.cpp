#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#ifdef local
#define debug(a...) qqbx(#a, a)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\n")));
}
#define TAK(STL, BEG, END, OUT) template <typename ...T> std::ostream & operator<<(std::ostream &O, std::STL<T...> v) \
    { O << BEG; int f = 0; for (auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }
TAK(vector, "[", "]", e)
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
const int maxn = 305, maxLg = 10;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
using ll = long long;

ll dp[maxn][maxn];

void chmax(ll &x, ll v) {
    if (x < v) x = v;
}
struct sparseTable2d {
    ll st[maxLg][maxLg][maxn][maxn];
    ll & operator()(int x, int y) {
        return st[0][0][x][y];
    }
    void build(int n) {
        for (int Lx = 0; Lx < maxLg; Lx++) {
            for (int Ly = 0; Ly < maxLg; Ly++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (Lx) {
                            int len = 1 << (Lx-1);
                            chmax(st[Lx][Ly][i][j], max(st[Lx-1][Ly][i][j], (i+len < n ? st[Lx-1][Ly][i+len][j] : 0)));
                        }
                        if (Ly) {
                            int len = 1 << (Ly-1);
                            chmax(st[Lx][Ly][i][j], max(st[Lx][Ly-1][i][j], (j+len < n ? st[Lx][Ly-1][i][j+len] : 0)));
                        }
                    }
                }
            }
        }
    }
    ll query(int lx, int rx, int ly, int ry) {
        int Lx = __lg(rx - lx);
        int Ly = __lg(ry - ly);
        int lenx = 1 << Lx, leny = 1 << Ly;
        debug(lx, rx, Lx);
        return max({
            st[Lx][Ly][lx][ly],
            st[Lx][Ly][lx][ry - leny],
            st[Lx][Ly][rx - lenx][ly],
            st[Lx][Ly][rx - lenx][ry - leny]
        });
    }
} st;
signed main() {
#ifndef local
    assert( freopen("pieaters.in", "r", stdin) && freopen("pieaters.out", "w", stdout) );
#endif // local
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int w, l, r;
        cin >> w >> l >> r;
        st(l-1, r-1) = w;
    }
    st.build(n);
    for (int l = n; l >= 1; l--) {
        for (int r = l; r <= n; r++) {
            for (int j = l; j <= r; j++) {
                dp[l][r] = max(dp[l][r], dp[l][j-1] + dp[j+1][r] + st.query(l-1, j, j-1, r));
            }
            /*
            for (int i = 1; i <= m; i++) {
                if (l > v[i].l || r < v[i].r) continue;
                for (int j = v[i].l; j <= v[i].r; j++)
                    dp[l][r] = max(dp[l][r], dp[l][j-1] + dp[j+1][r] + v[i].w);
                // j >= v[i].l >= l
                // j <= v[i].r <= r
            }
            */
        }
    }
    cout << dp[1][n] << '\n';
}
