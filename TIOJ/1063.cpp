#include <bits/stdc++.h>

using namespace std;

int n,m,cnt,x;
int con[227][227], stk[227], p;
int L[227],R[227];
signed main() {
    ios_base::sync_with_stdio(0),cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cnt = 0;
        for(int j = 0; j < m; j++) {
            cin >> x;
            x ? ++cnt : cnt=0;
            con[i][j] = cnt;
            //cout << con[i][j] << " \n"[j==m-1];
        }
    }
    int best = 0;
    for(int j = 0; j < m; j++) {
        p = 0;
        for(int i = 0; i < n; i++) {
            while(p && con[stk[p-1]][j]>=con[i][j]) --p;
            L[i] = p ? stk[p-1] : -1;
            //cout << L[i] << ',';
            stk[p++] = i;
        }
        //cout << '\n';
        p = 0;
        for(int i = n-1; i >= 0; i--) {
            while(p && con[stk[p-1]][j]>=con[i][j]) --p;
            R[i] = p ? stk[p-1] : n;
            //cout << R[i] << '.';
            stk[p++] = i;
        }
        //cout << '\n';
        for(int i = 0; i < n; i++) best = max(best, con[i][j]*(R[i]-L[i]-1));
    }
    cout << best;
}
