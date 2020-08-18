#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

main(){
    ll x;
    while(cin >> x){
        ll res = 0;
        while(x)res += x/=3;
        cout << res << '\n';
    }
    return 0;
}
