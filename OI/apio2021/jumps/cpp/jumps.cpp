#include "jumps.h"

#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
#define pary(x...) danb(#x, x)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\033[1;32m(" << s << ") = ("), ..., (std::cerr << a << (--cnt ? ", " : ")\033[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\033[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\033[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)

using namespace std;
const int maxn = 200025;
vector<int> H, L, R;
vector<int> pa;
vector<int> g[maxn];
vector<int> dep, in, ou;
vector<array<int,20>> to;
int tot;
void dfs(int i) {
    in[i] = tot++;
    for (int j: g[i]) {
        dep[j] = dep[i] + 1;
        dfs(j);
    }
    ou[i] = tot;
}

struct Segtree {
    pair<int,int> st[maxn * 2];
    int n;
    void build() {
        n = H.size();
        for (int i = 0; i < n; i++) st[i+n] = { H[i], i };
        for (int i = n-1; i > 0; i--) st[i] = max(st[i<<1], st[i<<1|1]);
    }
    pair<int,int> getMax(int l, int r) {
        pair<int,int> mx(-1e9, -1);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) mx = max(mx, st[l++]);
            if (r & 1) mx = max(mx, st[--r]);
        }
        return mx;
    }
} sgt;

void init(int N, std::vector<int> _H) {
    tot = 0;
    H = _H;
    L.resize(N);
    R.resize(N);
    pa.assign(N, -1);
    dep.assign(N+1, 0);
    in.assign(N, 0);
    ou.assign(N, 0);
    to.resize(N+1);
    vector<pair<int,int>> stk;
    for (int i = 0; i < N; i++) {
        while (stk.size() && stk.back().first <= H[i]) stk.pop_back();
        L[i] = stk.empty() ? -1 : stk.back().second;
        stk.emplace_back(H[i], i);
    }
    stk.clear();
    for (int i = N-1; i >= 0; i--) {
        while (stk.size() && stk.back().first <= H[i]) stk.pop_back();
        R[i] = stk.empty() ? -1 : stk.back().second;
        stk.emplace_back(H[i], i);
    }

    int root = -1;
    for (int i = 0; i < N; i++) {
        if (L[i] == -1 && R[i] == -1) {
            root = i;
        } else if (L[i] == -1) {
            pa[i] = R[i];
        } else if (R[i] == -1) {
            pa[i] = L[i];
        } else {
            pa[i] = H[L[i]] > H[R[i]] ? R[i] : L[i];
        }
    }
    for (int i = 0; i < N; i++) if (i != root) g[pa[i]].push_back(i);
    dfs(root);
    safe;
    dep[N] = -1;
    H.push_back(int(1e9));
    
    for (int i = 0; i < N; i++) {
        if (L[i] == -1 && R[i] == -1) {
            to[i][0] = N;
        } else if (L[i] == -1) {
            to[i][0] = R[i];
        } else if (R[i] == -1) {
            to[i][0] = L[i];
        } else {
            to[i][0] = H[L[i]] > H[R[i]] ? L[i] : R[i];
        }
    }
    to[N][0] = N;
    for (int L = 1; L < 20; L++)
        for (int i = 0; i <= N; i++)
            to[i][L] = to[to[i][L-1]][L-1];
    sgt.build();
    safe;
}

int query(int l, int r, int lim) {
    int L = r;
    for (int s = 1 << 20; s; s >>= 1) if (L - s >= l && sgt.getMax(L-s, r).first <= lim) L -= s;
    return sgt.getMax(L, r).second;
}

int minimum_jumps(int A, int B, int C, int D) {
    if (C == D) {
        int y = C;
        int x = query(A, B+1, H[y]);
        debug(x);
        /*
        int x = -1;
        for (int i = B; i >= A; i--) {
            if (H[i] > H[y])
                break;
            if (x == -1 || H[x] < H[i])
                x = i;
        }
        */
        if (x == -1)
            return -1;
        if (in[y] <= in[x] && in[x] < ou[y]) {
            int ans = 0;
            for (int L = 19; L >= 0; L--)
                if (H[to[x][L]] <= H[y])
                    x = to[x][L], ans += 1 << L;
            debug(x);
            ans += dep[x] - dep[y];
            return ans;
        } else 
            return -1;
    }
    return -7122;
}
