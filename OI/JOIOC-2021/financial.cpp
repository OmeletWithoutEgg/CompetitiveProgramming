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
const int maxn = 310025;
const int K = 200;
const int inf = 1e9 + 7;

// deque<pair<int,int>> dp[maxn];

int D;
struct SQRT {
    pair<int,int> single[maxn];
    vector<pair<int,int>> block[maxn / K + 1];
    vector<int> lazy[maxn / K + 1];
    int sz;
    void init(int n) {
        sz = (n / K + 1) * K;
        for (int i = 0; i < n; i++)
            single[i] = { 0, -inf };
    }
    int qry(pair<int,int> p, int atleast) {
        return p.second < atleast ? 0 : p.first;
    }
    void add(pair<int,int> &p, int atleast, int tag) {
        if (p.second >= atleast) p.second = tag;
    }
    int qry(vector<pair<int,int>> &dq, int atleast) {
        if (dq.empty()) return 0;
        int p = -1;
        for (int s = 1<<__lg(dq.size()); s; s>>=1) if (p+s < dq.size() && dq[p+s].second < atleast) p += s;
        ++p;
        return p < dq.size() ? dq[p].first : 0;
    }
    void add(vector<pair<int,int>> &dq, int atleast, int tag) {
        return;
        while (dq.size() && dq.back().second < atleast) dq.pop_back();
        if (!dq.empty()) {
            int len = dq.back().first;
            dq.clear();
            dq.emplace_back(len, tag);
        }
    }
    void push(int bid) {
        if (lazy[bid].empty())
            return;
        for (int i = bid * K; i < (bid+1)*K && i < sz; i++)
            add(single[i], lazy[bid].front() - D, lazy[bid].back());
        lazy[bid].clear();
    }
    int query(int l, int r, int atleast) {
        int res = 0;
        if (l % K != 0) push(l / K);
        if (r % K != 0) push(r / K);
        while (l % K != 0 && l < r)
            res = max(res, qry(single[l++], atleast));
        while (r % K != 0 && l < r)
            res = max(res, qry(single[--r], atleast));
        l /= K, r /= K;
        for (int i = l; i < r; i++) {
            if (lazy[i].size() && lazy[i].back() >= atleast) {
                if (block[i].size())
                    res = max(res, qry(block[i], lazy[i].front() - D));
            } else {
                res = max(res, qry(block[i], atleast));
            }
        }
        return res;
    }
    void build(int bid) {
        // assert (lazy[bid].empty());
        block[bid].assign(single + bid*K, single + (bid+1)*K);
        // debug(block[bid].size());
        sort(all(block[bid]), [](pair<int,int> a, pair<int,int> b){ return a.second < b.second; });
        int it = 0;
        for (int i = 0; i < block[bid].size(); i++) {
            while (it && block[bid][it-1].first <= block[bid][i].first)
                --it;
            block[bid][it++] = block[bid][i];
        }
        block[bid].resize(it);
    }
    void update(int l, int r, int atleast, int tag) {
        if (l % K != 0) {
            int lid = l / K;
            push(lid);
            while (l < (lid+1) * K && l < r)
                add(single[l++], atleast, tag);
            build(lid);
        }
        if (r % K != 0) {
            int rid = r / K;
            push(rid);
            while (r > rid * K && l < r)
                add(single[--r], atleast, tag);
            build(rid);
        }
        l /= K, r /= K;
        for (int i = l; i < r; i++) {
            add(block[i], atleast, tag);
            if (lazy[i].empty()) {
                lazy[i].push_back(tag);
            } else if (lazy[i].size() == 1) {
                if (lazy[i].back() < atleast)
                    lazy[i].clear();
                else
                    lazy[i].push_back(tag);
            } else if (lazy[i].size() == 2) {
                if (lazy[i].back() < atleast)
                    lazy[i].clear();
                else
                    lazy[i].back() = tag;
            }
        }
    }

    void edit(int p, int len, int id) {
        push(p / K);
        auto &dq = single[p];
        // while (dq.size() && dq.back().first <= len) dq.pop_back();
        // dq.emplace_back(len, id);
        dq = { len, id };
        build(p / K);
    }
} ds;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n >> D;
    vector<int> A(n);
    // for (int &x: A) cin >> x;
    for (int &x: A) x = rand();
    vector<int> u = A;
    sort(all(u));
    for (int &x: A) x = lower_bound(all(u), x) - u.begin();

    vector<int> cnt(n);
    iota(all(cnt), 0);
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
        ds.update(A[i], ds.sz, i - D, i);

        ds.edit(cnt[A[i]]++, len, i);
        /*
        while (dp[A[i]].size() && dp[A[i]].back().first <= len) dp[A[i]].pop_back();
        dp[A[i]].emplace_back(len, i);
        */
        ans = max(ans, len);
    }
    cout << ans << '\n';
}
