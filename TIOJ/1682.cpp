#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> a;
int main(){
    while(cin >> n){
        a.resize(n);
        for(int i = 0;i < n;i++)cin >> a[i];
        sort(a.begin(),a.end());
        cout << a[0];
        for(int i = 1;i < n;i++)cout << ' ' << a[i];
        cout << '\n';
    }
    return 0;
}
