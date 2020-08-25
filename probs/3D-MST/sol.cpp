#include<bits/stdc++.h>
#define pb emplace_back
#define debug(x) cerr<<#x<<" = "<<x<<'\n'
#define TIME Timer __timer(__PRETTY_FUNCTION__)
using namespace std;
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
const int64_t INF = 1e18;

int n;
array<int,3> T[N];
int64_t dist(array<int,3> a, array<int,3> b) {
    int64_t res = 0;
    for(int i = 0; i < 3; i++) res += 1LL*(a[i]-b[i])*(a[i]-b[i]);
    return res;
}
void Kruskal() {
    vector<tuple<int64_t,int,int>> edge;
    for(int i = 0; i < n; i++) for(int j = 0; j < i; j++) edge.pb(dist(T[i], T[j]), i, j);
    sort(edge.begin(), edge.end());
    vector<int> pa(n), rk(n);
    function<int(int)> anc = [&pa, &anc](int x) -> int { return x==pa[x] ? x : pa[x]=anc(pa[x]); };
    auto join = [&pa, &rk, &anc](int x, int y) -> bool {
        if((x=anc(x)) == (y=anc(y))) return false;
        if(rk[x] < rk[y]) swap(x, y);
        return pa[y] = x, rk[x]!=rk[y]||++rk[x], true;
    };
    iota(pa.begin(), pa.end(), 0);
    int64_t ans = 0;
    for(auto [w, a, b]: edge) if(join(a, b)) ans += w;
    cout << ans << '\n';
}
void Prim() {
    vector<int64_t> dis(n, INF);
    vector<bool> vis(n);
    dis[0] = 0;
    int64_t ans = 0;
    for(int i = 0; i < n; i++) {
        int p = min_element(dis.begin(), dis.end()) - dis.begin();
        ans += dis[p];
        dis[p] = INF;
        vis[p] = 1;
        for(int j = 0; j < n; j++) if(!vis[j]) dis[j] = min(dis[j], dist(T[p], T[j]));
    }
    cout << ans << '\n';
}
signed main(int argc, char **argv) {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) for(int c = 0; c < 3; c++) cin >> T[i][c];
    Prim();
}
