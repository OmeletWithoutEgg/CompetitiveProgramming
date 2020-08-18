#include <iostream>
#include <algorithm>
#define MAX_N 1000000

using namespace std;

int s[MAX_N + 1] = {}, l = 0;
int main(){
    cin >> s[0];
    while(cin >> s[l++]);
    sort(s,s + l - 1,greater<int>());
    while(--l)cout << s[l - 1] << ' ';
    cout << endl;
    return 0;
}
