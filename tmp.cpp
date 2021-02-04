#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define pb emplace_back

using namespace std;
const int maxn = 55, mod = 998244353;

const int dx[5] = {1, 0, -1, 0, 0};
const int dy[5] = {0, 1, 0, -1, 0};

int dis[maxn][maxn][maxn];
bool mp[maxn][maxn];
int dir[maxn];
int H, W;
bool valid(int x, int y, int r) {
    return x >= 0 && x < H && y >= 0 && y < W && mp[x][(y+r*dir[x]+W)%W];
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> H >> W;
    for(int i = 0; i < H; i++) {
        string s;
        cin >> s;
        if (s.find('L') != string::npos) dir[i] = 1;
        else if (s.find('R') != string::npos) dir[i] = -1;
        for(int j = 0; j < W; j++) {
            mp[i][j] = (s[j] == '.');
        }
    }
    bool noL = true;
    for(int i = 0; i < H; i++) if(dir[i] == 1) noL = false;
    for (int i = 0; i < H; i++) for(int j = 0; j < W; j++) for(int r = 0; r < W; r++) dis[i][j][r] = -1;
    queue<tuple<int,int,int>> q; // x, y, r
    q.emplace(0, 0, 0);
    dis[0][0][0] = 0;
    while(!q.empty()) {
        auto [x, y, r] = q.front(); q.pop();
        int nr = r==W-1 ? 0 : r+1;
        for(int k = 0; k < 5; k++) {
            int nx = x + dx[k], ny = (y + dy[k] + W) % W;
            if (valid(nx, ny, nr) && dis[nx][ny][nr] == -1)
                dis[nx][ny][nr] = dis[x][y][r] + 1, q.emplace(nx, ny, nr);
        }
    }
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            int d = -1;
            for(int r = 0; r < W; r++)
                if (dis[i][j][r] != -1 && (d == -1 || d > dis[i][j][r]))
                    d = dis[i][j][r];
            // cout << d << ' ';
            cout << (d==-1 ? '-' : char(d%10+'0'));
        }
        cout << '\n';
    }
}
