#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
template <typename ...T> void qqbx(const char *s, T ...args) {
    std::cerr << '(' << s << ')' << " = (";
    int cnt = sizeof...(T), dummy[] = { (std::cerr << args << (--cnt ? ", " : ")\n"), 0)... };
}
#else
#define debug(...) ((void)0)
#endif // local
template <typename U, typename V> std::ostream &operator<<(std::ostream &O, std::pair<U,V> p) { return O << '(' << p.first << ',' << p.second << ')'; }
#define pb emplace_back

using namespace std;
const int N = 2000025, K = 26;

struct AhoCorasick {
    vector<array<int,K>> ch;
    vector<int> fail;
    vector<pair<int,int>> pr;
    /* int ch[N][K], fail[N]; */
    /* pair<int,int> pr[N]; */
    vector<int> bfs;
    /* string raw[N]; */
    int tot;
    void resize(int n) {
        ++n;
        ch.resize(n);
        fail.resize(n);
        pr.resize(n);
    }
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
        bfs = vector<int>{0};
        for(int c = 0; c < K; c++) if(ch[0][c]) q.push(ch[0][c]);
        while(!q.empty()) {
            int i = q.front(); q.pop();
            bfs.pb(i);
            int f = fail[i];
            pr[i] = max(pr[i], pr[f]);
            for(int c = 0; c < K; c++) {
                if(ch[i][c]) {
                    fail[ ch[i][c] ] = ch[f][c];
                    q.push(ch[i][c]);
                } else {
                    ch[i][c] = ch[f][c];
                }
            }
        }
    }
    void add(const string &s, pair<int,int> p) {
        int i = 0;
        for(char c: s) {
            c -= 'a';
            i = ch[i][c];
            pr[i] = max(pr[i], p);
        }
    }
    void finish() {
        for(int i = int(bfs.size())-1; i >= 0; i--) {
            int x = bfs[i];
            pr[fail[x]] = max(pr[fail[x]], pr[x]);
        }
    }
} AC;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<string> v(m);
    vector<int> id(m);
    int totlen = 0;
    for(int i = 0; i < m; i++) {
        cin >> v[i];
        totlen += v[i].size();
    }
    AC.resize(totlen);
    for(int i = 0; i < m; i++)
        id[i] = AC.ins(v[i]);
    AC.buildFail();
    for(int i = 1; i <= n; i++) {
        string s;
        int p;
        cin >> s >> p;
        AC.add(s, {p, i});
    }
    AC.finish();
    for(int i = 0; i < m; i++) cout << AC.pr[id[i]].second << '\n';
}
