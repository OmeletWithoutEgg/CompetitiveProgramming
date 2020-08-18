#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
#define getchar getchar_unlocked
#define putchar putchar_unlocked

unsigned buf[100],t;
char p,stk[1000];
void R(unsigned &x) {
    x=0;
    p = getchar();
    while((p<'0'||p>'9') && ~p) p=getchar();
    while(p>='0'&&p<='9') x=x*10+p-'0', p=getchar();
}
main() {
    register unsigned n,s,k;
    while(R(n),n) {
        s = 0;
        while(n--) R(k), s^=k;
        buf[t++] = s;
    }
    while(t) {
        unsigned x = buf[--t];
        stk[p++]='\n';
        if(!x) stk[p++] = '0';
        while(x) stk[p++] = x%10+'0', x/=10;
    }
    while(p) putchar(stk[--p]);
}
