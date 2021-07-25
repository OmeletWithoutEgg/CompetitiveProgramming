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

using namespace std;
using ll = long long;

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

const int maxn = 50025, K = 60;
vector<tuple<int,int,int,int,int>> g[maxn];
int up[maxn][20][K];
int dn[maxn][20][K];
int pa[maxn][20];
int dep[maxn];
void dfs(int src) {
    vector<int> stk;
    stk.emplace_back(src);
    while (!stk.empty()) {
        int i = stk.back(); stk.pop_back();
        for (auto [j, p, a, b, w]: g[i]) {
            if (j == pa[i][0]) continue;
            dep[j] = dep[i] + 1;
            pa[j][0] = i;
            for (int r = 0; r < K; r++) {
                dn[j][0][r] = (a - r + K) % p + w;
                up[j][0][r] = (b - r + K) % p + w;
            }
            stk.emplace_back(j);
        }
    }
}
void merge_doubling(int result[], int a[], int b[]) {
    for (int r = 0; r < K; r++) {
        result[r] = a[r] + b[(r + a[r]) % K];
    }
}
int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    int dif = dep[a] - dep[b];
    for (int i = 0; i < 20; i++) if (dif >> i & 1) a = pa[a][i];
    if (a == b) return a;
    for (int i = 19; i >= 0; i--) {
        if (pa[a][i] != pa[b][i])
            a = pa[a][i], b = pa[b][i];
    }
    return pa[a][0];
}
int query(int a, int b, int r) {
    int c = lca(a, b);
    int da = dep[a] - dep[c];
    int db = dep[b] - dep[c];
    int ans = 0;
    for (int i = 0; i < 20; i++) if (da >> i & 1) {
        ans += up[a][i][r];
        r = (r + up[a][i][r]) % K;
        a = pa[a][i];
    }
    vector<pair<int,int>> tmp;
    for (int i = 0; i < 20; i++) if (db >> i & 1) {
        tmp.emplace_back(b, i);
        b = pa[b][i];
    }
    reverse(tmp.begin(), tmp.end());
    for (auto [b, i]: tmp) {
        ans += dn[b][i][r];
        r = (r + dn[b][i][r]) % K;
    }
    --ans;
    return ans;
}
signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v, w, a, b, p;
        cin >> u >> v >> w >> a >> b >> p;
        ++w;
        g[u].emplace_back(v, p, a, b, w);
        g[v].emplace_back(u, p, b, a, w);
    }
    dfs(1);
    pa[1][0] = 1;
    for (int L = 1; L < 20; L++) {
        for (int i = 1; i <= n; i++) {
            pa[i][L] = pa[pa[i][L-1]][L-1];
            merge_doubling(dn[i][L], dn[pa[i][L-1]][L-1], dn[i][L-1]);
            merge_doubling(up[i][L], up[i][L-1], up[pa[i][L-1]][L-1]);
        }
    }
    while (q--) {
        int h, m, s, t;
        cin >> h >> m >> s >> t;
        cout << query(s, t, m) << '\n';
    }
}
