#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
#define pary(x...) danb(#x, x)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\e[1;32m(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\e[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\e[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\e[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
const int K = 200;
const int maxn = 300025 + K;
const int inf = 1e9 + 7;

// deque<pair<int,int>> dp[maxn];

int D;
struct Segtree {
    using Lazy = vector<int>;
    deque<pair<int,int>> st[maxn * 2];
    Lazy lazy[maxn];
    int n;
    void init(int _n) {
        n = _n;
    }
    int qry(deque<pair<int,int>> &dq, int atleast) {
        while (dq.size() && dq.front().second < atleast) dq.pop_front();
        return dq.empty() ? 0 : dq.front().first;
    }
    void add(deque<pair<int,int>> &dq, int atleast, int tag) {
        while (dq.size() && dq.front().second < atleast) dq.pop_front();
        if (!dq.empty())
            dq.resize(1), dq.front().second = tag;
    }
    void add(deque<pair<int,int>> &dq, Lazy &lz) {
        if (lz.empty()) return;
        add(dq, lz.front() - D, lz.back());
    }
    void add(Lazy &lz, int atleast, int tag) {
        if (lz.empty()) {
            lz.push_back(tag);
        } else if (lz.size() == 1) {
            if (lz.back() < atleast)
                lz.clear();
            else
                lz.push_back(tag);
        } else if (lz.size() == 2) {
            if (lz.back() < atleast)
                lz.clear();
            else
                lz.back() = tag;
        }
    }
    void add(Lazy &lhs, Lazy &rhs) {
        if (rhs.empty()) return;
        add(lhs, rhs.front() - D, rhs.back());
    }
    void upd(int p, int atleast, int tag) {
        add(st[p], atleast, tag);
        if (p < n) add(lazy[p], atleast, tag);
    }
    void upd(int p, Lazy &lz) {
        add(st[p], lz);
        if (p < n) add(lazy[p], lz);
    }
    void push(int p) {
        for (int h = __lg(n); h >= 0; h--) {
            int i = p >> h;
            if (lazy[i>>1].empty()) continue;
            upd(i, lazy[i>>1]);
            upd(i^1, lazy[i>>1]);
            lazy[i>>1].clear();
        }
    }
    int query(int l, int r, int atleast) {
        int res = 0;
        push(l+n), push(r-1+n);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = max(res, qry(st[l++], atleast));
            if (r&1) res = max(res, qry(st[l++], atleast));
        }
        return res;
    }
    void update(int l, int r, int atleast, int tag) {
        push(l+n), push(r-1+n);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1)
                upd(l++, atleast, tag);
            if (r&1)
                upd(--r, atleast, tag);
        }
    }

    void edit(int p, int len, int id) {
        push(p+n);
        for (p += n; p; p >>= 1) {
            auto &dq = st[p];
            while (dq.size() && dq.back().first <= len) dq.pop_back();
            dq.emplace_back(len, id);
        }
    }
} ds;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n >> D;
    vector<int> A(n);
    for (int &x: A) cin >> x;
    // for (int &x: A) x = rand();
    vector<int> u = A;
    sort(all(u));
    u.erase(unique(all(u)), u.end());
    for (int &x: A) x = lower_bound(all(u), x) - u.begin();

    ds.init(n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        /*
        int len = 0;
        for (int j = 0; j < A[i]; j++) {
            while (dp[j].size() && dp[j].front().second < i - D) dp[j].pop_front();
            if (dp[j].size())
                len = max(len, dp[j].front().first);
        }
        ++len;
        */
        int len = ds.query(0, A[i], i - D) + 1;

        /*
        for (int j = A[i]; j < n; j++) {
            while (dp[j].size() && dp[j].front().second < i - D) dp[j].pop_front();
            if (dp[j].size())
                dp[j].resize(1), dp[j].front().second = i;
        }
        */
        ds.update(A[i], n, i - D, i);

        ds.edit(A[i], len, i);
        /*
        while (dp[A[i]].size() && dp[A[i]].back().first <= len) dp[A[i]].pop_back();
        dp[A[i]].emplace_back(len, i);
        */
        ans = max(ans, len);
    }
    cout << ans << '\n';
}
