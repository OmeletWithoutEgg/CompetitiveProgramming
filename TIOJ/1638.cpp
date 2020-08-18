#include <bits/stdc++.h>
#define ff first
#define ss second

using namespace std;
typedef long long ll;

signed main(){
    map<ll,ll> mp;
    ll n,x,y,k;
    cin >> n;
    while(n--){
        cin >> x >> y >> k;
        mp[x*x+y*y] += k;
    }
    ll s = 0,b = 0;
    for(auto p:mp){
        if(s+p.ss>0)s+=p.ss;
        else s = 0;
        if(s>b)b=s;
    }
    cout << b << '\n';
}
