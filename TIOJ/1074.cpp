#include <bits/stdc++.h>

using namespace std;

signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    int n,v[30] = {},s[444],p;
    while(cin >> n,n){
        p = 0;
        for(int i = 1; i <= n; i++) cin >> v[i], v[i] += v[i-1];
        for(int j = 1; j <= n; j++) for(int i = 0; i < j; i++)
            if(v[j]-v[i]<=v[n]) s[p++] = v[j]-v[i];
        sort(s,s+p),p = unique(s,s+p)-s;
        cout << (p==v[n]&&n!=v[n]?"YES\n":"NO\n");
    }
}
