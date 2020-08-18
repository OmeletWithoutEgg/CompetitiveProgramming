#include <bits/stdc++.h>
#define mid (l+(r-l>>1))

using namespace std;
typedef long long ll;
const ll N = 5000;

ll k,n,hasSame,cnt[26],dist[N];
vector<string> V,U;
void check(int a,int b){
    bool check = true;
    for(int i = 1; i < k; i++){
        if(V[i][a] != V[0][a]) dist[i]--;
        if(V[i][b] != V[0][b]) dist[i]--;
        if(V[i][a] != V[0][b]) dist[i]++;
        if(V[i][b] != V[0][a]) dist[i]++;
        if(dist[i] == 0){
            if(!hasSame) check = false;
        }else if(dist[i] != 2) check = false;
        if(V[i][a] != V[0][a]) dist[i]++;
        if(V[i][b] != V[0][b]) dist[i]++;
        if(V[i][a] != V[0][b]) dist[i]--;
        if(V[i][b] != V[0][a]) dist[i]--;
    }
    if(check){
        swap(V[0][a],V[0][b]);
        cout << V[0], exit(0);
    }
}
signed main(){
    cin >> k >> n;
    V.resize(k);
    for(int i = 0; i < k; i++) cin >> V[i];
    U = V;
    for(int i = 0; i < k; i++) {
        sort(U[i].begin(),U[i].end());
        if(U[i] != U[0]) return cout << -1, 0;
    }
    for(int i = 0; i < n; i++) if(cnt[V[0][i]-'a']++ == 1) hasSame = 1;
    for(int i = 1; i < k; i++) for(int j = 0; j < n; j++) if(V[i][j] != V[0][j]) dist[i]++;
    for(int i = 0; i < n; i++) for(int j = 0; j < i; j++) check(i,j);
    cout << -1;
}

