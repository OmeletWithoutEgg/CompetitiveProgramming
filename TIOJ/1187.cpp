#pragma g++ optimize("Ofast, no-stack-protector, unroll-loops")
#pragma loop_opt(on)
#include <cstdio>
inline char readchar() {
    constexpr int B = 1<<10;
    static char buf[B], *p=buf, *tail=buf;
    if(p == tail) {
        tail = buf+fread_unlocked(buf, 1, B, stdin);
        if(tail == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int nextint() {
    register int x = 0, c = readchar();
    while('0'>c||c>'9') c = readchar();
    while('0'<=c&&c<='9') x=x*10+c-'0', c=readchar();
    return x;
}

signed main() {
    int n;
    while(n = nextint()) {
        int sum = 0, v, mx = 0, mn = 10;
        for(register int i = 0; i < n; i++) {
            v = nextint();
            sum += v;
            if(mx < v) mx = v;
            if(mn > v) mn = v;
        }
        sum -= mx+mn;
        n -= 2;
        int ans = sum*100/n + (sum*1000/n%10>=5);
        register char stk[6],p=0;
        stk[p++] = '\n'^'0';
        stk[p++] = ans%10, ans/=10;
        stk[p++] = ans%10, ans/=10;
        stk[p++] = '.'^'0';
        stk[p++] = ans%10, ans/=10;
        if(ans) stk[p++] = ans%10;
        while(p) putchar_unlocked(stk[--p]^'0');
    }
}

