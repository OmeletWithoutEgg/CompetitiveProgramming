#include <bits/stdc++.h>
#ifdef local
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
void qqbx(const char *s) {}
template <typename H, typename ...T> void qqbx(const char *s, const H& h, T&& ...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if(sizeof...(T)) qqbx(++s, args...);
}
#endif // local

using namespace std;
using ll = int64_t;
using ld = long double;
const ll INF = 1e18;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    auto f = [](ll n, ll b) {
        if(b < 10) return -INF;
        ll p = 1, ans = 0;
        while(n) {
            if(n%b >= 10) return -INF;
            ans += p * (n%b);
            p *= 10;
            n /= b;
        }
        return ans;
    };
    ll Y, L;
    while(cin >> Y >> L) {
        ll ans = 10;
        for(ll b = 10; b*b*b <= Y; b++) if(f(Y, b) >= L) ans = max(ans, b); // covers at least 4 digits
        // 3 digits
        for(int i = 100; i < 1000; i++) if(i >= L) {
            ll a = i/100, b = i/10%10, c = i%10;
            // aB^2+bB+c = Y
            ld D = b*b-4.*a*(c-Y);
            if(D < 0) continue;
            ll B = floor((-b + sqrt(D)) / (2*a));
            if(a*B*B + b*B + c == Y) ans = max(ans, B);
            ++B;
            if(a*B*B + b*B + c == Y) ans = max(ans, B);
        }
        // 2 digits
        for(int i = 10; i < 100; i++) if(i >= L) {
            // i/10*B + i%10 = Y
            ll a = i/10, b = i%10;
            if(Y>=b && (Y-b)%a == 0) ans = max(ans, (Y-b) / a);
        }
        cout << ans << '\n';
    }
}
