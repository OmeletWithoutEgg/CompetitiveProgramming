#include <cstdio>

typedef long long ll;
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0' && ~c) c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
inline void readline(char *s) {
    char c = readchar();
    while(c != '\n') *s++ = c, c = readchar();
}

signed main() {
    ll n;
    char s[40];
    while(n = nextint()) {
        readline(s);
        ll h = n/2; // half
        ll right = n&1 ? 0 : n*(h-1);
        ll tmp = n-2-h;
        ll obtuse = tmp*(tmp+1)/2*n;
        // (# a + b + c = n, max(a,b,c) > n/2)
        // (sum_{a = n/2+1}^{n-2} n-a-1) = sum_{i=1}^{n-2-n/2} i
        // tot = n*(n-1)*(n-2)/6
        ll acute = (n-1)*(n-2)/2 - tmp*(tmp+1)/2*3;
        if(n%3)
            acute /= 3, acute *= n;
        else
            acute *= n/3;
        acute -= right;
        if(s[0] == "Right"[0])
            printf("%lld\n", right);
        else if(s[0] == "Acute"[0])
            printf("%lld\n", acute);
        else if(s[0] == "Obtuse"[0])
            printf("%lld\n", obtuse);
    }
}
