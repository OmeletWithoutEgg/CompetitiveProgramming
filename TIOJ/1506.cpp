#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
typedef long long ll;

long double a1,a2,b1,b2;
signed main(){
    cin >> a1 >> a2 >> b1 >> b2;
    cout << (b1-b2)/(a2-a1) << '\n';
    cout << (a2*b1-a1*b2)/(a2-a1) << '\n';
}


