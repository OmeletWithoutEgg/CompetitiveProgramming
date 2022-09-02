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
#define get_pos(u,x) int(lower_bound(all(u),x)-begin(u))

using namespace std;
using ll = int_fast64_t;
using ld = long double;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
const int mod = 1000000007;
const int inf = mod;
const ll INF = 1e18;
const int maxn = 40;

ostream & operator<<(ostream &O, vector<int> v) {
    O << '[';
    int f = 0;
    for (int x: v) O << (f++ ? ", " : "") << x;
    return O << ']';
}

template <typename U, typename V>
void compress(vector<pair<U,V>> &v) {
    sort(v.begin(), v.end());
    size_t it = 0;
    for (size_t i = 0; i < v.size(); i++) {
        if (it == 0 || v[it-1].first != v[i].first)
            v[it++] = v[i];
        else
            v[it-1].second += v[i].second;
    }
    v.resize(it);
}
// map<vector<int>, ll> state[maxn];
vector<pair<uint32_t, uint32_t>> state[maxn];
uint32_t mask[2][2];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    string str;
    cin >> str;
    int n = str.size();

    for (int i = 1; i < n; i++)
        mask[str[i] - '0'][str[i-1] - '0'] |= 1LL << i;

    const uint32_t U = (1LL<<n) - 1;
    state[0].emplace_back(0, 1);
    // state[0][vector<int>(n)] = 1;
    for (int i = 0; i < n; i++) {
        compress(state[i]);
        for (auto [s, val]: state[i]) {
            for (int c = 0; c < 2; c++) {
                // maintain dp[j] - dp[j-1]
                // if (str[j] == c && str[j-1] != c):
                //      dp[i][j] - dp[i][j-1] = dp[i-1][j-1] - dp[i-1][j-1] + 1 = 1
                // if (str[j] == c && str[j-1] == c):
                //      dp[i][j] - dp[i][j-1] = dp[i-1][j-1] - dp[i-1][j-2] = diff[i-1][j-1]
                // if (str[j] != c && str[j-1] == c):
                //      dp[i][j] - dp[i][j-1] = dp[i-1][j] - dp[i][j-2] - 1 = diff[i-1][j] + diff[i-1][j-1] - 1
                // if (str[j] != c && str[j-1] != c):
                //      dp[i][j] - dp[i][j-1] = dp[i-1][j] - dp[i-1][j-1] = diff[i-1][j]
                uint32_t dp = 0;
                dp |= str[0] == char('0'+c);
                dp |= s & 1;
                dp |= mask[c][!c];
                dp |= (s << 1) & mask[c][c];
                dp |= s & mask[!c][!c];
                dp |= s & (s << 1) & mask[!c][c];
                uint32_t lost = mask[!c][c] & ~(s | (s << 1));
                while (lost) {
                    uint32_t lowbit = lost & -lost;
                    uint32_t sac = dp & ~(lowbit - 1);
                    dp ^= sac & -sac;
                    lost ^= lowbit;
                }
                /*
                for (int i = 0, c = 0; i < n; i++) {
                    if (lost >> i & 1) ++c;
                    if (c && (dp >> i & 1)) --c, dp ^= 1 << i;
                }
                */
                /*
                for (int j = 0; j < n; j++) {
                    if (str[j] == c) {
                        if (j == 0 || str[j-1] != c) {
                            dp[j] = 1;
                        } else {
                            dp[j] = j ? s[j-1] : 0;
                        }
                    } else {
                        if (j == 0 || str[j-1] != c)
                            dp[j] = s[j];
                        else {
                            if (!(s[j] | (j ? s[j-1] : 0))) {
                                assert (last == 0);
                                last = -1;
                            }
                            dp[j] = s[j] & (j ? s[j-1] : 0);
                        }
                    }
                    if (dp[j] && last < 0) last += 1, dp[j] = 0;
                }
                // debug(last, pref(s), pref(dp), c);
                auto dp = s;
                for (int j = 0; j < n; j++)
                    if (str[j] == char('0' + c))
                        dp[j] = (j ? s[j-1] : 0) + 1;
                    else
                        dp[j] = s[j];
                for (int j = 1; j < n; j++)
                    dp[j] = max(dp[j], dp[j-1]);
                */
                state[i+1].emplace_back(dp, val);
            }
        }
    }

    compress(state[n]);
    ll ans = 0;
    for (auto [s, val]: state[n]) {
        // ans += s.back() * val;
        ans += 1LL * __builtin_popcount(s) * val;
    }
    debug(state[n].size());
    ll cnt = 1LL << n;
    ll g = __gcd(cnt, ans);
    ans /= g;
    cnt /= g;
    if (cnt != 1)
        cout << ans << '/' << cnt << '\n';
    else
        cout << ans << '\n';
}
