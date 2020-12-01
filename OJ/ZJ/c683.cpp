#include <iostream>
#include <cstdio>
#include <bitset>

using namespace std;

void f(uint32_t &x, uint32_t &c, uint32_t d) {
	for (int k = 0; k < 16; ++k) {
		c += ((x << k) | (x >> (32 - k))) / d;
		c += ((x >> k) | (x << (32 - k))) / d;
		x += c * 2654435761lu;
		cout << '\t' << "k = " << k << ",x = " << x << endl;
	}
}

int main(){
    uint16_t n, m;
    uint32_t s[10001] = {}, x, last = 0, c = 0;
    /*uint32_t trueAns[] = {3997325084u,2705072328u,1928591162u,836263515u};
    for(int i = 0;i < 4;i++){
        cout << trueAns[i] << endl;
    }*/
    cin >> n >> m;
    for(int i = 0;i < n;i++)cin >> s[i];
    for(int i = 0;i < m;i++){
        cin >> x;
        for(int i = 0;i < n;i++){
            //x ^= last;
            f(x ^= last,c,s[i]);
        }
        cout << x << endl;
    }
    return 0;
}

/*
3 4
2 2 2
20 20 20 20

*/
