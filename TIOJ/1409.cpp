#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline long long nextint() {
    long long x = 0;
    char c = readchar();
    while(c < '0' && ~c) c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

signed main() {
    int n;
    while(n = nextint()) {
        long long v, sum = 0, mx = 0;
        for(int i = 0; i < n; i++)
            v = nextint(), sum += v, mx = mx<v ? v : mx;
        puts(mx*2 < sum ? "YES" : "NO");
    }
}

