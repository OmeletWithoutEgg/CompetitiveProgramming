#include <bits/stdc++.h>

using namespace std;
const int N = 200;

bool ok(vector<pair<int,int>> A, vector<pair<int,int>> B) {
}
int n;
int len[N], dir[N];
bool solve() {
    for(int i = 0; i < n; i++) {
        char c;
        cin >> c >> len[i];
        dir[i] = c=='N' ? 0 : c=='W' ? 1 : c=='S' ? 2 : 3;
    }
    int tot = 0;
    for(int i = 0; i < n; i++) tot += len[i];
    if(tot & 1) return false;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        if(i == j) continue;
        int a = pre[i], b = (pre[i]+half)%tot;
        int c = pre[j], d = (pre[j]+half)%tot;
        // a->c == d->b
        auto A = getsubstr(a, c);
        auto B = getsubstr(b, d);
        for(auto &[dir, len]: B) dir = (dir+2)%4;
        reverse(B.begin(), B.end());
        if(A == B) {
            ;
        }
    }
    return false;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    while(cin >> n && n) {
        bool ret = solve();
        cout << "Polygon " << ++tot << ": " << (ret ? "Possible\n" : "Impossible\n");
    }
}
