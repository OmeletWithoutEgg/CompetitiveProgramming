#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "\033[1;32m(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
}
#define TAK(args...) std::ostream& operator<<(std::ostream &O, args)
#define NIE(STL, BEG, END, OUT) template <typename ...T> TAK(std::STL<T...> v) \
    { O << BEG; int f=0; for(auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }
NIE(vector, "[", "]", e)
#else
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)
#define sort_uni(v) sort(all(v)), v.erase(unique(all(v)),v.end())
#define get_pos(v,x) int(lower_bound(all(v),x)-v.begin())

using namespace std;
const int N = 300001;

vector<int> g[N], stk, bccv[N];
int vis[N], low[N], tot;
int bccn, bcc[N];
bool ap[N];
void dfs(int i, int p) {
    int child = 0;
    vis[i] = low[i] = ++tot;
    stk.pb(i);
    for(int j: g[i]) {
        if(j == p) continue;
        if(vis[j]) {
            low[i] = min(low[i], vis[j]);
        } else {
            ++child;
            dfs(j, i);
            if(low[j] >= vis[i]) {
                int x;
                do {
                    x = stk.back(), stk.pop_back();
                    bcc[x] = bccn;
                    bccv[bccn].pb(x);
                } while(x != j);
                bcc[i] = bccn;
                bccv[bccn].pb(i);
                ++bccn;
                ap[i] = true;
            }
            low[i] = min(low[i], low[j]);
        }
    }
    if(p == -1 && child == 1)
        ap[i] = false;
}
vector<int> tr[N*2];
int in[N*2], ou[N*2], cnt;
int pa[20][N*2], dep[N*2];
bool isap[N*2];
bool isAnc(int p, int i) {
    return in[p] <= in[i] && in[i] < ou[p];
}
void DFS(int i, int p) {
    in[i] = cnt++;
    for(int j: tr[i]) {
        if(j != p) {
            pa[0][j] = i;
            dep[j] = dep[i] + 1;
            DFS(j, i);
        }
    }
    ou[i] = cnt;
}
int LCA(int a, int b) {
    if(dep[a] > dep[b]) swap(a, b);
    int d = dep[b] - dep[a];
    for(int i = 19; i >= 0; i--) if(d >> i & 1) b = pa[i][b];
    if(a == b) return 0;
    for(int i = 19; i >= 0; i--) if(pa[i][a] != pa[i][b]) a = pa[i][a], b = pa[i][b];
    return pa[0][a];
}
bool ok(int a, int b, int c) {
    int lca = LCA(a, b);
    if(!isap[lca] && c==pa[0][lca]) return true;
    if(isap[c] && ok(a, b, pa[0][c])) return true;
    if(isAnc(lca, c) && (isAnc(c, a) || isAnc(c, b))) return true;
    if(isAnc(c, lca) && (isAnc(a, b) || isAnc(b, a))) return true;
    return false;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].pb(b), g[b].pb(a);
    }
    dfs(0, -1);
    for(int i = 0; i < n; i++) if(ap[i]) {
        bcc[i] = bccn++;
        isap[bcc[i]] = true;
    }
    debug(bccn);
    for(int i = 0; i < bccn && i < N; i++)
        for(int j: bccv[i])
            if(ap[j])
                tr[i].pb(bcc[j]), tr[bcc[j]].pb(i);
    for(int i = 0; i < bccn; i++)
        sort_uni(tr[i]), debug(i, tr[i]);
    DFS(0, -1);
    // return 0;
    for(int L = 1; L < 20; L++)
        for(int i = 0; i < bccn; i++)
            pa[L][i] = pa[L-1][pa[L-1][i]];
    while(q--) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b, --c;
        a = bcc[a], b = bcc[b], c = bcc[c];
        if(ok(a, b, c) || ok(c, a, b) || ok(b, c, a))
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}
