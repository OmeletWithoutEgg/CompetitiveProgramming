#include <bits/stdc++.h>

using namespace std;
const int N = 10025;

int n,v[N],u[N],res,k;
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> k;
    for(int i = 0; i < n; i++) cin >> v[i];
    for(int i = 0; i < n; i++) cin >> u[i];
    for(int i = n-1; i > 0; i--) v[i] -= v[i-1];
    for(int i = 0; i < n; i++) {
        if(i) v[i] += v[i-1];
        while(v[i] > 9) v[i] -= 9;
        while(v[i] <= 0) v[i] += 9;
        int dif = u[i]-v[i];
        if(dif < 0) dif += 9;
        if(dif != 0 && i+k > n) return cout << 0 << '\n', 0;
        v[i] += dif, v[i+k] -= dif;
        res += dif;
    }
    cout << res << '\n';
}

