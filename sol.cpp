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
#define pb emplace_back

using namespace std;
const int N = 24;

int p[N], l[N], r[N], g[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> l[i] >> r[i];
    for(int i = 0; i < n; i++) {
        g[i] = 1 << i;
        for(int j = 0; j < n; j++) {
            if(j == i) continue;
            if((l[i] < l[j] && l[j] < r[i]) ^ (l[i] < r[j] && r[j] < r[i])) {
                g[i] |= 1 << j;
            }
        }
    }
    int ans = n;
    iota(p, p+n, 0);
    mt19937 rng(7122);
    for(int c = 0; c < 50; c++) {
        shuffle(p, p+n, rng);
        vector<int> now;
        for(int i = 0; i < n; i++) {
            bool found = false;
            for(int &x: now) {
                if(~x >> p[i] & 1) {
                    x |= g[p[i]];
                    found = true;
                    break;
                }
            }
            if(!found) now.pb(g[p[i]]);
        }
        ans = min(ans, int(now.size()));
        /* next_permutation(p, p+n); */
    }
    cout << ans << '\n';
}
