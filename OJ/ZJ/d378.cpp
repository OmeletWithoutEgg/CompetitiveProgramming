#include <bits/stdc++.h>
#define MAX_S 101

using namespace std;

int main(){
    fill
    uint16_t n, m, ct = 1;
    while(cin >> n >> m){
        uint32_t g[MAX_S + 1][MAX_S + 1] = {};
        uint32_t cost[MAX_S + 1][MAX_S + 1] = {};
        for(int i = 0;i < n;i++)
            for(int j = 0;j < m;j++)
                cin >> g[i][j],cost[i][j] = (i || j) * min(i ? cost[i - 1][j] : UINT_MAX,j ? cost[i][j - 1] : UINT_MAX) + g[i][j];
        /*
        for(int i = 0;i < n;i++,cout << endl)
            for(int j = 0;j < m;j++)
                cout << setw(10) << cost[i][j] << ' ';
        */
        cout << "Case #" << ct++ << " :\n" << cost[n - 1][m - 1] << endl;
    }
    return 0;
}
