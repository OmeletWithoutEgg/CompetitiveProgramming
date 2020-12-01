#include <iostream>
using namespace std;
const int N = 21, K = 7;

long long dp[N][N*K][1<<K];
int pc[1<<K];
signed main() {
    int n,m,k;
    cin >> n >> m >> k;
    for(int i = 1; i < (1<<m); i++) pc[i] = pc[i-(i&-i)] + 1;
    dp[0][0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int s = 0; s < (1<<m); s++) {
            for(int t = 0; t < (1<<m); t++) if(!(pc[t]&1)) {
                for(int c = pc[t]; c <= k; c++) {
                    dp[i][s][c] += dp[i-1][s^t][c-pc[t]];
                }
            }
        }
    }
    cout << dp[n][0][k] << '\n';
}

