#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
const int N = 1000025;

int solve(const vector<int> &v, int now) {
    if(v.empty()) return 0;
    int ans = *max_element(v.begin(), v.end());
    int last = 0, n = v.size();
    vector<int> tmp;
    for(int i = 0, j = 0; i < n; i = j) {
        for(j = i; j < n; j++) if(v[i] != v[j]) break;
        int len = j - i;
        if(v[i] == now) {
            if(len & 1) {
                for(int t = 0; t < len/2; t++) tmp.pb(now+1);
                ans = max(ans, solve(tmp, now+1));
                tmp.clear();
                for(int t = 0; t < len/2; t++) tmp.pb(now+1);
            } else {
                for(int t = 0; t < len/2; t++) tmp.pb(now+1);
            }
        } else {
            for(int t = 0; t < len; t++) tmp.pb(v[i]);
        }
    }
    ans = max(ans, solve(tmp, now+1));
    return ans;
}
signed main() {
#ifndef local
    freopen("262144.in", "r", stdin);
    freopen("262144.out", "w", stdout);
#endif // local
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    cout << solve(v, 1) << '\n';
}
