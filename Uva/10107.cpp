#include <bits/stdc++.h>

using namespace std;

int main(){
    int a[20000]={};
    int i=0;
    while(cin >> a[i++])sort(a,a+i),cout << ((i&1)?(a[i>>1]):((a[i>>1]+a[(i>>1)-1])>>1)) << '\n';
}
