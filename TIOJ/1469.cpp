#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse","popcnt")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#include <cstdio>

using namespace std;

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

inline void readstr(char *s) {
    char c = readchar();
    while(c != ' ' && c != '\n') *s++ = c, c = readchar();
}

int code(const char * s) {
    // X = 88
    // S = 83
    // M = 77
    // L = 76
    if(s[0] != 'X')
        return s[0] % 8;
    if(s[1] != 'X')
        return s[1] == 'S';
    return 2;
}
char A[6], B[6];
signed main() {
    int n, m;
    while(n = nextint()) {
        m = nextint();
        int cnt[1<<6] = {};
        for(int i = 0; i < m; i++) {
            readstr(A);
            readstr(B);
            int a = code(A), b = code(B);
            ++cnt[(1<<a) | (1<<b)];
            // for(int s = 0; s < (1<<6); s++) if((s >> a & 1) && (s >> b & 1)) ++cnt[s];
        }
        for(int i = 0; i < 6; i++)
            for(int s = 0; s < (1<<6); s++)
                if(s >> i & 1)
                    cnt[s] += cnt[s ^ (1<<i)];
        n /= 6;
        bool ok = true;
        for(int s = 0; s < (1<<6); s++) if(__builtin_popcount(s) * n < cnt[s]) ok = false;
        puts(ok ? "YES" : "NO");
    }
}
