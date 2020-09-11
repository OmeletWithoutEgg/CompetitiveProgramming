#include <bits/stdc++.h>
using namespace std;
#define debug(x) std::cerr<<#x<<" = "<<x<<'\n'
#define pb emplace_back

#define TIME Timer __timer(__PRETTY_FUNCTION__)
class Timer {
private:
    std::string title;
    chrono::high_resolution_clock::time_point start;
public:
    Timer(std::string t) :
        title(t), start(chrono::high_resolution_clock::now()) {}
    ~Timer() {
        auto finish = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
        double ms = double(duration) * 0.001;
        std::cerr << "Timer: " << title << " takes " << ms << " ms to finish.\n";
    }
};

const int N = 100025;
vector<int> g[N];
int pa[20][N], dep[N];
void dfs(int r) {
    vector<int> stk;
    stk.pb(r);
    while(!stk.empty()) {
        int i = stk.back(); stk.pop_back();
        for(int j: g[i]) {
            if(j != pa[0][i]) {
                pa[0][j] = i;
                dep[j] = dep[i] + 1;
                stk.pb(j);
            }
        }
    }
}
int query(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    int ans = dep[a] - dep[b];
    for(int i = 19; i >= 0; i--) if(ans >> i & 1) a = pa[i][a];
    if(a == b) return ans;
    for(int i = 19; i >= 0; i--) if(pa[i][a] != pa[i][b]) {
        a = pa[i][a];
        b = pa[i][b];
        ans += 2 << i;
    }
    return ans + 2;
}
signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b), g[b].pb(a);
    }
    dfs(0);
    for(int L = 1; L < 20; L++) for(int i = 0; i < n; i++) pa[L][i] = pa[L-1][pa[L-1][i]];
    for(int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        cout << query(a, b) << '\n';
    }
}
