#include <bits/stdc++.h>
#define pb emplace_back
#define all(v) begin(v),end(v)
#define ff first
#define ss second
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
}
#endif // local

using namespace std;
using ll = long long;
const int N = 1025;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    deque<pair<int,int>> dq;
    dq.pb(0, n);
    for(int i = 0; i < q; i++) {
        int k;
        cin >> k;
        dq.front().second -= 1, dq.front().first += 1;
        if(dq.front().second == 0) dq.pop_front();
        int now = 0;
        ll ans = 0;
        while(dq.size()) {
            int d = min(k, dq.front().second);
            ans += 1LL * d * (dq.front().first - now);
            now += d;
            k -= d;
            if(d == dq.front().second) {
                dq.pop_front();
            } else {
                dq.front().second -= d, dq.front().first += d;
                break;
            }
        }
        dq.emplace_front(0, now);
        cout << ans << (i+1==q ? '\n' : ' ');
    }
}
