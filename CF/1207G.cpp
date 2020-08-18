#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define debug(x) cerr<<#x<<" = "<<x<<'\n'

using namespace std;
typedef long long ll;
const int N = 400025, K = 26;

vector<pair<int,int>> Q[N];
int ans[N];

struct TreePathSum {
    vector<int> g[N];
    int in[N], ou[N], tot;
    ll sum[N];
    void addEdge(int a, int b) {
        g[a].push_back(b);
    }
    void dfs(int i = 0) {
        in[i] = ++tot;
        for(int j: g[i]) dfs(j);
        ou[i] = tot+1;
    }
    void add(int x, int d) {
        for(int p = in[x]; p <= tot; p += p&-p) sum[p] += d;
    }
    int query(int x) {
        ll res = 0;
        for(int p = ou[x]-1; p > 0; p -= p&-p) res += sum[p];
        for(int p = in[x]-1; p > 0; p -= p&-p) res -= sum[p];
        return res;
    }
    /*void dbg() {
        for(int i = 1; i <= tot; i++) cout << query(i)-query(i-1) << ' ';
        cout << '\n';
    }*/
} tr;

struct AhoCorasick {
    int ch[N][K], fail[N];
    int tot, q[N];
    int ins(const string &s) {
        int i = 0;
        for(char c: s) {
            if(!ch[i][c-'a'])
                ch[i][c-'a'] = ++tot;
            i = ch[i][c-'a'];
        }
        return i;
    }
    void buildFail() {
        int head = 0, tail = 0;
        for(int c = 0; c < K; c++)
            if(ch[0][c])
                q[tail++] = ch[0][c];
        while(head != tail) {
            int i = q[head++];
            for(int c = 0; c < K; c++) {
                int f = fail[i];
                if(ch[i][c])
                    fail[ q[tail++]=ch[i][c] ] = ch[f][c];
                else
                    ch[i][c] = ch[f][c];
            }
        }
        for(int i = 1; i <= tot; i++) tr.addEdge(fail[i], i);
        tr.dfs();
    }
    int stk[N]={0}, p=1;
    void advance(int c) {
        int i = stk[p-1];
        tr.add(stk[p++] = ch[i][c], 1);
    }
    void moveback() {
        tr.add(stk[--p], -1);
    }
    int query(int i) {
        return tr.query(i);
    }
} AC;

struct Trie {
    int ch[N][K], tot;
    int ins(int i, char c) {
        if(!ch[i][c-'a'])
            ch[i][c-'a'] = ++tot;
        return ch[i][c-'a'];
    }
    void DFS(int i = 0) {
        for(auto [qid, tid]: Q[i]) ans[qid] = AC.query(tid);
        for(int c = 0; c < K; c++) if(ch[i][c]) {
            AC.advance(c);
            DFS(ch[i][c]);
            AC.moveback();
        }
    }
} T;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n;
    //n = 40000;
    vector<int> root(n);
    for(int i = 0; i < n; i++) {
        int t, j;
        char c;
        cin >> t;
        //t = 1 + (i!=0);
        if(t == 1) {
            cin >> c;
            //c = 'a';
            root[i] = T.ins(0, c);
        } else if(t == 2) {
            cin >> j >> c, --j;
            //j = i-1, c = 'a' + (i&1);
            root[i] = T.ins(root[j], c);
        }
    }
    cin >> q;
    for(int i = 0; i < q; i++) {
        int id;
        string t;
        cin >> id >> t, --id;
        Q[root[id]].emplace_back(i, AC.ins(t));
    }
    AC.buildFail();
    T.DFS();
    for(int i = 0; i < q; i++) cout << ans[i] << '\n';
}

