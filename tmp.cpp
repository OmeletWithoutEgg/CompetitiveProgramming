#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
template <class ...T> void qqbx(const char *s, T ...a) {
    int f = 0;
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << (f++ ? ", " : "") << a)), std::cerr << ")\n";
}
#else
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
using ll = int64_t;
const int maxn = 250025, inf = 1e9;

struct RMQ {
    int mn[20][maxn];
    int & operator [](int i) { return mn[0][i]; }
    void build(int n) {
        for (int L = 1; L < 20; L++) {
            int len = 1 << L-1;
            for (int i = 0; i < n; i++)
                mn[L][i] = min(mn[L-1][i], (i + len < n ? mn[L-1][i + len] : inf));
        }
    }
    int operator()(int l, int r) const {
        if (l == r) return inf;
        // assert( l < r );
        int lev = __lg(r - l);
        return min(mn[lev][l], mn[lev][r - (1 << lev)]);
    }
};

struct SuffixArray {
    int sa[maxn], rk[maxn];
    int nrk[maxn];
    int lcp[maxn];
    string s;
    RMQ LCP, pos;
    void build(const string &s_) {
        s = s_;
        for (int i = 0; i < s.size(); i++) rk[i] = s[i], sa[i] = i;
        for (int L = 1; L < s.size(); L <<= 1) {
            auto cmp = [&](int a, int b) {
                if (rk[a] != rk[b]) return rk[a] < rk[b];
                int ra = a+L < s.size() ? rk[a+L] : -1;
                int rb = b+L < s.size() ? rk[b+L] : -1;
                return ra < rb;
                if (ra != rb) return ra < rb;
                return a > b;
            };
            sort(sa, sa+s.size(), cmp);
            nrk[sa[0]] = 0;
            for (int i = 1; i < s.size(); i++) nrk[sa[i]] = nrk[sa[i-1]] + cmp(sa[i-1], sa[i]);
            for (int i = 0; i < s.size(); i++) rk[i] = nrk[i];
        }
        // cerr << "SA of " << s << '\n';
        // for (int i = 0; i < s.size(); i++) cerr << i << ' ' << s.substr(sa[i]) << '\n';
        for (int i = 0, h = 0; i < s.size(); i++) {
            if (rk[i] == 0) continue;
            int j = sa[rk[i]-1];
            while (i+h < s.size() && j+h < s.size() && s[i+h] == s[j+h]) ++h;
            lcp[rk[i]-1] = h;
            if (h > 0) --h;
        }
        // for (int i = 0; i < s.size(); i++)
        //     cerr << lcp[i] << ' ' << s.substr(sa[i]) << '\n';
        for (int i = 0; i < s.size(); i++) LCP[i] = lcp[i];
        LCP.build(s.size());
        for (int i = 0; i < s.size(); i++) pos[i] = inf;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '$') break;
            pos[rk[i]] = -i;
            // debug(rk[i], s[i]);
        }
        // debug("SAFE\n");
        pos.build(s.size());
    }

    pair<int,int> bsearch(int suf, int p) {
        assert ( sa[suf] + p <= s.size() );
        int l = suf, r = suf - 1;
        for (int step = 1 << 18; step; step >>= 1) {
            if (l - step >= 0 && LCP(l - step, suf) >= p) l -= step;
            if (r + step < s.size() && LCP(suf, r + step) >= p) r += step;
        }
        ++r;
        // debug(suf, l, r);
        // debug(s.substr(sa[suf]), p);
        // for (int i = 0; i < s.size(); i++) cerr << i << ' ' << sa[i] << ' ' << s.substr(sa[i]) << '\n';
        return { l, r };
        // returns [l, r) such that LCP(suf, sa[i]) >= p for all i \in [l, r)
    }

    int occur(int suf, int p) {
        auto [l, r] = bsearch(suf, p);
        int mx = -pos(l, r);
        if (mx == -inf) return -1;
        return mx;
    }
} SA, rSA;

