// #define _GLIBCXX_DEBUG
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#ifdef local
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define pary(a...) danb(#a, a)
#define debug(a...) qqbx(#a, a)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\033[1;32m(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\033[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\033[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\033[0m\n";
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#define pary(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define pb emplace_back

using namespace std;
using ll = int64_t;
template <typename T> using max_heap = priority_queue<T, vector<T>, less<T>>;
const int maxn = 100025;
const long long inf = 1000000001;
const int prs[4] = {2, 3, 5, 7};
int bp[1 << 4];

int square_free(int x) {
    for (int p: prs)
        while (x % (p*p) == 0)
            x /= p;
    return x;
}
int mul(int a, int b) {
    return min(inf, 1LL*a*b);
}
int cnt[101];
int calc(int L) {
    vector<int> has;
    for (int j = 1; j <= 100; j++) if (cnt[j]) has.push_back(j);
    int ans = 0;
    for (int s = 0, U = (1<<4)-1; s < (1<<4); s++) {
        bool fail = false;
        int prod = 1;
        bool inProd[100] = {};
        for (int j: has) {
            bool coprime = (__gcd(j, bp[U ^ s]) == 1);
            if (coprime) {
                int bigPart = j / __gcd(j, 2 * 3 * 5 * 7);
                if (bigPart == 1) {
                    prod = inf;
                    break;
                } else {
                    if (!inProd[bigPart])
                        prod = mul(prod, bigPart);
                    inProd[bigPart] = true;
                }
            }
        }
        int M = L / bp[U ^ s] / prod;
        if (M == 0) continue;
        for (int m = s; ; m = (m-1) & s) {
            int coef = __builtin_parity(m) ? -1 : 1;
            ans += coef * (M / bp[m]);
            if (!m) break;
        }
    }

#ifdef local
    int c = 0;
    for (int i = 1; i <= L; i++) {
        bool ok = true;
        for (int j: has)
            if (__gcd(j, i) == 1)
                ok = false;
        if (ok)
            ++c;
    }
    pary(all(has));
    debug(ans, L, c);
#endif // local

    return ans;
}
signed main() {
    for (int s = 0; s < (1<<4); s++) {
        bp[s] = 1;
        for (int i = 0; i < 4; i++) if (s >> i & 1) bp[s] *= prs[i];
    }
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    assert( cin >> n >> m );
    vector<pair<int,int>> evt;
    for (int i = 0; i < m; i++) {
        int l, r, x;
        assert( cin >> l >> r >> x );
        assert( 1 <= l && l <= r && r <= n );
        assert( 1 <= x && x <= 100 );
        x = square_free(x);
        --l;
        evt.emplace_back(l, x);
        evt.emplace_back(r, -x);
    }
    evt.emplace_back(0, 0);
    evt.emplace_back(n, 0);
    sort(all(evt));
    int ans = 0;
    for (int i = 0, j = 0; i < evt.size(); i = j) {
        for (j = i; j < evt.size(); j++) {
            if (evt[j].first != evt[i].first) break;
            int x = evt[j].second;
            if (x > 0) {
                ++cnt[x];
            } else if (x < 0) {
                --cnt[-x];
            }
        }
        if (j == evt.size()) continue;
        int l = evt[i].first;
        int r = evt[j].first;
        int cur = calc(r) - calc(l);
        ans += cur;
        debug(l, r, cur);
    }
    cout << ans << '\n';
}

/*
15 2
1 15 3
1 15 15

10000 2
1 10000 22
1 10000 33
 */
