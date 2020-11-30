#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#include <bits/stdc++.h>

using namespace std;
const int N = 1025, K = 20;

int prv[N][K], dp[1<<K];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int k;
        string s;
        cin >> k >> s;
        int n = s.size();
        for(int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            for(int j = 0; j < k; j++) {
                if(j == c) prv[i][j] = i;
                else prv[i][j] = i ? prv[i-1][j] : -1;
            }
        }
        fill(dp, dp+(1<<k), 1e9);
        dp[0] = n;
        bool ans = true;
        for(int s = 0, U = (1<<k)-1; s < (1<<k); s++) {
            if(dp[s] <= 0) {
                ans = false;
                break;
            }
            for(int m = U ^ s; m; m -= m&-m) {
                int l = m & -m;
                int i = 31 - __builtin_clz(l);
                dp[s | l] = min(dp[s | l], prv[dp[s] - 1][i]);
            }
        }
        if(ans) cout << "Yes\n";
        else cout << "No\n";
    }
}
