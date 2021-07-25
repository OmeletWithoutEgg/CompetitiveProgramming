#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000;

int R, C;
bool vis[maxn][maxn], obs[maxn][maxn];
bool valid(int x, int y) { return 0 <= x && x < R && 0 <= y && y < C && !obs[x][y]; }
void dfs(int sx, int sy) {
    const int dx[4] = {1, 0, -1, 0};
    const int dy[4] = {0, 1, 0, -1};
    stack<pair<int,int>> stk;
    stk.emplace(sx, sy);
    vis[sx][sy] = true;
    while(!stk.empty()) {
        auto [x, y] = stk.top(); stk.pop();
        for(int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if(valid(nx, ny) && !vis[nx][ny])
                vis[nx][ny] = true, stk.emplace(nx, ny);
        }
    }
}
signed main() {
    cerr << "Validator start.\n";
    ios_base::sync_with_stdio(0), cin.tie();
    assert( cin >> R >> C );
    assert( 1 <= R && R <= 1000 && 1 <= C && C <= 1000 );
    int Rs, Cs, Rd, Cd;
    assert( cin >> Rs >> Cs >> Rd >> Cd );
    assert( 0 <= Rs && Rs < R && 0 <= Cs && Cs < C );
    assert( 0 <= Rd && Rd < R && 0 <= Cd && Cd < C );
    assert( Rs != Rd || Cs != Cd );
    int N;
    assert( cin >> N );
    assert( 0 <= N && N <= R * C );

    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++)
            obs[i][j] = true;
    obs[Rs][Cs] = false;
    obs[Rd][Cd] = false;
    for(int i = 0; i < N; i++) {
        int Ri, Ci, Li;
        assert( cin >> Ri >> Ci >> Li );
        assert( 0 <= Ri && Ri < R && 0 <= Ci && Ci < C && 0 <= Li && Li <= 1000000000 );
        assert( Ri != Rs || Ci != Cs );
        assert( Ri != Rd || Ci != Cd );
        assert( obs[Ri][Ci] == true );
        obs[Ri][Ci] = false;
    }

    dfs( Rs, Cs );
    assert( vis[Rd][Cd] );
}
