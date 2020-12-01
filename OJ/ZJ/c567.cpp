#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

inline int gcd(int a,int b){
    int t;
    while(b)t = a % b,a = b,b = t;
    return a;
}

inline int way(int a,int b,int k,int m){
    int g = gcd(a,b);
    if(k % g)return 0;
    a /= g,b /= g,k /= g;
    if(a > b)swap(a,b);
    m = min(m,k / a);
    int s = 0;
    for(int x = 0;x <= m;x++)
        if(k % b == (a * x) % b)++s,cout << a << " * " << x << " + " << b << " * " << (k - a * x) / b << " = " << k << endl;
    return s;
}

int main(){
    int t;
    int n, a, b, k;
    cin >> t;
    while(t--){
        cin >> n >> a >> b >> k;
        cout << way(a,b,k,n) << endl;
    }
    return 0;
}
