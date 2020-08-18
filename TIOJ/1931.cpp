#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
#include <algorithm>
inline int readchar() {
    const int B = 1048576;
    static char buf[B];
    static char *p = buf, *tail = buf;
    if(p == tail) {
        if((tail = buf + fread(buf, 1, B, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int nextint() {
    //bool neg = false;
    int x = 0, c = readchar();
    while('0'>c || c>'9') c=readchar();
    //if(c=='-') neg=1, c=readchar();
    while('0'<=c && c<='9') x=x*10+c-'0', c=readchar();
    //if(neg) x = -x;
    return x;
}

int n,t,v[100025];
int main() {
    t = nextint();
    while(t--) {
        n = nextint();
        for(int i = 0; i < n; i++) v[i] = nextint();
        std::sort(v,v+n);
        long long sum = 0;
        for(int i = n&1; i < n; i += 2) sum += v[i];
        printf("%lld\n", sum<<2);
    }
}

