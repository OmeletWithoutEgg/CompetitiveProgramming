#include <bits/stdc++.h>

using namespace std;

int main(){
    string s, weekDay[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    int i, p;
    cin >> s;
    for(i=0;i<7;i++)if(weekDay[i] == s)break;
    cin >> p;
    cout << weekDay[(i+p)%7] << '\n';
    return 0;
}
