#include <bits/stdc++.h>

using namespace std;

int main(){
    int p, q;
    cin >> p >> q;
    if(p%q&&q%p)cout << "N\n";
    else cout << "Y\n";
    return 0;
}
