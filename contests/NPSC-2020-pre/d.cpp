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
const int N = 41, MOD = 1000000007;

int inv[N*N*N];
int val[N][N];
int n;
map<vector<int>,int> mp;
int C2(int n) { return n * (n-1) / 2; }
int DP(int G[]) {
    for(int i = 1; i <= n; i++) if(G[i] < 0) return 0;
    if(G[n] == 1) return 0;
    if(mp.count(vector<int>(G+1, G+n))) return mp[vector<int>(G+1, G+n)];
    int &ans = mp[vector<int>(G+1, G+n)];
    ans = 1;
    int H[41];
    for(int i = 1; i <= n; i++) H[i] = G[i];
    int i = 0;
    for(int A = 1; A <= n; A++) if(G[A]) {
        int j = 0;
        for(int B = 1; B <= n && A+B <= n; B++) if(G[B]) {
            if(j > i) break;
            --H[A], --H[B], ++H[A+B];
            int p = 1LL * A * B * (A == B ? C2(G[A]) : G[A] * G[B]) * inv[C2(n)] % MOD;
            ans = (ans + 1LL * (DP(H) + val[A][B]) * p) % MOD;
            ++H[A], ++H[B], --H[A+B];
            j++;
        }
        i++;
    }
    int sum = C2(n);
    for(int C = 1; C <= n; C++) sum -= C2(C) * G[C];
    int p = 1LL * C2(n) * inv[sum] % MOD;
    ans = 1LL * ans * p % MOD;
    return ans;
}
signed main() {
    inv[1] = 1;
    for(int i = 2; i < N*N*N; i++) inv[i] = 1LL * (MOD - MOD/i) * inv[MOD % i] % MOD;
    ios_base::sync_with_stdio(0), cin.tie(0);
    /* n = 40; */
    /* for(int i = 1; i <= n; i++) for(int j = 1; j <= i && i+j <= n; j++) val[i][j] = val[j][i] = rand() % MOD; */
    // for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cout << val[i][j] << (j==n ? '\n' : ' ');
    cin >> n;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin >> val[i][j];
    int G[41] = {0, n};
    cout << DP(G) << '\n';
}
