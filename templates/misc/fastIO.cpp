inline char readchar() {
    constexpr int B = 1 << 20;
    static char buf[B], *p, *q;
    if (p == q && (q = (p = buf) + fread(buf, 1, B, stdin)) == buf)
        return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while (c < '0') c = readchar();
    while (c >= '0') x = x * 10 + (c ^ '0'), c = readchar();
    return x;
}

inline void readline(char* s) {
    char c = readchar();
    while (c != '\n') *s++ = c, c = readchar();
}

struct FastOut {
    constexpr static int B = 1 << 20;
    static char buf[B];
    int q;
    inline void writeint(int x, char sep = '\n') {
        static char stk[20];
        char p = 0;
        if (!x) stk[p++] = '0';
        while (x) stk[p++] = x % 10 ^ '0', x /= 10;
        while (p) buf[q++] = stk[--p];
        buf[q++] = sep;
        if (q + 20 >= B) fwrite(buf, 1, q, stdout), q = 0;
    }
    ~FastOut() { fwrite(buf, 1, q, stdout); }
} ouf;
char FastOut::buf[B];
