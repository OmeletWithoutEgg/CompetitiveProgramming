#include <iostream>
#include <string>

using namespace std;

int main(){
    string s = "";
    int n, l, i;
    cin >> n;
    l = (n << 1) - 1;
    for(i = 0;i < l;i++)s += "_";
    for(i = 0;i < n;i++)s[n - 1 + i] = s[n - 1 - i] = '*',cout << s << endl;
    return 0;
}
