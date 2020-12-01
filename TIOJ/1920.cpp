#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
const int N = 10025, K = 31;
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

int n, q, suf[N], root[N];
struct Trie {
    int ch[N*(K+1)][2], mn[N*(K+1)], tot;
    int ins(int old, int x, int pos) {
        int now = ++tot, root = now;
        for(int i = K-1; i >= 0; i--) {
            int d = x>>i & 1;
            ch[now][d] = ++tot;
            ch[now][!d] = ch[old][!d];
            now = ch[now][d];
            old = ch[old][d];
            mn[now] = pos;
        }
        return root;
    }
    int query(int p, int x, int pos) {
        int res = 0;
        for(int i = K-1; i >= 0; i--) {
            int d = ~x>>i & 1;
            if(ch[p][d] && mn[ch[p][d]] < pos)
                p = ch[p][d], res |= 1<<i;
            else
                p = ch[p][!d];
        }
        return res;
    }
} tr;
signed main() {
    n = nextint(), q = nextint();
    for(int i = 0; i < n; i++) suf[i] = nextint();
    for(int i = n-1; i >= 0; i--) suf[i] ^= suf[i+1];
    for(int i = n-1; i >= 0; i--) root[i] = tr.ins(root[i+1], suf[i], i);
    for(int i = 0; i < q; i++) {
        int L = nextint(), R = nextint(), V = nextint();
        printf("%d\n", tr.query(root[L], suf[R]^V, R));
    }
}
