#include <bits/stdc++.h>

using namespace std;
const int inf = 1e9;

struct KuhnMunkres {
    int n;
    vector<vector<int>> g;
    vector<int> lx, ly, slack;
    vector<int> match, visx, visy;
    KuhnMunkres(int n) : n(n), g(n, vector<int>(n)), lx(n), ly(n), slack(n), match(n), visx(n), visy(n) {}
    void addEdge(int a, int b, int c) {
        g[a][b] = max(g[a][b], c);
    }
    vector<int> & operator[](int i) { return g[i]; }
    bool dfs(int i, bool aug) {
        if(visx[i]) return false;
        visx[i] = true;
        for(int j = 0; j < n; j++) {
            if(visy[j]) continue;
            int d = lx[i] + ly[j] - g[i][j];
            if(d == 0) {
                visy[j] = true;
                if(match[j] == -1 || dfs(match[j], aug)) {
                    if(aug)
                        match[j] = i;
                    return true;
                }
            } else {
                slack[j] = min(slack[j], d);
            }
        }
        return false;
    }
    int solve() {
        /* for(int i = 0; i < n; i++) {
            lx[i] = 0;
            for(int j = 0; j < n; j++) lx[i] = max(lx[i], g[i][j]);
        } */
        fill(lx.begin(), lx.end(), inf);
        fill(ly.begin(), ly.end(), 0);
        fill(match.begin(), match.end(), -1);
        for(int i = 0; i < n; i++) {
            fill(slack.begin(), slack.end(), inf);
            fill(visx.begin(), visx.end(), false);
            fill(visy.begin(), visy.end(), false);
            auto augment = [&]() -> bool {
                for(int j = 0; j < n; j++) if(!visy[j] && slack[j] == 0) {
                    visy[j] = true;
                    if(match[j] == -1 || dfs(match[j], false)) {
                        return true;
                    }
                }
                return false;
            };
            auto relabel = [&]() -> void {
                int d = inf;
                for(int j = 0; j < n; j++) if(!visy[j]) d = min(d, slack[j]);
                for(int i = 0; i < n; i++) {
                    if(visx[i]) lx[i] -= d;
                    if(visy[i]) ly[i] += d;
                    else slack[i] -= d;
                }
            };
            if(dfs(i, true)) continue;
            while(!augment()) relabel();
            fill(visx.begin(), visx.end(), false);
            fill(visy.begin(), visy.end(), false);
            dfs(i, true);
        }
        int ans = 0;
        for(int j = 0; j < n; j++) if(match[j] != -1) ans += g[match[j]][j];
        return ans;
    }
};
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    while(cin >> n && n) {
        KuhnMunkres KM(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int c;
                cin >> c;
                if(c > 0)
                    KM[i][j] = c;
            }
        }
        cout << KM.solve() << '\n';
    }
}
