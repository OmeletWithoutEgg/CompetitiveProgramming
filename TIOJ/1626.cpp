#include <cstdio>
#include <algorithm>
const int N = 1000000;
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline long long nextint() {
    long long x = 0;
    char c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

long long p[N];
signed main() {
    for(int i = 1, j = 1; i < N; i++) {
        p[i] = p[i-1] + j;
        if(i == p[j]) ++j;
    }
    //for(int i = 1; i <= 100; i++) cout << p[i] << ' ';
    long long n;
    while(n = nextint()) printf("%d\n", int(std::lower_bound(p,p+N,n) - p));
}

/*
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
*/
