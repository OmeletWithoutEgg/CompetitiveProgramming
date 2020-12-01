#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    double a, b, c, d;
    double det;
    while(cin >> a >> b >> c >> d){
        if(a == 0 && b == 0 && c == 0 && d == 0)return 0;
        det = a * d - b * c;
        if(det == 0)cout << "cheat!\n";
        else cout << fixed << setprecision(5) << d / det << ' ' << -b / det << '\n' << -c / det << ' ' << a / det << '\n';
    }
    return 0;
}
