#include <bits/stdc++.h>

using namespace std;
using cd = complex<long double>;
const long double PI = acos(-1);
const cd omega = exp(cd(0, PI/3));

signed main() {
    int x1, y1, x2, y2;
    cout << fixed << setprecision(3);
    while(cin >> x1 >> y1 >> x2 >> y2) {
        cd A{x1, y1};
        cd B{x2, y2};
        cd C = A + (B-A) * omega;
        cd D = A + (B-A) / omega;
        if(C.real() > D.real() || (C.real()==D.real() && C.imag()>D.imag())) swap(C,D);
        cout << C.real() << ' ' << C.imag() << ' ' << D.real() << ' ' << D.imag() << '\n';
    }
}
