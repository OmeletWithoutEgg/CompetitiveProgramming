#include <bits/stdc++.h>

using namespace std;
const int N = 1025;

char col[N][N];
int n, p;
void read(string filename) {
    ifstream fin(filename);
    memset(col, '-', sizeof col);
    fin >> n >> p;
    cout << n << ' ' << p << '\n';
    for(int i = 1; i <= n; i++) {
        string u;
        fin >> u;
        if(u == "-") continue;
        if(u == "0") {
            for(int j = 1; j <= n; j++) col[j][i] = '#';
            continue;
        }
        char c = u.back(); u.pop_back();
        int cnt = stoi(u);
        for(int j = 1; j < cnt; j++) col[j][i] = '#';
        col[cnt][i] = c;
    }
    for(int i = 1; i <= n; i++) {
        string l, r;
        fin >> l >> r;
        if(l == "0") {
            for(int j = 1; j <= n; j++) col[i][j] = '#';
        } else if(l != "-") {
            char c = l.back(); l.pop_back();
            int cnt = stoi(l);
            for(int j = 1; j < cnt; j++) col[i][j] = '#';
            col[i][cnt] = c;
        }
        if(r == "0") {
            for(int j = 1; j <= n; j++) col[i][j] = '#';
        } else if(r != "-") {
            char c = r.back(); r.pop_back();
            int cnt = stoi(r);
            for(int j = 1; j < cnt; j++) col[i][n+1-j] = '#';
            col[i][n+1-cnt] = c;
        }
    }
    for(int i = 1; i <= n; i++) {
        string d;
        fin >> d;
        if(d == "-") continue;
        if(d == "0") {
            for(int j = 1; j <= n; j++) col[j][i] = '#';
            continue;
        }
        char c = d.back(); d.pop_back();
        int cnt = stoi(d);
        for(int j = 1; j < cnt; j++) col[n+1-j][i] = '#';
        col[n+1-cnt][i] = c;
    }
}
void print() {
    cout << ' ';
    for(int i = 1; i <= n; i++) cout << (i < 10 ? char('0'+i) : char('A'+i-10));
    cout << '\n';
    for(int i = 1; i <= n; i++) {
        cout << (i < 10 ? char('0'+i) : char('A'+i-10));
        for(int j = 1; j <= n; j++) {
            cout << col[i][j];
        }
        cout << '\n';
    }
}
void solve() {
    print();
    int x, y;
    char c;
    while(cin >> x >> y >> c && x && y) {
        col[x][y] = c;
        print();
    }
    int q = 0;
    memset(vis, 0, sizeof vis);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(!vis[i][j] && (col[i][j] == 'M'||col[i][j]=='B')) {
        dfs(i, j, col[i][j]);
        ++q;
    }
    /* ofstream ouf("jizz.out"); */
}
signed main() {
    read("pajel_1.in");
    solve();
}
