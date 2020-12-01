#include <bits/stdc++.h>

using namespace std;
const long long N = 1000;

string s,t;
int dp[N+1][N+1] = {}, n;
char S[N+1][N+1] = {};
signed main(){
    cin >> s, t = s, reverse(t.begin(),t.end()), n = s.size();
    for(int i = 0;i < n;i++) if(s[i]==t[0]) dp[i][0] = s[i]==t[0];
    for(int j = 0;j < n;j++) dp[0][j] = s[0]==t[j];
    for(int i = 1;i < n;i++)
        for(int j = 1;j < n;j++){
            if(dp[i][j]<dp[i-1][j]) dp[i][j]=dp[i-1][j], S[i][j] = '$';
            if(dp[i][j]<dp[i][j-1]) dp[i][j]=dp[i][j-1], S[i][j] = '$';
            if(s[i] == t[j] && dp[i][j]<dp[i-1][j-1]+1)
                dp[i][j] = dp[i-1][j-1]+1, S[i][j] = s[i];
        }
    cout << dp[n-1][n-1];
}
