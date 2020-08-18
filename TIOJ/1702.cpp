#include <bits/stdc++.h>

using namespace std;
const int N = 125;

int n,m,tab[N][N];
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    while(cin >> n >> m) {
        for(int i = 0; i <= n+1; i++) tab[i][0] = tab[i][m+1] = 0;
        for(int j = 0; j <= m+1; j++) tab[0][j] = tab[n+1][j] = 0;
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> tab[i][j];
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
            if(tab[i][j]) cout << 'X';
            else {
                cout << (tab[i-1][j+1])+(tab[i][j+1])+(tab[i+1][j+1])+
                        (tab[i-1][j])  +              (tab[i+1][j])  +
                        (tab[i-1][j-1])+(tab[i][j-1])+(tab[i+1][j-1]) ;

            }
            cout << " \n"[j==m];
        }
    }
}
