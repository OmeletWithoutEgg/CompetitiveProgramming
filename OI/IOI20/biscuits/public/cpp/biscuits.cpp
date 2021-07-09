#include "biscuits.h"
#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "\e[1;32m(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\e[0m\n")));
}
#else
#define debug(...) ((void)0)
#endif
using namespace std;

const int maxn = 65;
long long suf[maxn];
unordered_map<long long, long long> dp[maxn];
int cnt = 0;
long long dfs(vector<long long> &a, long long x, int i, long long carry) {
    if (i == a.size()) {
        return carry / x + 1;
    }
    ++cnt;
    if (dp[i].count(carry))
        return dp[i][carry];
    long long &res = dp[i][carry];
    carry += a[i];
    if (carry + suf[i] < x)
        return res = 1;
    res += dfs(a, x, i+1, carry / 2); // y >> i & 1 == 0
    if (carry >= x)
        res += dfs(a, x, i+1, (carry - x) / 2);
    return res;
}
long long count_tastiness(long long x, std::vector<long long> a) {
    for (int i = 0; i < a.size(); i++) dp[i].clear();
    for (int i = 0; i+1 < a.size(); i++) {
        if (a[i] >= x) {
            long long diff = (a[i] - x) / 2;
            a[i] -= diff * 2;
            a[i+1] += diff;
        }
    }
    for (int i = 0; i < a.size(); i++) {
        suf[i] = 0;
        for (int j = i+1; j < a.size(); j++) {
            suf[i] += a[j] << (j - i);
        }
    }
    for (int i = 0; i < a.size(); i++)
        cerr<<a[i]<<(i+1==a.size()?'\n':',');
    long long res = dfs(a, x, 0, 0);
    debug(cnt);
    return res;
}

