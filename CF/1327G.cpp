#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#ifdef local
#define debug(x) (cerr<<#x<<" = "<<(x)<<'\n')
#else
#define debug(x) ((void)0)
#endif // local

using namespace std;
typedef int64_t ll;
constexpr ll N = 1025, INF = 1e18, K = 14;

//#define int ll
struct AhoCorasick {
    int ch[N][K], fail[N];
    int val[N], q[N], tot;
    pair<int,ll> nxt[16][N];
    ll dp[1<<K][N];
    void ins(const string &s, int v) {
        int i = 0;
        for(char c: s) {
            if(!ch[i][c-'a'])
                ch[i][c-'a'] = ++tot;
            i = ch[i][c-'a'];
        }
        val[i] += v;
    }
    void buildFail() {
        int head = 0, tail = 0;
        for(int c = 0; c < K; c++) if(ch[0][c])
            q[tail++] = ch[0][c];
        while(head != tail) {
            int i = q[head++];
            for(int c = 0; c < K; c++) {
                int f = fail[i], j = ch[i][c];
                while(f && !ch[f][c]) f = fail[f];
                if(ch[f][c]) f = ch[f][c];
                if(ch[i][c])
                    fail[ q[tail++]=ch[i][c] ] = f, val[ch[i][c]] += val[f];
                else
                    ch[i][c] = f;
            }
        }
        //for(int i = 0; i < tot; i++) val[q[i]] += val[fail[q[i]]];
    }
    pair<int,ll> advance(const string &s, int p) {
        ll res = 0;
        for(char c: s) p = ch[p][c-'a'], res += val[p];
        return {p, res};
    }
    int prepare(const string &s) {
        int cnt = 0, last = 0;
        for(int i = 0; i <= s.size(); i++) {
            if(i == s.size() || s[i] == '?') {
                string t = s.substr(last, i-last);
                for(int p = 0; p <= tot; p++)
                    nxt[cnt][p] = advance(t, p);
                last = i+1;
                cnt++;
            }
        }
        return cnt;
    }
    ll DP(int cnt) {
        for(int mask = 0; mask < (1<<K); mask++) {
            for(int p = 0; p <= tot; p++) {
                dp[mask][p] = -INF;
            }
        }
        auto [q, v] = nxt[0][0];
        dp[0][q] = v;
        ll res = -INF;
        for(int mask = 0; mask < (1<<K); mask++) {
            int L = __builtin_popcount(mask);
            if(L >= cnt) continue;
            for(int p = 0; p <= tot; p++) {
                if(L == cnt-1) {
                    res = max(res, dp[mask][p]);
                    continue;
                }
                for(int c = 0; c < K; c++) if(~mask>>c & 1) {
                    int to = mask ^ (1<<c);
                    auto [q, v] = nxt[L+1][ch[p][c]];
                    v += val[ch[p][c]];
                    dp[to][q] = max(dp[to][q], dp[mask][p] + v);
                }
            }
        }
        return res;
    }
} AC;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int k, x;
    string s;
    cin >> k;
    while(k--) {
        cin >> s >> x;
        AC.ins(s, x);
    }
    AC.buildFail();
    cin >> s;
    int block = AC.prepare(s);
    ll res = AC.DP(block);
    cout << res << '\n';
}
