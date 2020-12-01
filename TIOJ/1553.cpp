#include <cstdio>

inline int min(int a, int b) {return a<b?a:b;}
inline int max(int a, int b) {return a>b?a:b;}
const int N = 225;

int n, v[N], dp[N][N], sum, cnt, mx = 0;
signed main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", v+i);
    for(int i = 0; i < n; i++) sum += v[i];
    for(int L = 1; L <= n-1; L++) {
        for(int i = 0; i < n; i++) {
            if(n-L & 1) {
                dp[i][L] = min(dp[i][L-1], dp[(i+1)%n][L-1]);
            }else {
                dp[i][L] = max(dp[i][L-1]+v[(i+L-1)%n], dp[(i+1)%n][L-1]+v[i]);
            }
            //cout << dp[i][L] << ' ';
        }
        //cout << '\n';
    }
    //for(int i = 0; i < n; i++) cout << v[i]+dp[(i+1)%n][n-1] << ' '; cout << '\n';
    //debug(sum);
    for(int i = 0; i < n; i++) {
        int t = v[i]+dp[(i+1)%n][n-1];
        if(t > mx) mx = t;
        if(t > sum-t) ++cnt;
    }
    printf("%d %d\n", cnt, mx);
}
