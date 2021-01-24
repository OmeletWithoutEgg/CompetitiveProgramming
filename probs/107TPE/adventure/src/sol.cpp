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

template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
const int inf = 1e9, N = 1000;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m;
int lev[N][N];
int dis[N][N];
signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int xs, ys, xt, yt, k;
    cin >> n >> m >> xs >> ys >> xt >> yt;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++)
        lev[i][j] = dis[i][j] = -1;
    cin >> k;
    for(int i = 0; i < k; i++) {
        int x, y, l;
        cin >> x >> y >> l;
        lev[x][y] = l;
    }
    min_heap<tuple<int,int,int>> pq;
    lev[xs][ys] = lev[xt][yt] = 0;
    pq.emplace(dis[xs][ys] = 0, xs, ys);
    while(!pq.empty()) {
        auto [d, x, y] = pq.top(); pq.pop();
        if(dis[x][y] != d) continue;
        for(int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m || lev[nx][ny] == -1) continue;
            if(dis[nx][ny] == -1 || dis[nx][ny] > max(dis[x][y], lev[nx][ny]))
                pq.emplace(dis[nx][ny] = max(dis[x][y], lev[nx][ny]), nx, ny);
        }
    }
    cout << dis[xt][yt] << '\n';
    cerr << dis[xt][yt] << '\n';
}
