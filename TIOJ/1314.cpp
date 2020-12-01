#include <bits/stdc++.h>
#define ff first
#define ss second

using namespace std;
typedef long long ll;

signed main(){
    ll a[3] = {},n;
    cin >> n;
    while(n--){
        cin >> a[0] >> a[1] >> a[2];
        sort(a,a+3);
        cout << ((a[0]+a[1]>a[2] && a[0]*a[0]+a[1]*a[1]==a[2]*a[2])?"yes\n":"no\n");
    }
}

