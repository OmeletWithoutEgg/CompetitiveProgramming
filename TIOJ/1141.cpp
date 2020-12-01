#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;

int n,v[10025],res;
signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> v[i];
    sort(v+1,v+n+1);
    for(int i = 1; i <= n; i++) res += (v[i]-v[i-1])*(v[i]-v[i-1]);
    cout << res << '\n';
}
