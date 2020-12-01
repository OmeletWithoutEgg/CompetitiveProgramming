#include <iostream>

using namespace std;

signed main(){
    int a,b;
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> a >> b;
    if(a > b)
        for(int i = a; i >= b; i--,cout<<'\n') for(int j = 0; j < i; j++) cout << '*';
    else
        for(int i = a; i <= b; i++,cout<<'\n') for(int j = 0; j < i; j++) cout << '*';
}
