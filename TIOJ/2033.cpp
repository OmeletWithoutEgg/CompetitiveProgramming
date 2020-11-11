#pragma GCC optimize("Ofast")
#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <unistd.h>

using std::swap;
const int N = 3000025;

int v[N], u[N];
int pos[N];
inline char readchar() {
    static const int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && ((p=buf) == (q=buf+fread_unlocked(buf, 1, B, stdin)))) return EOF;
    /* if(p == q && ((p=buf) == (q=buf+read(0, buf, B)))) return -1; */
    return *p++;
}
int readArr(int v[]) {
    int n = 0;
    char c, last = '_';
    while((c = readchar()) != '\n') {
        if(isdigit(c)) v[n] = v[n] * 10 + (c ^ '0');
        else if(c != last) ++n;
        last = c;
    }
    return ++n;
}
inline void W(int x) {
    static char stk[20], p, buf[20];
    int q = 0;
    if(!x) buf[q++] = '0';
    while(x) stk[p++] = x%10^'0', x /= 10;
    while(p) buf[q++] = stk[--p];
    write(1, buf, q);
}
signed main() {
    int p = readArr(v);
    int q = readArr(u);
    if(p != q) return write(1, "-1", 2), 0;
    // for(int i = 0; i < p; i++) printf("%d%c", u[i], i+1==p ? '\n' : ' ');
    /* for(int i = 0; i < p; i++) --v[i], --u[i]; */
    for(int i = 0; i < p; i++) pos[v[i]] = i;
    for(int i = 0; i < p; i++) u[i] = pos[u[i]];
    for(int i = 0; i < p; i++) pos[u[i]] = i;
    int ans = 0;
    for(int i = 0, x; i < p; i++) {
        if((x = u[i]) != i) {
            swap(u[i], u[pos[i]]);
            swap(pos[x], pos[i]);
            ++ans;
        }
    }
    W(ans);
    // printf("%d\n", ans);
}

