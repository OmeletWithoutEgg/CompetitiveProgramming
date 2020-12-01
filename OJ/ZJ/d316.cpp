#include <iostream>

using namespace std;

inline uint64_t gcd(uint64_t a,uint64_t b){
    uint64_t t;
    while(b)t = a % b,a = b,b = t;
    return a;
}
int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    uint64_t s, k, d, n, g;
    while(cin >> s >> k){
        n = k * k + 1;
        d = k * k + (k << 1) + 1;
        g = gcd(n,d),n /= g,d /= g;
        g = gcd(s,d),s /= g,d /= g;
        if(d > 1)cout << s * n << " / " << d << endl;
        else cout << s * n << endl;
    }
    return 0;
}
