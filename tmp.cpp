#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
const int maxn = 155, mod = 998244353, sigma = 6;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    set<int> st;
    set<pair<int,int>> intervals; // near dist, pos
    auto calc = [](int L, int R) -> pair<int,int> {
        int M = (L+R)/2;
        return { L - M, M }; // notice the L-M
    };

    st.insert(0), st.insert(n+1);
    intervals.insert(calc(0, n+1));
    auto insert = [&](int p) {
        auto it = st.lower_bound(p);
        if(it != st.end() && it != st.begin()) {
            int L = *prev(it);
            int R = *it;
            assert(L+1 != R);
            intervals.erase(calc(L, R));
        }
        if(it != st.end()) {
            int L = p;
            int R = *it;
            if(L+1 != R)
                intervals.insert(calc(L, R));
        }
        if(it != st.begin()) {
            int L = *prev(it);
            int R = p;
            if(L+1 != R)
                intervals.insert(calc(L, R));
        }
        st.insert(p);
    };

    auto erase = [&](int p) {
        st.erase(p);
        auto it = st.lower_bound(p);
        if(it != st.end()) {
            int L = p;
            int R = *it;
            if(L+1 != R)
                intervals.erase(calc(L, R));
        }
        if(it != st.begin()) {
            int L = *prev(it);
            int R = p;
            if(L+1 != R)
                intervals.erase(calc(L, R));
        }
        if(it != st.end() && it != st.begin()) {
            int L = *prev(it);
            int R = *it;
            assert(L+1 != R);
            intervals.insert(calc(L, R));
        }
    };

    auto getInsertPos = [&]() {
        if(intervals.empty()) return -1;
        return intervals.begin() -> second;
    };
    map<int, vector<int>> mp;
    for(int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        if(a) {
            insert(i);
            mp[a].pb(i);
        }
    }
    for(int i = 0; i < q; i++) {
        int t, k;
        cin >> t >> k;
        if(t == 0) {
            int p = getInsertPos();
            if(p != -1)
                insert(p);
            cout << p << '\n';
            mp[k].pb(p);
        } else {
            for(int p: mp[k])
                erase(p);
            mp.erase(k);
        }
    }
}
