#include <bits/stdc++.h>

using namespace std;
const int N = 525;

int n,m,cnt;
string s[N];
int val[] = {0, 1, 2, 4, 6, 10, 12, 14, 16, 18, 2147483647};
void dfs(int i,int j) {
    s[i][j] = '#';
    const int dx[] = {1,1,0,-1,-1,-1,0,1};
    const int dy[] = {0,1,1,1,0,-1,-1,-1};
    for(int k = 0; k < 8; k++) {
        int x = i+dx[k], y = j+dy[k];
        if(s[x][y] == '1') dfs(x,y);
    }
}
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> s[i];
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) if(s[i][j] == '1') dfs(i,j), cnt++;
    for(int i = 0; i <= 10; i++) if(val[i] >= cnt) return cout << i << '\n', 0;
}


