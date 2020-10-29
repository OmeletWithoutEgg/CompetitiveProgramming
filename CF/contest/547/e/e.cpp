#include <bits/stdc++.h>
#define pb emplace_back
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local

using namespace std;
using ll = long long;
const int N = 200025, K = 26;

struct TreeSum {
    vector<int> g[N];
    int in[N], ou[N], tot;
    ll sum[N];
    void addEdge(int a, int b) {
        g[a].pb(b);
        g[b].pb(a);
    }
    void dfs(int i, int p) {
        in[i] = ++tot;
        for(int j: g[i]) if(j != p) dfs(j, i);
        ou[i] = tot;
    }
    void add(int p, int d) {
        debug(tot);
        for(p = in[p]; p <= tot; p += p&-p) sum[p] += d;
    }
    ll query(int p) {
        int l = in[p] - 1, r = ou[p];
        ll res = 0;
        for(; r > 0; r -= r&-r) res += sum[r];
        for(; l > 0; l -= l&-l) res -= sum[l];
        return res;
    }
} tr;
struct AhoCorasick {
    int ch[N][K], fail[N], tot;
    int ins(const string &s) {
        int i = 0;
        for(char c: s) {
            c -= 'a';
            if(!ch[i][c])
                ch[i][c] = ++tot;
            i = ch[i][c];
        }
        return i;
    }
    void buildFail() {
        queue<int> q;
        for(int i = 0; i < K; i++) if(ch[0][i]) q.push(ch[0][i]);
        while(!q.empty()) {
            int i = q.front(); q.pop();
            for(int c = 0; c < K; c++) {
                if(ch[i][c]) {
                    fail[ch[i][c]] = ch[fail[i]][c];
                    q.push(ch[i][c]);
                } else {
                    ch[i][c] = ch[fail[i]][c];
                }
            }
        }
        for(int i = 1; i <= tot; i++) tr.addEdge(i, fail[i]);
        tr.dfs(0, -1);
    }
    void run(const string &s) {
        int i = 0;
        for(char c: s) {
            c -= 'a';
            i = ch[i][c];
            tr.add(i, 1);
        }
    }
} AC;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<string> v(n);
    vector<vector<tuple<int,int,int>>> Q(n);
    for(string &s: v) cin >> s;
    for(int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        --k, --l, --r;
        if(l > 0) Q[l-1].pb(k, -1, i);
        if(r < n) Q[r].pb(k, 1, i);
    }
    vector<int> ed(n);
    for(int i = 0; i < n; i++) ed[i] = AC.ins(v[i]);
    /* for(int i = 0; i < n; i++) cerr << ed[i] << ' '; */
    /* cerr << '\n'; */
    AC.buildFail();
    vector<int> ans(q);
    for(int i = 0; i < n; i++) {
        AC.run(v[i]);
        for(auto [k, r, id]: Q[i])
            ans[id] += 1LL * r * tr.query(ed[k]);
    }
    for(int i = 0; i < q; i++) cout << ans[i] << '\n';
}
