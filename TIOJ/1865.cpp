#ifndef local
#include "lib1865.h"
#else
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <algorithm>
#include <cassert>
long long v[1000];
int cnt;
int GetN() {
    srand(7122);
    for(int i = 0; i < 1000; i++) v[i] = rand()%25+1;
    return 1000;
}
bool Magic_Isdivide(int x) {
    assert(0 <= x && x < 1000);
    ++cnt;
    return v[x+1]%v[x] == 0;
}
void Magic_Operate(int x) {
    long long g = std::__gcd(v[x], v[x+1]);
    v[x+1] *= v[x]/g;
    v[x] = g;
    ++cnt;
}
void End() {
    for(int i = 0; i < 1000; i++) printf("%lld%c", v[i], i==1000-1 ? '\n' : ' ');
    printf("cnt = %d\n", cnt);
}
#endif // local

signed main() {
    int n = GetN();
    for(int i = 0; i < n; i++) {
        for(int j = i-1; j >= 0; j--) {
            /* if(!Magic_Isdivide(j)) */
                Magic_Operate(j);
            /* else */
                /* break; */
        }
    }
    End();
    return 0;
}
