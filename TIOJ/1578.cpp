#include <iostream>

using namespace std;
const int N = 30;

long long dp[N][N];
inline long long sub(long long a, long long b){
    //cout << a << ',' << b << '\n';
    return (a*b)/(b-a);
}
signed main(){
    for(int i = 1; i <= 29; i++) {
        dp[i][1] = dp[i][i] = i;
        for(int j = 2; j < i; j++) dp[i][j] = sub(dp[i-1][j-1],dp[i][j-1]);
    }
    int r,c;
    cin >> r >> c;
    cout << dp[r][c] << '\n';
}
