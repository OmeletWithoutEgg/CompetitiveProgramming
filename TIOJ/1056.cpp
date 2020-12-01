#include <bits/stdc++.h>
//#define int long long

using namespace std;

set<int> able;
void decode(int s,int t[]) {
    for(int i = 0; i < 9; i++) {
        t[i] = s%3, s/=3;
        if(t[i] == 2) t[i] = -1;
    }
}
int encode(int t[]) {
    int s = 0;
    for(int i = 8; i >= 0; i--) {
        s *= 3;
        if(t[i] == -1) t[i] += 3;
        s += t[i];
    }
    return s;
}
void dbg(int t[]) {
    int cnt = 0;
    for(int i = 0; i < 9; i++) if(t[i] != 0) cnt++;
    if(cnt < 6) return;
    for(int i = 0; i < 9; i++) {
        cout << "X.O"[t[i]+1];
        if(i%3 == 2) cout << '\n';
    }
    system("PAUSE");
}
bool win(int t[],int x) {
    int diag[2] = {};
    for(int i = 0; i < 3; i++) {
        int row = 0, col = 0;
        for(int j = 0; j < 3; j++) {
            if(t[i*3+j] == x) row++;
            if(t[i+j*3] == x) col++;
        }
        if(row == 3 || col == 3) return true;
        if(t[i*3+i] == x) diag[0]++;
        if(t[i*3+2-i] == x) diag[1]++;
    }
    return (diag[0] == 3 || diag[1] == 3);
}
void dfs(int s,int now=1) {
    if(able.count(s)) return;
    able.insert(s);
    int t[9];
    decode(s,t);
    //dbg(t);
    if(win(t,-now)) return;
    for(int i = 0; i < 9; i++) {
        if(t[i] == 0) {
            t[i] = now;
            s = encode(t);
            dfs(s,-now);
            t[i] = 0;
        }
    }
}
char tb[3][4];
int t[9];
signed main() {
    dfs(0);
    for(int i = 0; i < 3; i++) cin >> tb[i];
    for(int i = 0; i < 9; i++) {
        if(tb[i/3][i%3] == 'O') t[i] = 1;
        else if(tb[i/3][i%3] == 'X') t[i] = -1;
        else if(tb[i/3][i%3] == '.') t[i] = 0;
        else cout << "IMPOSSIBLE\n", exit(0);
    }
    if(able.count(encode(t))) cout << "POSSIBLE\n";
    else cout << "IMPOSSIBLE\n";
}
