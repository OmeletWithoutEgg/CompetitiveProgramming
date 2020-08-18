#include <bits/stdc++.h>

using namespace std;
const int N = 101;
int n;
string v[N],u[N];
bool ok(int L) {
    for(int i = 0; i < n; i++) {
        if(L >= v[i].size()) return false;
        else u[i] = v[i].substr(L);
    }
    sort(u,u+n);
    int h = unique(u,u+n)-u;
    return h == n;
}
int solve() {
    int x = 0, s = 4096;
    while(s) {
        if(ok(x+s)) x += s;
        s >>= 1;
    }
    return x;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    while(cin >> n && n) {
        for(int i = 0; i < n; i++) cin >> v[i];
        cout << solve() << '\n';
    }
}
