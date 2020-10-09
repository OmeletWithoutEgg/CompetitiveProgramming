#pragma GCC optimize("Ofast")
/* #pragma GCC target("sse3","sse2","sse") */
/* #pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3") */
/* #pragma GCC target("f16c") */
/* #pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector") */
#include <cstdio>

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int readline(char *s) {
    char c = readchar();
    if(c == EOF) return 0;
    int len = 0;
    while(c != '\n') *s++ = c, c = readchar(), ++len;
    return len;
}
const int N = 200025;
char s[N];
int Z[N];
inline int max(int a, int b) { return a < b ? b : a; }
inline int min(int a, int b) { return a > b ? b : a; }
inline void swap(char &a, char &b) { char t = a; a = b; b = t; }
signed main() {
    while(int n = readline(s)) {
        for(int i = 0; (i<<1|1) < n; i++) swap(s[i], s[n-1-i]);
        for(int i = 1, j = 0, r = 0; i < n; i++) {
            Z[i] = max(0, min(Z[i-j], r-i));
            while(i+Z[i] < n && s[Z[i]] == s[i+Z[i]]) ++Z[i];
            if(i+Z[i] > r) {
                j = i;
                r = i+Z[i];
            }
        }
        int ans = 0;
        for(int i = 1; i < n; i++) if(Z[i] >= i) ans = i;
        printf("%d\n", ans);
    }
}
