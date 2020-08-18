#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int main(){
    vector<string> v;
    int n;
    cin >> n;
    cin.ignore();
    v.resize(n);
    for(int  i = 0;i < n;i++)getline(cin,v[i]);
    sort(v.begin(),v.end());
    for(int i = 0;i < n;i++)cout << v[i] << '\n';
    return 0;
}
