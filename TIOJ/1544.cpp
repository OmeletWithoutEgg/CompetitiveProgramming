#include <bits/stdc++.h>

using namespace std;

int lt(string &a,string &b){
    return a.length()!=b.length() ? a.length() < b.length() : a < b;
}
int main(){
    string a, b;
    int q;
    cin >> q;
    while(q--){
        cin >> a >> b;
        cout << lt(a,b) << '\n';
    }
    return 0;
}

