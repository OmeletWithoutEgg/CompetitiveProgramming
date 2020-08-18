#include <bits/stdc++.h>

using namespace std;

int t;
string s;
void inv(string &s){
    int m;
    m = s.find("and");
    if(m != string::npos){
        string a = s.substr(0,m-1), b = s.substr(m+4);
        inv(a),inv(b);
        s = a + " or " + b;
        return;
    }
    m = s.find("or");
    if(m != string::npos){
        string a = s.substr(0,m-1), b = s.substr(m+3);
        inv(a),inv(b);
        s = a + " and " + b;
        return;
    }
    m = s.find("not");
    if(m != string::npos){
        s = s.substr(m+4);
        return;
    }
    s = "not "+s;
    return;

}
signed main(){
    cin >> t;
    cin.ignore();
    while(t--){
        getline(cin,s);
        int i = s.find("IF"), j = s.find("THEN");
        string a = s.substr(i+3,j-i-4), b = s.substr(j+5);
        inv(a), inv(b);
        cout << "IF " << b << " THEN " << a << '\n';
    }
}
