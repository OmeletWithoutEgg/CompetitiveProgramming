#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

signed main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ll q,t,mx = 0,res;
    while(cin >> q,q){
        mx = res = 0;
        while(q--){
            cin >> t;
            res+=t, mx = max(mx,t);
        }
        cout << res+mx+1 << '\n';
    }
}
