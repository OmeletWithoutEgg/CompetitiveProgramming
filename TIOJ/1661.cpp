#include <cstdio>
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
    while(('0'>c || c>'9') && c!=EOF) c=readchar();
    //if(c=='-') neg=1, c=readchar();
    while('0'<=c && c<='9') x=x*10+c-'0', c=readchar();
    //if(neg) x = -x;
    return x;
}

int n,v[100];
int main() {
    while(n = nextint()) {
        for(register int i = 0; i < n; i++) v[i] = nextint();
        int q = nextint();
        register int i,j,t;
        while(q--) i = nextint(), j = nextint(), t = v[i], v[i] = j[v], j[v] = t;
        for(register int i = 0; i < n; i++) printf("%d", v[i]), putchar(" \n"[i==n-1]);
    }
}
