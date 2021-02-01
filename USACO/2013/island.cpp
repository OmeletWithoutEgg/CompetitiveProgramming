#include <bits/stdc++.h>
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ... args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}

using namespace std;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
const int N = 55, inf = 1e9;

int R, C;
string s[N];
int enc(int x, int y) {
    return x * C + y;
}
char at(int i) {
    int x = i / C, y = i % C;
    return s[x][y];
}
vector<int> neighbors(int i) {
    const int dx[4] = {1, 0, -1, 0};
    const int dy[4] = {0, 1, 0, -1};
    int x = i / C, y = i % C;
    vector<int> res;
    for(int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if(nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
        res.emplace_back(enc(nx, ny));
    }
    return res;
}
bool vis[N*N];
int grp[N*N];
int dis[15][N*N];
queue<int> q[15];
void dfs(int r, int i) {
    q[r].push(i);
    dis[r][i] = 0;
    grp[i] = r;
    vis[i] = true;
    debug(r, i);
    for(int j: neighbors(i))
        if(at(j) == 'X' && !vis[j])
            dfs(r, j);
}
int dd[15][15];
int dp[15][1<<15];
signed main() {
#ifndef local
    assert( freopen("island.in", "r", stdin) && freopen("island.out", "w", stdout) );
#endif
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> R >> C;
    for(int i = 0; i < R; i++)
        cin >> s[i];
    memset(dis, -1, sizeof dis);
    int cnt = 0;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            if(s[i][j] == 'X' && !vis[enc(i, j)]) {
                dfs(cnt++, enc(i, j));
            }
        }
    }
    for(int i = 0; i < cnt; i++)
        for(int j = 0; j < cnt; j++)
            dd[i][j] = inf;
    for(int c = 0; c < cnt; c++) {
        auto &Q = q[c];
        while(!Q.empty()) {
            int i = Q.front(); Q.pop();
            for(int j: neighbors(i)) {
                if(at(j) != '.' && dis[c][j] == -1)
                    dis[c][j] = dis[c][i] + 1, Q.push(j);
            }
        }
        for(int i = 0; i < R*C; i++) if(dis[c][i] != -1 && at(i) == 'X') {
            debug(i, grp[i]);
            dd[c][grp[i]] = min(dd[c][grp[i]], dis[c][i] - (grp[i] != c));
        }
        for(int i = 0; i < R*C; i++) cerr << dis[c][i] << " \n"[i%C==C-1];
    }
    for(int i = 0; i < cnt; i++)
        for(int j = 0; j < cnt; j++)
            cerr << dd[i][j] << (j+1==cnt ? '\n' : ' ');
    cerr << '\n';
    int best = inf;
    for(int i = 0; i < cnt; i++) for(int s = 0; s < (1<<cnt); s++) dp[i][s] = inf;
    min_heap<tuple<int,int,int>> pq;
    for(int i = 0; i < cnt; i++) {
        dp[i][1<<i] = 0;
        pq.emplace(0, i, 1<<i);
    }
    while(!pq.empty()) {
        auto [d, i, s] = pq.top(); pq.pop();
        if(dp[i][s] != d) continue;
        for(int j = 0; j < cnt; j++) {
            if(dp[j][s | (1<<j)] > dp[i][s] + dd[i][j]) {
                dp[j][s | (1<<j)] = dp[i][s] + dd[i][j];
                pq.emplace(dp[j][s | (1<<j)], j, s | (1<<j));
            }
        }
        if(s == (1<<cnt)-1)
            best = min(best, dp[i][s]), debug(i, s, dp[i][s]);
    }
    cout << best << '\n';
}
