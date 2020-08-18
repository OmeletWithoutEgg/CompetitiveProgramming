#include <bits/stdc++.h>

using namespace std;

int main(){
    int a, b, ct = 0;
    set<int> par;
    cin >> a >> b;
    while(a != b){
        if(a > b)a >>= 1;
        else b >>= 1;
        ct++;
    }
    cout << ct << '\n';
    return 0;
}
