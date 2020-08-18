#include <bits/stdc++.h>

using namespace std;

int main(){
    int m;
    int a[50001];
    int b[50001];
    while(cin >> m){
        for(int i = 0;i < m;i++)cin >> a[i];
        for(int i = 0;i < m;i++)cin >> b[i];
        sort(a,a+m),sort(b,b+m);
        long long ans = 0;
        for(int i = 0;i < m;i++)ans += a[i] * b[i];
        cout << ans << '\n';
    }
    return 0;
}
