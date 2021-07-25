#include <bits/stdc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
#define pary(a...) danb(#a, a)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    if(!cnt) return std::cerr << "\033[1;32m() = ()\033\[0m\n", void();
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\033[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\033[0m\n";
}
#define pb emplace_back

using namespace std;

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

const int maxn = 525, inf = 1e9;

struct KuhnMunkres {
    int n;
    int w[maxn][maxn];
    int match[maxn];
    int lx[maxn], ly[maxn], slack[maxn];
    bool visx[maxn], visy[maxn];
    void addEdge(int a, int b, int c) {
        w[a][b] = c;
    }
    bool dfs(int i, bool aug) {
        if (visx[i]) return false;
        visx[i] = true;
        for (int j = 0; j < n; j++) if (!visy[j]) {
            int d = lx[i] + ly[j] - w[i][j];
            if (d) {
                slack[j] = min(slack[j], d);
            } else {
                visy[j] = true;
                if (match[j] == -1 || dfs(match[j], aug)) {
                    if (aug)
                        match[j] = i;
                    return true;
                }
            }
        }
        return false;
    }
    bool augment() {
        for (int i = 0; i < n; i++) if (!visy[i] && slack[i] == 0) {
            visy[i] = true;
            if (match[i] == -1 || dfs(match[i], false))
                return true;
        }
        return false;
    }
    void relabel() {
        int d = inf;
        for (int i = 0; i < n; i++) if (!visy[i]) d = min(d, slack[i]);
        assert( d != inf );
        for (int i = 0; i < n; i++) if (visx[i]) lx[i] -= d;
        for (int i = 0; i < n; i++) if (visy[i]) ly[i] += d;
        for (int i = 0; i < n; i++) if (!visy[i]) slack[i] -= d;
    }
    void solve() {
        for (int i = 0; i < n; i++) {
            match[i] = -1;
            lx[i] = 0;
            ly[i] = 0;
            for (int j = 0; j < n; j++) lx[i] = max(w[i][j], lx[i]);
        }
        for (int i = 0; i < n; i++) {
            // debug(i);
            fill(visx, visx+n, false);
            fill(visy, visy+n, false);
            fill(slack, slack+n, inf);
            if (dfs(i, true)) continue;
            while (!augment()) relabel();
            fill(visx, visx+n, false);
            fill(visy, visy+n, false);
            dfs(i, true);
        }
        int ans = 0;
        for (int i = 0; i < n; i++)
            ans += w[match[i]][i];
        cout << ans << '\n';
        for (int i = 0; i < n; i++)
            cout << lx[i] << (i+1==n ? '\n' : ' ');
        for (int i = 0; i < n; i++)
            cout << ly[i] << (i+1==n ? '\n' : ' ');

        cerr << ans << '\n';
    }
} KM;
signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    KM.n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c;
            cin >> c;
            KM.addEdge(i, j, c);
        }
    }
    KM.solve();
}
