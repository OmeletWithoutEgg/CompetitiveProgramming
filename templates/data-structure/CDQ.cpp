namespace cdq {
    const int maxn = 1000000;
    struct Fenwick {
        int sum[maxn];
        void add(int p, int d) {
            for (; p < maxn; p += p & -p) sum[p] += d;
        }
        int qry(int p) {
            int res = 0;
            for (; p > 0; p -= p & -p) res += sum[p];
            return res;
        }
    } BB;
    struct Query {
        int t;
        int x, y, z;
        int v;
        int id;
    } Q[maxn];
    int tot;
    int64_t ans[maxn];
    void addQ(int t, int x, int y, int z, int v, int id) {
        Q[tot++] = {t, x, y, z, v, id};
    }
    bool cmp(const Query &a, const Query &b) {
        return a.y != b.y ? a.y < b.y : a.t < b.t;
    }
    void solve(int l, int r) {
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
