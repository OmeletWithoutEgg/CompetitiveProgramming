inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

inline void readline(char *s) {
    char c = readchar();
    while(c != '\n') *s++ = c, c = readchar();
}

struct FastOut {
    char *buf;
    int q;
    const int B;
    inline void writeln(int x) {
        static char stk[20];
        char p = 0;
        if(!x) stk[p++] = '0';
        while(x) stk[p++] = x%10^'0', x/=10;
        while(p) buf[q++] = stk[--p];
        buf[q++] = '\n';
        if(q + 20 >= B) fwrite(buf, 1, q, stdout), q = 0;
    }
    FastOut(int B = 1<<20) : B(B), q(0), buf(new char[B]){}
    ~FastOut() {
        fwrite(buf, 1, q, stdout);
        delete [] buf;
    }
};
