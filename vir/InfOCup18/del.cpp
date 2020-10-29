#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)

using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for(int i = 0; i < q; i++) {
        int x;
        cin >> x;
        --x;
        v[x] = true;
    }
    int last = 0, flag = 0;
    for(int i = 0, j = 0; i < n; i = j) {
        for(j = i; j < n; j++) if(v[i] != v[j]) break;
        if(v[i]) {
            if(last & 1) {
                if(j-i > 1) return cout << -1 << '\n', void();
                ans.pb(i);
                last -= 1;
                flag = 1;
            }
        } else {
            last = j - i - flag;
        }
    }

}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--) solve();
}
