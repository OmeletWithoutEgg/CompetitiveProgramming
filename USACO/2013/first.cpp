#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
const int N = 30025;

int n;
string s[N];
vector<int> ans;
int g[26][26], deg[26], indeg[26];
bool topo() {
    queue<int> q;
    for(int i = 0; i < 26; i++) deg[i] = indeg[i];
    for(int i = 0; i < 26; i++) if(indeg[i] == 0) q.push(i);
    while(!q.empty()) {
        int i = q.front(); q.pop();
        for(int j = 0; j < 26; j++) if(g[i][j] && --deg[j] == 0) q.push(j);
    }
    for(int i = 0; i < 26; i++) if(deg[i]) return false;
    return true;
}
void solve(vector<int> v, size_t len = 0) {
    if(!topo()) return;
    if(v.size() == 1) {
        for(int x: v) ans.pb(x);
        return;
    }
    vector<int> e;
    for(int x: v) if(s[x].size() == len) e.pb(x);
    if(e.size()) {
        assert(e.size() == 1);
        for(int x: e) ans.pb(x);
        return;
    }
    vector<int> buc[26];
    for(int x: v) {
        int c = s[x][len] - 'a';
        buc[c].pb(x);
    }
    for(int c = 0; c < 26; c++) if(buc[c].size()) {
        for(int i = 0; i < 26; i++) if(c != i && buc[i].size()) {
            if(++g[c][i] == 1) {
                ++indeg[i];
            }
        }
        solve(buc[c], len + 1);
        for(int i = 0; i < 26; i++) if(c != i && buc[i].size()) {
            if(--g[c][i] == 0) {
                --indeg[i];
            }
        }
    }
}
signed main() {
#ifndef local
    freopen("first.in", "r", stdin);
    freopen("first.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> s[i];
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    solve(id, 0);
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for(int x: ans) cout << s[x] << '\n';
}
