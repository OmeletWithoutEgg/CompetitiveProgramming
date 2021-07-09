#include <bits/stdc++.h>
#ifdef local
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(a...) qqbx(#a, a)
#define pary(a...) danb(#a, a)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\033[1;32m(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\033[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\033[1;32m[ " << s << " ] = [ ";
    for (auto it = L; it != R; ++it)
        std::cerr << *it << ' ';
    std::cerr << "]\033[0m\n";
}
#else
#define safe ((void)0)
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define pb emplace_back
#define get_pos(u,v) int(lower_bound(all(u), v) - u.begin())

using namespace std;
using ll = int64_t;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template <typename T> using max_heap = priority_queue<T, vector<T>, less<T>>;
const int maxn = 100025, inf = 1e9, MOD = 1000000007;
const ll INF = 1e18;

#define int ll
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<pair<int,int>> v(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v[i] = {x+y, x-y};
    }
    sort(all(v));

    auto f = [&v](int a, int b) {
        auto [xa, ya] = v[a];
        auto [xb, yb] = v[b];
        return max(abs(xa-xb), abs(ya-yb));
    };

    auto calc = [&](int L, bool ouf) {
        /* ll ans=0; */
        /* for (auto [X, Y]: v) */
        /*     for (auto [nX, nY]: v) { */
        /*         if (nX == X) break; */
        /*         if (nX >= X - L && Y-L <= nY && nY <= Y+L) ++ans; */
        /*     } */
        /* return ans; */
        vector<int> u;
        for (auto [X, Y]: v) u.pb(Y-L), u.pb(Y+L), u.pb(Y);

        set<pair<int,int>> st;
        auto erase = [&](int id) {
            st.erase({ v[id].second, id });
        };
        auto insert = [&](int id) {
            st.insert({ v[id].second, id });
        };
        
        vector<int> out;
        auto brute = [&](int i, int l, int r) {
            auto it = st.lower_bound({ l, 0 });
            while (it != st.end() && it->first <= r && out.size() <= k) {
                int j = it->second;
                ++it;
                out.pb(f(i, j));
            }
        };
        
        for (int i = 0, j = 0; i < n; i++) {
            while (v[j].first < v[i].first - L)
                erase(j++);
            debug( j, i );
            auto [X, Y] = v[i];
            brute(i, Y-L, Y+L);
            insert(i);
        }
        pary(all(out));
        if (ouf) {
            out.resize(k, L+1);
            sort(all(out));
            for (int x: out)
                cout << x << '\n';
        }
        return out.size() < k;
    };
    // max(X - X', Y - Y') <= k -> X' >= X-k, Y-k <= Y' <= Y+k
    ll ans = 0;
    for (ll s = 1LL << 31; s; s >>= 1) if (calc(ans + s, false)) ans += s;
    debug(ans);
    calc(ans, true);
}
