#include <bits/stdc++.h>
#define pb emplace_back
#define all(v) begin(v),end(v)
#define ff first
#define ss second
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
}
#endif // local

using namespace std;
const int N = 1025;

int v[N][N];
int vis[N][N][4];
pair<int,int> ROT(pair<int,int> p, int rot) {
    if(rot == 0) return p;
    if(rot == 1) return {-p.ss, p.ff};
    if(rot == 2) return {-p.ff, -p.ss};
    if(rot == 3) return {p.ss, -p.ff};
    exit(3);
    return {7122, 7122};
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    pair<int,int> center;
    vector<pair<int,int>> blocks;
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for(int j = 1; j <= m; j++) {
            char c = s[j-1];
            if(c == '.') {
                v[i][j] = 1;
            } else if(c == 'o') {
                v[i][j] = 0;
            } else {
                v[i][j] = 1;
                if(c == 'X') {
                    center = {i, j};
                    blocks.pb(i, j);
                } else if(c == 'x') {
                    blocks.pb(i, j);
                }
            }
        }
    }
    auto ok = [&](pair<int,int> p, int rot) -> bool {
        for(auto q: blocks) {
            q.first -= center.first;
            q.second -= center.second;
            q = ROT(q, rot);
            q.first += p.first;
            q.second += p.second;
            if(q.first <= 0 || q.first > n || q.second <= 0 || q.second > m || v[q.first][q.second] == 0) return false;
        }
        return true;
    };
    vector<pair<pair<int,int>,int>> ans;
    queue<pair<pair<int,int>,int>> q;
    q.push({center, 0});
    vis[center.ff][center.ss][0] = true;
    const int dx[3] = {0, 1, 0};
    const int dy[3] = {1, 0, -1};
    while(!q.empty()) {
        auto [pos, rot] = q.front(); q.pop();
        /* ans.pb(pos, rot); */
        for(int c: {1, 3}) {
            if(!vis[pos.ff][pos.ss][(rot+c)%4] && ok(pos, (rot+c)%4)) {
                vis[pos.ff][pos.ss][(rot+c)%4] = true;
                q.push({pos, (rot+c)%4});
            }
        }
        for(int k = 0; k < 3; k++) {
            int x = pos.ff + dx[k], y = pos.ss + dy[k];
            if(!vis[x][y][rot] && ok({x, y}, rot)) {
                vis[x][y][rot] = true;
                q.push({{x, y}, rot});
            }
        }
        pos.ff += 1;
        if(!ok(pos, rot)) {
            pos.ff--;
            ans.pb(pos, rot);
        }
    }
    sort(all(ans));
    for(auto [p, d]: ans) {
        auto [x, y] = p;
        cout << x-1 << ' ' << y-1 << ' ' << d << '\n';
    }
}
