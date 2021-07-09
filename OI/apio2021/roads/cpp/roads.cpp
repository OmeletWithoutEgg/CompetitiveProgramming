#pragma GCC optimize("Ofast")
#include "roads.h"

// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
#define pary(x...) danb(#x, x)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\033[1;32m(" << s << ") = ("), ..., (std::cerr << a << (--cnt ? ", " : ")\033[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\033[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\033[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)
using namespace std;
using ll = long long;
const int maxn = 100025;

vector<pair<int,int>> g[maxn];
bool isBig[maxn];
ll dp[maxn][2];
int vis[maxn];
void dfs(int k, int i, int p) {
    ll sum = 0;
    vector<ll> tmp;
    for (auto [j, w]: g[i]) {
        if (j != p) {
            dfs(k, j, i);
            sum += dp[j][0] + w;
            ll t = dp[j][1] - dp[j][0] - w;
            if (t < 0)
                tmp.push_back(t);
        }
    }
    // dp[i][0]: at most k
    dp[i][0] = dp[i][1] = sum;
    if (tmp.size() >= k) {
        nth_element(tmp.begin(), tmp.begin() + k, tmp.end());
    }
    for (int s = 0; s < k && s < tmp.size(); s++)
        dp[i][0] += tmp[s];
    if (tmp.size() >= k-1) {
        nth_element(tmp.begin(), tmp.begin() + k-1, tmp.end());
    }
    for (int s = 0; s < k-1 && s < tmp.size(); s++)
        dp[i][1] += tmp[s];
    // debug(i, dp[i][0], dp[i][1]);
}

vector<pair<int,int>> bigNeiId[maxn];
vector<int> smallNei[maxn];
vector<ll> smallPre[maxn];
void dfs2(int k, int i, int p) {
    vis[i] = k;
    ll sum = -smallPre[i].back();
    // debug(i);
    // pary(all(smallNei[i]));
    // debug(sum);
    vector<ll> tmp;
    for (auto [j, w]: bigNeiId[i]) {
        if (j != p) {
            dfs2(k, j, i);
            sum += dp[j][0] + w;
            ll t = dp[j][1] - dp[j][0] - w;
            if (t < 0)
                tmp.push_back(t);
        }
    }
    dp[i][0] = dp[i][1] = sum;
    /*
    tmp.insert(tmp.end(), all(smallNei[i]));
    sort(all(tmp));
    if (tmp.size() >= k) {
        nth_element(tmp.begin(), tmp.begin() + k, tmp.end());
    }
    for (int s = 0; s < k && s < tmp.size(); s++)
        dp[i][0] += tmp[s];
    if (tmp.size() >= k-1) {
        nth_element(tmp.begin(), tmp.begin() + k-1, tmp.end());
    }
    for (int s = 0; s < k-1 && s < tmp.size(); s++)
        dp[i][1] += tmp[s];
    // debug(i, dp[i][0], dp[i][1]);
    return;
    */
    if (tmp.empty()) {
        dp[i][0] += smallPre[i][k];
        dp[i][1] += smallPre[i][k-1];
        return;
    }
    sort(all(tmp));
    for (int s = tmp.size() - 1; s >= 0; s--) {
        int rk = (lower_bound(all(smallNei[i]), tmp[s]) - smallNei[i].begin());
        if (rk + s + 1 <= k) {
            dp[i][0] += smallPre[i][k - s-1];
            for (int j = 0; j <= s; j++)
                dp[i][0] += tmp[j];
            break;
        }
        if (s == 0) {
            dp[i][0] += smallPre[i][k];
        }
    }
    for (int s = tmp.size() - 1; s >= 0; s--) {
        int rk = (lower_bound(all(smallNei[i]), tmp[s]) - smallNei[i].begin());
        if (rk + s + 1 <= k-1) {
            dp[i][1] += smallPre[i][k-1 - s-1];
            for (int j = 0; j <= s; j++)
                dp[i][1] += tmp[j];
            break;
        }
        if (s == 0) {
            dp[i][1] += smallPre[i][k-1];
        }
    }
}
vector<long long> minimum_closure_costs(int N, vector<int> U,
                                             vector<int> V,
                                             vector<int> W) {
    for (int i = 0; i < N-1; i++) {
        g[U[i]].emplace_back(V[i], W[i]);
        g[V[i]].emplace_back(U[i], W[i]);
    }
    vector<long long> ans(N);
    const int K = 300;
    safe;
    for (int k = 0; k < K && k < N; k++) {
        dfs(k, 0, -1);
        debug(k);
        ans[k] = dp[0][0];
        if (ans[k] == 0) break;
    }
    safe;
    vector<int> big;
    for (int i = 0; i < N; i++) if (g[i].size() >= K) big.push_back(i), isBig[i] = true;
    for (int i = 0; i < N; i++) vis[i] = -1;

    for (int i = 0; i < N; i++) {
        if (!isBig[i]) continue;
        for (auto [j, w]: g[i]) {
            if (!isBig[j]) {
                smallNei[i].push_back(-w);
            } else {
                bigNeiId[i].emplace_back(j, w);
            }
        }
        sort(all(smallNei[i]));
        smallPre[i].resize(N+1);
        for (int j = 0; j < N; j++)
            smallPre[i][j+1] = smallPre[i][j] + (j < smallNei[i].size() ? smallNei[i][j] : 0);
    }
    for (int k = K; k < N; k++) {
        for (int x: big) if (vis[x] != k) {
            // debug(x);
            dfs2(k, x, -1);
            ans[k] += dp[x][0];
        }
        debug(ans[k]);
        if (ans[k] == 0) break;
    }
    return ans;
}
