#include <bits/stdc++.h>
#define sort_uni(v) sort(begin(v),end(v)), v.erase(unique(begin(v),end(v)),end(v))

using namespace std;
const int N = 525;

int n,m,k;
vector<int> adjL[N];
bool adjM[N][N];
string s;
void addEdge(int a,int b){
    adjM[a][b] = true;
    adjL[a].push_back(b);
}
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m >> k;
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> s >> b;
        if(s.front() == '<') addEdge(b,a);
        if(s.back() == '>') addEdge(a,b);
    }
    if(k) {
        for(int i = 1; i <= n; i++) {
            cout << i << " ->";
            if(adjL[i].size() == 0) cout << " 0\n";
            else {
                sort_uni(adjL[i]);
                for(auto j:adjL[i]) cout << ' ' << j;
                cout << '\n';
            }
        }
    }else {
        for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
            cout << adjM[i][j] << " \n"[j==n];
    }
}

