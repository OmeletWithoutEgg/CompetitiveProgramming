#include <cstdio>
#include <algorithm>

long long gcd(long long a, long long b) {
    long long s = __builtin_ctzll(a|b), t;
    a >>= s, b >>= s;
    do {
        if(a > b) t = a, a = b, b = t;
        b -= a;
        b >>= __builtin_ctz(b);
    }while(b);
    //printf("%lld %lld\n",a,b);
    return a << s;
}
void mul(long long A[2][2], long long B[2][2]) {
    long long C[2][2] = {};
    for(int i = 0; i < 2; i++) for(int k = 0; k < 2; k++) {
        long long r = A[i][k];
        for(int j = 0; j < 2; j++) C[i][j] = (C[i][j]+r*B[k][j])%3;
    }
    for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) A[i][j] = C[i][j];
}
long long F(long long n) {
    long long A[2][2] = {{1,1},{1,0}};
    long long R[2][2] = {{1,0},{0,1}};
    //printf("n = %lld\n", n);
    while(n) {
        if(n & 1) mul(R, A);
        mul(A, A);
        n >>= 1;
    }
    //{a_i, a_{i-1}}
    //printf("%lld %lld\n%lld %lld\n", R[0][0],R[0][1],R[1][0],R[1][1]);
    return R[0][0];
}
signed main() {
    long long a, b;
    scanf("%lld%lld", &a, &b);
    long long g = std::__gcd(a+1,b+1);
    //printf("g = %lld\n", g);
    printf("%lld\n", F(g-1));
}
