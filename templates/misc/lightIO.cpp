#include <unistd.h>

inline char readchar() {
    constexpr int B = 1<<10;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+read(0, buf, B)) == buf) return -1;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
inline void writeint(int x) {
    static char stk[20], buf[20];
    char p = 0, q = 0;
    if(!x) stk[p++] = '0';
    while(x) stk[p++] = x%10^'0', x/=10;
    while(p) buf[q++] = stk[--p];
    write(1, buf, q);
}
inline void writestr(const char *s) {
    int len = 0;
    for(; s[len]; ++len);
    write(1, s, len);
}
