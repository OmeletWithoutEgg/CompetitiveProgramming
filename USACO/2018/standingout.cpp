#include <bits/stdc++.h>
#ifdef local
#define debug(a...) qqbx(#a, a)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\033[1;32m(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : "\033[0m)\n")));
}
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define pb emplace_back
#define sort_uni(v) sort(all(v)), v.erase(unique(all(v)), v.end())

using namespace std;
using ll = int64_t;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
const ll INF = 1e18;
const int maxn = 200025, inf = 1e9, K = 500;

struct SuffixArray {
    int sa[maxn], rk[maxn], nrk[maxn];
    int H[maxn];
    int st[20][maxn]; // sparse table;
    void build(const string &s) {
        int n = s.size();
        for (int i = 0; i < n; i++) rk[i] = s[i];
        iota(sa, sa+n, 0);
        for (int L = 1; L < s.size(); L *= 2) {
            auto cmp = [&](int a, int b) {
                if (rk[a] != rk[b]) return rk[a] < rk[b];
                int ra = a+L < n ? rk[a+L] : -1;
                int rb = b+L < n ? rk[b+L] : -1;
                return ra < rb;
            };
            sort(sa, sa+n, cmp);
            nrk[sa[0]] = 0;
            for (int i = 1; i < n; i++)
                nrk[sa[i]] = nrk[sa[i-1]] + cmp(sa[i-1], sa[i]);
            for (int i = 0; i < n; i++) rk[i] = nrk[i];
        }

        for (int i = 0, h = 0; i < n; i++) {
            if (rk[i] == 0) continue;
            int j = sa[rk[i] - 1];
            while (i+h < n && j+h < n && s[i+h] == s[j+h]) ++h;
            H[rk[i]] = h;
            if (h > 0)
                --h;
        }
        H[0] = H[n] = 0;
        for (int i = 0; i <= n; i++) st[0][i] = H[i];
        for (int L = 1; L < 20; L++) {
            int len = 1 << (L-1);
            for (int i = 0; i+len <= n; i++)
                st[L][i] = min(st[L-1][i], st[L-1][i + len]);
        }
    }
    int nxtSep[maxn];
    int L[maxn], R[maxn], lastSame[maxn];
    void solve(const string &t) {
        build(t);

        vector<int> group(t.size(), -1);
        int tot = 0;
        for (int i = 0; i < t.size(); i++) {
            if (t[i] == '$')
                ++tot;
            else
                group[i] = tot;
        }
        for (int i = t.size()-1; i >= 0; i--) {
            if (t[i] == '$')
                nxtSep[i] = i;
            else
                nxtSep[i] = nxtSep[i+1];
        }
        
        L[0] = -1;
        for (int i = 1; i < t.size(); i++)
            if (group[sa[i]] == group[sa[i-1]])
                L[i] = L[i-1];
            else
                L[i] = i-1;
        
        R[t.size()-1] = t.size();
        for (int i = t.size()-2; i >= 0; i--)
            if (group[sa[i]] == group[sa[i+1]])
                R[i] = R[i+1];
            else
                R[i] = i+1;

        vector<int> last(tot);
        for (int i = 0; i < t.size(); i++) {
            if (group[sa[i]] == -1)
                continue;
            lastSame[i] = last[group[sa[i]]];
            last[group[sa[i]]] = i;
        }

        auto LCP = [&](int a, int b) -> int {
            if (a == b) return t.size() - sa[a];
            int res = t.size() - sa[b];
            ++a, ++b;
            int lev = __lg(b - a);
            res = min({ res, st[lev][a], st[lev][b - (1 << lev)] });
            return res;
        };
        vector<ll> ans(tot);
        for (int i = 0; i < t.size(); i++) {
            if (t[sa[i]] == '$') continue;
            int len = max({ LCP(L[i], i), LCP(i, R[i]), LCP(lastSame[i], i) });
            // debug(i, group[sa[i]], lastSame[i], LCP(L[i], i), LCP(i, R[i]), H[i], t.substr(sa[i]), max(0, nxtSep[sa[i]] - sa[i] - len));
            ans[group[sa[i]]] += max(0, nxtSep[sa[i]] - sa[i] - len);
            // lcp[i] + 1 ~ nxtSep[i];
        }
        for (int i = 0; i < tot; i++)
            cout << ans[i] << '\n';
    }
} SA;
signed main() {
    assert( freopen("standingout.in", "r", stdin) && freopen("standingout.out", "w", stdout) );
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    string t;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        t += s + '$';
    }
    SA.solve(t);
}
