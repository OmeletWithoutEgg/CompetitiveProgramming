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
const int maxn = 100025;

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

void upd(vector<int> &v, int x) {
    v.push_back(x);
    sort(v.rbegin(), v.rend());
    v.erase(unique(v.begin(), v.end()), v.end());
    if (v.size() > 2)
        v.pop_back();
}

struct node {
    vector<int> down, ans;
};

vector<pair<int,int>> g[maxn];

#ifdef local
node dp[maxn];
int dis[maxn], pa[maxn];
vector<int> ord;
void BFS() {
    // local stack too small
    queue<int> q;
    memset(dis, -1, sizeof dis);
    pa[0] = -1, dis[0] = 0, q.push(0);
    while (!q.empty()) {
        int i = q.front(); q.pop();
        ord.push_back(i);
        for (auto [j, w]: g[i]) if (dis[j] == -1) pa[j] = i, dis[j] = dis[i] + 1, q.push(j);
    }
}
#else
node dfs(int i, int p) {
    node res;
    res.down.push_back(0);
    for (auto [j, w]: g[i]) if (j != p) {
        auto r = dfs(j, i);
        for (int a: r.down) for (int b: res.down) upd(res.ans, a + b + w);
        for (int a: r.down) upd(res.down, a + w);
        for (int a: r.ans) upd(res.ans, a);
    }
    return res;
}
#endif // local

signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
#ifdef local
    BFS();
    reverse(ord.begin(), ord.end());
    for (int i: ord) {
        auto &res = dp[i];
        res.down.push_back(0);
        for (auto [j, w]: g[i]) if (j != pa[i]) {
            auto r = dp[j];
            for (int a: r.down) for (int b: res.down) upd(res.ans, a + b + w);
            for (int a: r.down) upd(res.down, a + w);
            for (int a: r.ans) upd(res.ans, a);
        }
    }
    auto res = dp[0].ans;
#else
    auto res = dfs(0, -1).ans;
#endif // local
    cout << res[1] << '\n';
}
