#pragma GCC optimize("Ofast")
/* #pragma GCC target("sse3","sse2","sse") */
/* #pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3") */
/* #pragma GCC target("f16c") */
/* #pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector") */
#include <cstdio>

using namespace std;
const int K = 26, N = 20025;

inline char readchar() {
    constexpr int B = 1<<16;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
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
    *s++ = '\0';
}

struct SuffixAutomaton {
    struct node {
        int ch[K];
        int len, fail, cnt;
        int indeg;
        node(int L = 0) : ch{}, len(L), fail(0), cnt(0), indeg(0) {}
    } st[N];
    int root, last, tot;
    void extend(int c) {
        int cur = ++tot;
        st[cur] = node(st[last].len + 1);
        while(last && !st[last].ch[c]) {
            st[last].ch[c] = cur;
            last = st[last].fail;
        }
        if(!last) {
            st[cur].fail = root;
        } else {
            int q = st[last].ch[c];
            if(st[q].len == st[last].len + 1) {
                st[cur].fail = q;
            } else {
                int clone = ++tot;
                st[clone] = st[q];
                st[clone].len = st[last].len + 1;
                st[clone].cnt = 0;
                st[cur].fail = st[q].fail = clone;
                while(last && st[last].ch[c] == q) {
                    st[last].ch[c] = clone;
                    last = st[last].fail;
                }
            }
        }
        st[cur].cnt += 1;
        last = cur;
    }
    void init(const char *s) {
        tot = 0;
        root = last = ++tot;
        st[root] = node(0);
        for(char c; c = *s; ++s) extend(c - 'a');
    }
    int q[N];
    void dp() {
        for(int i = 1; i <= tot; i++) ++st[st[i].fail].indeg;
        int head = 0, tail = 0;
        for(int i = 1; i <= tot; i++) if(st[i].indeg == 0) q[tail++] = i;
        while(head != tail) {
            int now = q[head++];
            if(int f = st[now].fail) {
                st[f].cnt += st[now].cnt;
                if(--st[f].indeg == 0) q[tail++] = f;
            }
        }
    }
    int run(const char *s) {
        int now = root;
        for(char c; c = *s; ++s) {
            c -= 'a';
            if(!st[now].ch[c]) return 0;
            now = st[now].ch[c];
        }
        return st[now].cnt;
    }
} SAM;
char S[10025];
signed main() {
    int t = nextint();
    while(t--) {
        readline(S);
        int q = nextint();
        SAM.init(S);
        SAM.dp();
        while(q--) {
            readline(S);
            printf("%d\n", SAM.run(S));
        }
    }
}
