#include <bits/stdc++.h>
#define ff first
#define ss second
#define N 100000

using namespace std;
typedef long long ll;

signed main(){
    ll fac[N+1] = {},res = 0;
    for(int i = 1;i <= n;i++){
        if(fac[i] < n/i-1)for(int j = i<<1;j <= n;j+=i)++fac[j];
        else res += fac[i];
    }
    ll t,n;
    cin >> t;
    while(t--){
        cin >> n;
        cout << res[n] << '\n';
    }
}



