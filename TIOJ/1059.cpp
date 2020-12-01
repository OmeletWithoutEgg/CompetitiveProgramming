#include <bits/stdc++.h>
#define debug(x) cout<<#x<<':'<<x<<'\n'

using namespace std;

signed main(){
    double t;
    int s,profit=0,n,v,sum=0;
    cin >> s >> t >> n;
    profit -= round(s*t*0.3);
    for(int i = 0; i < n; i++) cin >> v, sum += v;
    for(int i = 1; i <= sum; i++) {
        if(i <= round(t*0.2)) profit += round(s*0.7);
        else if(i <= round(t*0.4)) profit += round(s*0.8);
        else if(i <= round(t*0.6)) profit += round(s*0.9);
        else profit += s;
    }
    cout << profit << '\n';
}
