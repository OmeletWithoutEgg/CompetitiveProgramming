#include <bits/stdc++.h>

using namespace std;

long long t,n,v[1<<22],h;
bool check;
main(){
    //cout << (2 ^5 ^4 ^10 ^8 ^11 ^9 ) << '\n';
    ios_base::sync_with_stdio(0),cin.tie(0);
    cin >> t;
    while(t--){
        cin >> h;
        n = (1LL<<h+1)-1;
        for(int i = 0; i < n; i++) cin >> v[i];
        sort(v,v+n);
        check = true;
        for(int i = 0; check && i < n; i++) {
            if(i*2+1>=n) break;
            if(v[i*2+1] != v[i]*2) check = false;
            if(i*2+2>=n) break;
            if(v[i*2+2] != v[i]*2+1) check = false;
        }
        if(!check) cout << "do not "; cout << "dodge\n";
    }
}
