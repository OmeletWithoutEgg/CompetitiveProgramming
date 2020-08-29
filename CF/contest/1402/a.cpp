#include <bits/stdc++.h>
#ifdef local
#define debug(...) QQBX(#__VA_ARGS__, __VA_ARGS__);
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
void QQBX(const char *s) {}
template <typename H, typename ...T> void QQBX(const char *s, const H& h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if(sizeof...(T)) QQBX(++s, args...);
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local

using namespace std;
typedef long long ll;
const int N = 100025, MOD = 1000000007;

#define int ll
struct seg {
    int h, l, r;
    seg(int h, int l, int r) : h(h), l(l), r(r) {}
};
int C2(int n) { return 1LL*n*(n+1)/2 % MOD; }
int n;
int h[N], w[N];
ll pre[N];
ll sum(int l, int r) {
    return ((r ? pre[r-1] : 0) - (l ? pre[l-1] : 0)) % MOD;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> h[i];
    for(int i = 0; i < n; i++) cin >> w[i];
    pre[0] = w[0];
    for(int i = 1; i < n; i++) pre[i] = pre[i-1] + w[i];
    int ans = 0;
    deque<seg> dq;
    int now = 0;
    for(int i = 0; i < n; i++) {
        while(dq.size() && dq.back().h >= h[i]) {
            auto [h, l, r] = dq.back();
            dq.pop_back();
            now = (now - C2(h) * sum(l, r) % MOD + MOD) % MOD;
        }
        /* for(seg s: dq) debug(s.l, s.r, s.h); */
        /* safe; */
        int l = dq.empty() ? 0 : dq.back().r;
        int r = i+1;
        dq.emplace_back(h[i], l, r);
        now = (now + C2(h[i]) * sum(l, r)) % MOD;
        debug(l, r);
        debug(now);

        ans = (ans + now * w[i]) % MOD;
        ans = (ans - C2(h[i]) * C2(w[i]-1) % MOD + MOD) % MOD;
        debug(C2(h[i])*C2(w[i]-1));
    }
    cout << ans << '\n';
}
