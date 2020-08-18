#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <iostream>
using namespace std;
const int N = 400025, K = 26;

struct AhoCorasick {
    int tot, ch[N][K], ans[N], fail[N]; // root = 0
    int q[N], head, tail;
    void init() {
        for(int i = 0; i <= tot; i++) {
            ans[i] = fail[i] = 0;
            for(int c = 0; c < K; c++) ch[i][c] = 0;
        }
        tot = head = tail = 0;
    }
    int ins(const string &s) {
        int i = 0;
        for(char c: s) {
            if(!ch[i][c-'a']) ch[i][c-'a'] = ++tot;
            i = ch[i][c-'a'];
        }
        return i;
    }
    void get_fail() {
        for(int c = 0; c < K; c++) if(ch[0][c]) q[tail++] = ch[0][c];
        while(head != tail) {
            int i = q[head++];
            for(int c = 0; c < K; c++) {
                int j = fail[i];
                if(ch[i][c])
                    fail[ q[tail++] = ch[i][c] ] = ch[j][c];
                else
                    ch[i][c] = ch[j][c];
            }
        }
    }
    void run(const string &s) {
        int i = 0;
        for(char c: s) {
            i = ch[i][c-'a'];
            ++ans[i];
        }
        for(int i = tot-1; i >= 0; i--) {
            int x = q[i];
            ans[fail[x]] += ans[x];
        }
    }
} AC;
int endnode[N];
void solve() {
    int n;
    string T, P;
    cin >> T >> n;
    AC.init();
    for(int i = 0; i < n; i++) cin >> P, endnode[i] = AC.ins(P);
    AC.get_fail();
    AC.run(T);
    for(int i = 0; i < n; i++) cout << AC.ans[endnode[i]] << '\n';
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--) solve();
}
