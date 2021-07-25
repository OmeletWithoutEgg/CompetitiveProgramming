#include <bits/stdc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
#define TAK(args...) std::ostream& operator<<(std::ostream &O, args)
#define NIE(STL, BEG, END, OUT) template <typename ...T> TAK(std::STL<T...> v) \
    { O << BEG; int f=0; for(auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }
NIE(deque, "[", "]", e) ; NIE(vector, "[", "]", e)
NIE(set, "{", "}", e) ; NIE(multiset, "{", "}", e) ; NIE(unordered_set, "{", "}", e)
NIE(map , "{", "}", e.first << ":" << e.second)
NIE(unordered_map , "{", "}", e.first << ":" << e.second)
template <typename ...T> TAK(std::pair<T...> p) { return O << '(' << p.first << ',' << p.second << ')'; }
template <typename T, size_t N> TAK(std::array<T,N> a) { return O << std::vector<T>(a.begin(), a.end()); }
template <typename ...T> TAK(std::tuple<T...> t) {
    return O << "(", std::apply([&O](T ...s){ int f=0; (..., (O << (f++ ? ", " : "") << s)); }, t), O << ")";
}
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    if(!cnt) return std::cerr << "\033[1;32m() = ()\033\[0m\n", void();
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
}

using namespace std;
using ll = long long;
const int maxn = 500025;
const int inf = 1000000007;

#define TIME Timer __timer(__PRETTY_FUNCTION__)
class Timer {
private:
    std::string title;
    chrono::high_resolution_clock::time_point start;
public:
    Timer(std::string t) :
        title(t), start(chrono::high_resolution_clock::now()) {}
    ~Timer() {
        auto finish = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
        double ms = double(duration) * 0.001;
        std::cerr << "Timer: " << title << " takes " << ms << " ms to finish.\n";
    }
};

signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> t(n), s(n), d(n);
    for (int i = 1; i < n; i++) cin >> t[i];
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) cin >> d[i];

    auto bs = [&s, &d](int p, int m) {
        auto calc = [&](int x) -> pair<ll,ll> {
            ll cnt = 0;
            ll sum = 0;
            // take all cost > x
            for (int i = 0; i < p; i++) {
                if (s[i] <= x) continue;
                // s[i] - d[i] * c > x
                // c < (s[i] - x) / d[i]
                if (d[i] == 0) {
                    return { inf, 0 };
                }
                ll c = (s[i] - x - 1) / d[i] + 1;
                cnt += c;
                sum += 1LL * (s[i] * 2 - (c-1) * d[i]) * c / 2;
            }
            return { cnt, sum };
        };
        int x = -1;
        for (int s = 1<<29; s; s >>= 1)
            if (calc(x + s).first > m)
                x += s;
        ++x;
        auto [cnt, sum] = calc(x);
        assert (cnt <= m);
        assert (x==0 || calc(x-1).first > m);
        return sum + x * (m - cnt);
    };
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (i) m -= t[i];
        if (m <= 0) break;
        ans = max(ans, bs(i+1, m));
    }
    cout << ans << '\n';
    debug(ans);
}
