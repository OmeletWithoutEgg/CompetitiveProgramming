#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

char c;
int g[22][22];
int n, m, t;
int main(){
    pair<int,int> cur,ends;
    cin >> t;
    while(t--){
        cin >> n >> m;
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= m;j++){
                cin >> c;
                switch(c){
                    case '#':g[i][j] = 1;break;
                    case '.':g[i][j] = 0;break;
                    case 'S':g[i][j] = 0;cur = mp(i,j);break;
                    case 'T':g[i][j] = 0;ends = mp(i,j);break;
                }
                g[0][j] = g[n+1][j] = 1;
                g[i][0] = g[i][m+1] = 1;
        }
        while(cur != ends){
            g[cur.first][cur.second] = 1;
            if(!g[cur.first-1][cur.second]){cur = mp(cur.first-1, cur.second);cout << 'U';}
            else if(!g[cur.first+1][cur.second]){cur = mp(cur.first+1, cur.second);cout << 'D';}
            else if(!g[cur.first][cur.second-1]){cur = mp(cur.first, cur.second-1);cout << 'L';}
            else if(!g[cur.first][cur.second+1]){cur = mp(cur.first, cur.second+1);cout << 'R';}
            //cout << cur.first << ' ' << cur.second << '\n';
        }
        cout << '\n';
    }
    return 0;
}
