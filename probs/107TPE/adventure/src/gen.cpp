#include "jngen.h"
#include <iostream>
#include <queue>
#include <cassert>
using namespace std;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
const int inf = 1e9;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

ostream & operator<<(ostream &O, pair<int,int> p) {
    return O << p.first << ' ' << p.second;
}

vector<pair<int,int>> genPath(int n, int m, function<int(void)> randomWeight, function<int(int,int)> heuristic) {
    // assert(n * m <= 5e4);
    // O(|path| * log) ?
    vector<int> dis(n*m, inf), prv(n*m, -1);
    auto neighbors = [n, m](int p) -> vector<int> {
        int x = p / m, y = p % m;
        const int dx[4] = {1, 0, -1, 0};
        const int dy[4] = {0, 1, 0, -1};
        Array res;
        for(int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            res.emplace_back(nx * m + ny);
        }
        return res.shuffled();
    };
    auto [S, T] = rnd.nextp(n*m, dpair);
    cerr << "Generating path on " << n << " x " << m << " grid.\n";
    cerr << "src: (" << S/m << ',' << S%m << ") / dest: (" << T/m << ',' << T%m << ")\n";

    // random A* (?)
    auto H = [T, m, &heuristic](int p) {
        int tx = T / m, ty = T % m;
        int px = p / m, py = p % m;
        int dx = (tx - px), dy = (ty - py);
        return heuristic(dx, dy);
    };
    min_heap<pair<int,int>> pq;
    dis[S] = 0;
    pq.emplace(H(S), S);
    int cnt = 0;
    while(!pq.empty()) {
        auto [d, cur] = pq.top(); pq.pop();
        // cerr << d << ' ' << cur << '\n';
        for(int nxt: neighbors(cur)) {
            if(dis[nxt] == inf) {
                prv[nxt] = cur;
                dis[nxt] = dis[cur] + randomWeight();
                pq.emplace(dis[nxt] + H(nxt), nxt);
            }
        }
    }

    assert(dis[T] < inf && prv[T] != -1);

    vector<pair<int,int>> res;
    for(auto X = T; X != S; X = prv[X])
        res.emplace_back(X / m, X % m);
    res.emplace_back(S / m, S % m);
    reverse(res.begin(), res.end());
    /*
    Drawer d;
    d.setFill("black");
    for(auto p: res)
        d.circle(p, 0.1);
    d.dumpSvg("grid.svg");
    */
    if(res.size() < 3)
        return genPath(n, m, randomWeight, heuristic);
    cerr << "complete.\n";
    return res;
}

void genSmall(string filename, int minn, int maxn) {
    int n = rnd.next(minn, maxn);
    int m = rnd.next(minn, maxn);
    auto path = genPath(n, m, [](){ return rnd.next(-500, 2000); }, [](int dx, int dy){ return (abs(dx) + abs(dy) + 1) * 10; });
    auto S = path.front();
    auto T = path.back();

    ofstream fout(filename);
    fout << n << ' ' << m << '\n';
    fout << S << ' ' << T << '\n';
    fout << path.size() - 2 << '\n';
    for(int i = 1; i+1 < path.size(); i++) {
        int w = rnd.next(0, n*m*2);
        fout << path[i] << ' ' << w << '\n';
    }
    fout.close();
}

void gen(string filename, int minn, int maxn, int maxc) {
    int n = rnd.next(minn, maxn);
    int m = rnd.next(minn, maxn);
    auto path = genPath(n, m, [](){ return rnd.next(2500, 3000); }, [](int dx, int dy){ return (abs(dx) + abs(dy) + 1) * 2500; });
    auto S = path.front();
    auto T = path.back();

    vector<vector<int>> weight(n, vector<int>(m, -1));
    auto chmin = [](int &x, int v) {
        if(x == -1 || x > v)
            x = v;
    };

    for(int i = 1; i+1 < path.size(); i++) {
        auto [x, y] = path[i];
        chmin(weight[x][y], rnd.wnext(maxc, 3));
    }

    for(int p: Array::id(n*m).choice(rnd.wnext(n*m, 10))) {
        int x = p / m, y = p % m;
        chmin(weight[x][y], rnd.next(maxc));
    }

    weight[S.first][S.second] = -1;
    weight[T.first][T.second] = -1;

    vector<tuple<int,int,int>> points;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(weight[i][j] != -1)
                points.emplace_back(i, j, weight[i][j]);

    ofstream fout(filename);
    fout << n << ' ' << m << '\n';
    fout << S << ' ' << T << '\n';
    fout << points.size() << '\n';
    for(auto [a, b, c]: points)
        fout << a << ' ' << b << ' ' << c << '\n';
    fout.close();
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    // genPath(1000, 1000, [](){ return rnd.next(2500, 3000); }, [](int dx, int dy){ return (abs(dx) + abs(dy) + 1) * 2500; });
    string prefix = getOpt("o");

    for(int i = 0; i < 10; i++)
        genSmall(prefix + format("%02d.in", i), 1, 10);
    for(int i = 10; i < 20; i++)
        gen(prefix + format("%02d.in", i), 5, 100, 1000);
    for(int i = 20; i < 30; i++)
        gen(prefix + format("%02d.in", i), 5, 1000, 1000000000);
}
