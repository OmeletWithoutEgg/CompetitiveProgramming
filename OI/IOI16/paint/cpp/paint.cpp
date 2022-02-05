#include "paint.h"
#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
#define pary(x...) danb(#x, x)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\e[1;32m(" << s << ") = ("), ..., (std::cerr << a << (--cnt ? ", " : ")\e[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\e[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\e[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)

using namespace std;
const int maxn = 200025;
int white[maxn], black[maxn], white_sum[maxn], black_sum[maxn];
int pre_dp[maxn][225];
int suf_dp[maxn][225];
int maybe_black[maxn];
int maybe_white[maxn];
std::string solve_puzzle(std::string s, std::vector<int> c) {
    int n = s.size();
    int k = c.size();
    for (int i = 0; i < n; i++)
        if (s[i] == '_')
            white[i+1] = 1;
        else if (s[i] == 'X')
            black[i+1] = 1;
    for (int i = 1; i <= n; i++)
        white_sum[i] = white_sum[i-1] + white[i];
    for (int i = 1; i <= n; i++)
        black_sum[i] = black_sum[i-1] + black[i];

    pre_dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k*2+1; j++) {
            if (j & 1) {
                int id = j >> 1;
                if (i >= c[id] && white_sum[i] - white_sum[i-c[id]] == 0) {
                    pre_dp[i][j] = pre_dp[i-c[id]][j-1];
                } else {
                    pre_dp[i][j] = false;
                }
            } else {
                if (black[i] == 0) {
                    pre_dp[i][j] = pre_dp[i-1][j];
                    if (j != 0)
                        pre_dp[i][j] |= pre_dp[i-1][j-1];
                } else {
                    pre_dp[i][j] = false;
                }
            }
        }
    }
    assert (pre_dp[n][k*2] || pre_dp[n][k*2-1]);
    suf_dp[n+1][k*2] = 1;
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < k*2+1; j++) {
            if (j & 1) {
                int id = j >> 1;
                if (i + c[id] - 1 <= n && white_sum[i + c[id] - 1] - white_sum[i - 1] == 0) {
                    suf_dp[i][j] = suf_dp[i+c[id]][j+1];
                } else {
                    suf_dp[i][j] = false;
                }
            } else {
                if (black[i] == 0) {
                    suf_dp[i][j] = suf_dp[i+1][j];
                    if (j != k * 2)
                        suf_dp[i][j] |= suf_dp[i+1][j+1];
                } else {
                    suf_dp[i][j] = false;
                }
            }
        }
    }
    assert(suf_dp[1][0] || suf_dp[1][1]);

    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k*2+1; j++)
            cerr << pre_dp[i][j];
        cerr << '\n';
    }
    */

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            if (pre_dp[i][j*2+1] && suf_dp[i+1][j*2+2]) {
                debug(i, j);
                // (i-c[j], i] can be black
                maybe_black[i-c[j]+1] += 1;
                maybe_black[i+1] -= 1;
            }
        }
    }
    for (int i = 1; i <= n; i++) maybe_black[i] += maybe_black[i-1];
    debug(suf_dp[3][0]);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            if (pre_dp[i][j*2] && suf_dp[i][j*2]) {
                // i can be white
                maybe_white[i] = 1;
            }
        }
    }
    string ans;
    for (int i = 1; i <= n; i++) {
        if (maybe_black[i] && maybe_white[i])
            ans += '?';
        else if (maybe_black[i])
            ans += 'X';
        else if (maybe_white[i])
            ans += '_';
        else
            exit(3);
    }
    pary(maybe_black+1, maybe_black+n+1);
    pary(maybe_white+1, maybe_white+n+1);
    return ans;
}
