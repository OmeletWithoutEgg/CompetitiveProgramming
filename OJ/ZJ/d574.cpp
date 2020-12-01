#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(){
    uint32_t n, i, last;
    string s;
    while(cin >> n >> s){
        string ns = "";
        stringstream ss;
        for(i = last = 0;i <= s.length();i++){
            if(s[i] != s[last]){
                ss << (i - last);
                ss << s[last];
                last = i;
            }
        }
        ss >> ns;
        cout << ((s.length() > ns.length())?ns:s) << endl;
    }
    return 0;
}
