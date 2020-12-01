#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
void plus1(string &x){
    for(int i = x.size()-1;i >= 0;i--){
        if(x[i] != '9')return x[i]++,void();
        else x[i] = '0';
    }
    x[0] = '1',x += '0';
}
signed main(){
    string s;
    cin >> s;
    plus1(s);
    ld res = 0;
    int l = min(40,(int)s.size());
    for(int i = l-1;i >= 0;i--)res /= 10,res += s[i]-'0';
    cout << floor(log2(res)+(s.size()-1)/log10(2)) << '\n';
}
