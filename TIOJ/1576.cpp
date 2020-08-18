#include <bits/stdc++.h>

using namespace std;

int main(){
    int a[4]={},res=0;
    for(int i=0;i<4;i++)cin>>a[i];
    int t = min(a[0],a[1]);
    res += t*100,a[0]-=t,a[1]-=t;
    res += (min(a[0],a[1])*80+min(a[2],a[3])*60);
    cout << min(a[0],a[1]) << ' ' << t << ' ' << min(a[2],a[3]) << '\n';
    cout << res << '\n';
    return 0;
}
