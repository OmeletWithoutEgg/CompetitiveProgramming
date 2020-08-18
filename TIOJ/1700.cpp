#include <bits/stdc++.h>

using namespace std;

inline int gcd(int a,int b){
    int t;
    while(b)t = a%b,a = b,b = t;
    return a;
}
int n, a[2];
int main(){
    while(cin >> n){
        a[0] = a[1] = 0;
        for(int i = 0;i < n;i++)cin >> a[0],a[1] = gcd(a[0],a[1]);
        cout << a[1] << '\n';
    }
    return 0;
}

