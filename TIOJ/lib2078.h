#include <iostream>

using namespace std;

int p,x,y,e,n,c,k,phi=20;
uint64_t PhiOracle(uint64_t x) {
    return (x%phi)%k;
}
long long getPhi(long long,long long);
uint64_t decrypt(uint64_t, uint64_t, uint64_t, uint64_t);
signed main() {
    #if 0
    while(cin >> p >> x >> y >> k) {
        //n = x*y;
        //c = modpow(p,e,n);
        //phi = (x-1)*(y-1);
        /*if(__gcd(phi,e) != 1)
            cout << "e and phi must be coprime\n";
        else
            cout << c << ' ' << e << ' ' << n << ' ' << phi << '\n';*/
        //cout << "n: " << n << '\n';
        //cout << "phi: " << phi << '\n';
        cout << getPhi(phi,k) << '\n';
    }
    #else
    // c=p^e%n
    while(cin >> c >> e >> n >> k) {
        cout << decrypt(e,n,c,k) << '\n';
    }
    #endif // 1
}
