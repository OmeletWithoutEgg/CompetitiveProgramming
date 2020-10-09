#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    vector<int> pa, rk;
    Dsu(int n) : pa(n), rk(n) { iota(pa.begin(), pa.end(), 0); }
    int anc(int x) { return x==pa[x] ? x : pa[x]=anc(pa[x]); }
    bool join(int x, int y) {
        if((x=anc(x)) == (y=anc(y))) return false;
        if(rk[x] < rk[y]) swap(x, y);
        return pa[y] = x, rk[x]!=rk[y] || ++rk[x];
    }
};
struct Edge {
    string name;
    int a, b, cost, id;
};
void solve(int n) {
    vector<string> att(n);
    for(string &s: att) cin >> s;
    int m;
    cin >> m;
    vector<Edge> E(m), ans;
    int tot = 0;
    for(auto &e: E) cin >> e.name >> e.a >> e.b >> e.cost, e.id = ++tot;
    string src;
    cin >> src;
    sort(E.begin(), E.end(), [](Edge &a, Edge &b){ return a.cost < b.cost; });
    Dsu dsu(n);
    for(auto &e: E) if(dsu.join(e.a, e.b)) ans.push_back(e);
    sort(ans.begin(), ans.end(), [](Edge &a, Edge &b){ return a.id < b.id; });
    tot = 0;
    int sum = 0;
    for(auto &e: ans) {
        if(e.a > e.b) swap(e.a, e.b);
        cout << "#" << ++tot << " Road is named " << e.name << ", connect " << att[e.a] << " and " << att[e.b] << ",length=" << e.cost << '\n';
        sum += e.cost;
    }
    cout << "Jiang will spend " << sum*100 << " TMTdollars.\n";
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    while(cin >> n, n) solve(n);
}
