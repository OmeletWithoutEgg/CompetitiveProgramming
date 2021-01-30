#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,avx512bw,avx512cd,avx512f,avx512dq,avx512vl,avx512vnni")
#include <cstdio>
#include <cstring>
#include <algorithm>

const int K = 16;
typedef int v16i __attribute__ ((vector_size (K * sizeof(int))));

struct Query {
    int v, l, r, c, k, id;
    friend bool operator<(const Query &a, const Query &b) {
        return a.v != b.v ? a.v < b.v : a.r < b.r;
    }
} Q[300125];
int ans[200125];
int pref[100125];
int n, q;
void add(int p) {
    v16i v;
    for(int i = p; i <= n; i += K) {
        memcpy(&v, &pref[i], sizeof(v16i));
        v += 1;
        memcpy(&pref[i], &v, sizeof(v16i));
        // for(int j = 0; j < K; j++)
        //     pref[i+j] += 1;
    }
}
int query(int l, int r, int k, int c) {
    v16i match = {};
    for(int i = l-1; i <= r; i += K) {
        if(i+k + K-1 > r) {
            for(int j = 0; i+j+k <= r; j++) {
                if(pref[i+j+k] - pref[i+j] == c)
                    return true;
            }
            break;
        }
        v16i a, b;
        memcpy(&a, &pref[i], sizeof(v16i));
        memcpy(&b, &pref[i+k], sizeof(v16i));
        match |= (b - a) == c;
        // for(int j = 0; j < K; j++) {
        //     if(pref[i+j+k] - pref[i+j] == c)
        //         return true;
        // }
    }
    for(int j = 0; j < K; j++)
        if(match[j])
            return true;
    return false;
}
int main() {
    scanf("%d", &n);
    // v16i vs;
    for(int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        Q[i].v = a;
        Q[i].l = i+1;
        Q[i].r = -1;
    }
    scanf("%d", &q);
    // if(n+q > 300000) return 3;
    for(int i = 0; i < q; i++) {
        scanf("%d%d%d%d%d", &Q[i+n].v, &Q[i+n].l, &Q[i+n].r, &Q[i+n].c, &Q[i+n].k), Q[i+n].id = i;
        auto &qq = Q[i+n];
        // if(qq.v <= 0 || qq.c < 0 || qq.r <= 0 || qq.l <= 0 || qq.r > n || qq.l > n) return 3;
    }
    std::sort(Q, Q+q+n);
    for(int i = 0; i < n+q; i++) {
        // printf("%d\n", Q[i].v);
        if(Q[i].r == -1) {
            add(Q[i].l);
        } else {
            // for(int j = 0; j < n; j++) printf("%d%c", pref[i], j+1==n ? '\n' : ' ');
            ans[Q[i].id] = query(Q[i].l, Q[i].r, Q[i].k, Q[i].c);
        }
    }
    for(int i = 0; i < q; i++)
        printf("%d\n", ans[i]);
}
