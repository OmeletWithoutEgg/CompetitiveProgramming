#include <bits/stdc++.h>

using namespace std;

signed main(){
    ios::sync_with_stdio(0), cin.tie(0);
    long long a=1,b=2,t,q,cnt=0;
    cin >> q;
    for(int i = 0;i < q;i++){
        for(int k = 0;k < a;k++)cout << ++cnt%3;
        cout << '\n';
        t=a+b,a=b,b=t;
    }
}
