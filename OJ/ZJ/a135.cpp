#include <bits/stdc++.h>

using namespace std;

int main(){
    map<string,string> m;
    m["HELLO"] = "ENGLISH";
    m["HOLA"] = "SPANISH";
    m["HALLO"] = "GERMAN";
    m["BONJOUR"] = "FRENCH";
    m["CIAO"] = "ITALIAN";
    m["ZDRAVSTVUJTE"] = "RUSSIAN";
    string s;

    int ct = 1;
    while(cin >> s){
        if(s != "#"){
            cout << "Case " << ct++ << ": ";
            if(m.find(s) != m.end())cout << m[s] << endl;
            else cout << "UNKNOWN" << endl;
        }
    }
    return 0;
}
