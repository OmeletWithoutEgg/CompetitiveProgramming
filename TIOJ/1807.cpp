#include <bits/stdc++.h>
#define int long long
using namespace std;

main(){
    int v,e;
    cin >> v >> e;
    if(e>v*v+v>>1){
        cout << "Yes\n";
        return 0;
    }
    bool g[2000][2000] = {};
    map<int,int> num;
    int t,f,l = 0;
    for(int i = 0;i < e;i++){
        cin >> t >> f;t--,f--;
        if(t == f){
            cout << "Yes\n";
            return 0;
        }
        if(!num.count(t))t = num[t] = l++;
        else t = num[t];
        if(!num.count(f))f = num[f] = l++;
        else f = num[f];
        if(g[t][f] || g[f][t]){
            cout << "Yes\n";
            return 0;
        }
        g[t][f] = g[f][t] = 1;
    }
    cout << "yes\n";
    return 0;
}