namespace cdq {
    struct Fenwick {
        int sum[maxn * 2];
        void add(int p, int d) {
            for (p += maxn; p < maxn * 2; p += p & -p) sum[p] += d;
        }
        int qry(int p) {
            int res = 0;
            for (p += maxn; p > 0; p -= p & -p) res += sum[p];
            return res;
        }
    } BB;
    struct Query {
        int t;
        int x, y, z;
        int v;
        int id;
    } Q[maxn * 4];
    int tot;
    int64_t ans[maxn];
    void addQ(int t, int x, int y, int z, int v, int id) {
        Q[tot++] = {t, x, y, z, v, id};
    }
    bool cmp(const Query &a, const Query &b) {
        return a.y != b.y ? a.y < b.y : a.t < b.t;
    }
    void solve(int l, int r) {
        /*
        for (int i = l; i < r; i++) {
            if (Q[i].t == 1) {
                for (int j = l; j < i; j++) {
                    if (Q[j].t == 0 && Q[j].y <= Q[i].y && Q[j].z <= Q[i].z) {
                        ans[Q[i].id] += Q[j].v * Q[i].v;
                    }
                }
            }
        }
        return;
        */
        if (r-l <= 1) return;
        int m = (l+r)/2;
        solve(l, m);
        solve(m, r);

        int i = l, j = m;
        while (i != m || j != r) {
            if (j == r || (i != m && cmp(Q[i], Q[j]))) {
                auto &qq = Q[i++];
                if (qq.t == 0)
                    BB.add(qq.z, qq.v);
            } else {
                auto &qq = Q[j++];
                if (qq.t == 1)
                    ans[qq.id] += BB.qry(qq.z) * qq.v;
            }
        }
        for (int i = l; i < m; i++) {
            auto &qq = Q[i];
            if (qq.t == 0) BB.add(qq.z, -qq.v);
        }
        inplace_merge(Q+l, Q+m, Q+r, cmp);
    }
    void solve() {
        sort(Q, Q+tot, [](const Query &a, const Query &b){ return a.x != b.x ? a.x < b.x : a.t < b.t; });
        solve(0, tot);
    }
}

// vector<tuple<int,int,int>> cdq;
void addQuery(int l1, int r1, int l2, int r2, int l3, int r3, int id) {
    cdq::addQ(1, r1, r2, r3, 1, id);
    
    cdq::addQ(1, l1, r2, r3, -1, id);
    cdq::addQ(1, r1, l2, r3, -1, id);
    cdq::addQ(1, r1, r2, l3, -1, id);

    cdq::addQ(1, l1, l2, r3, 1, id);
    cdq::addQ(1, r1, l2, l3, 1, id);
    cdq::addQ(1, l1, r2, l3, 1, id);

    cdq::addQ(1, l1, l2, l3, -1, id);
    // debug(l1, r1, l2, r2, l3, r3);
    /*
    int ans = 0;
    for (auto [x, y, z]: cdq)
        if (l1 <= x && x < r1 &&
            l2 <= y && y < r2 &&
            l3 <= z && z < r3)
            ++ans;
    // debug(ans);
    return ans;
    */
}
void calc(int n, int offset, int sz, int id) {
    int l1 = SA.occur(SA.rk[offset], sz);
    int r1 = n - 1 - rSA.occur(rSA.rk[offset], sz);
    for (int i = 1; i < sz; i++) {
        int j = sz - i;
        auto [l2, r2] = SA.bsearch(SA.rk[offset + i], j);
        auto [l3, r3] = rSA.bsearch(rSA.rk[offset + j], i);
        if (l1 >= r1 || l2 >= r2 || l3 >= r3) continue;
        addQuery(l1-1, r1-1, l2-1, r2-1, l3-1, r3-1, id);
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    string orgS, orgT;
    cin >> orgS >> orgT;

    int n = orgS.size();

    int q;
    cin >> q;
    string S = orgS, T = orgT;
    reverse(all(S));
    
    vector<int> pos(q), sz(q);
    for (int i = 0; i < q; i++) {
        string P;
        cin >> P;
        pos[i] = T.size() + 1;
        sz[i] = P.size();
        T += '$' + P;
        reverse(all(P));
        S += '$' + P;
    }
    SA.build(T);
    rSA.build(S);

    for (int i = 0; i+1 < n; i++) {
        int x = SA.rk[i+1];
        int y = rSA.rk[n-1-i];
        // debug(SA.s.substr(i+1));
        // debug(rSA.s.substr(n-1-i));
        cdq::addQ(0, i, x, y, 1, -1);
        // cdq.pb(i, x, y);
        // debug(i, x, y);
    }
    //debug(S, T);

    S = orgS, T = orgT;
    reverse(all(T));

    for (int i = 0; i < q; i++) {
        // debug(l, r);
        calc(n, pos[i], sz[i], i);
    }
    cdq::solve();
    for (int i = 0; i < q; i++)
        cout << cdq::ans[i] << '\n';
}
