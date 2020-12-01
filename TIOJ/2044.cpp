#include <cstdio>

typedef long long ll;
const ll MOD = 1000000007, K = 14699;
int t, n, m;
signed main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        ll last, A, B, ok = 1;
        for(int i = 0; i < n; i++) {
            A = B = 0;
            for(int j = 0; j < m; j++) {
                ll x;
                scanf("%lld", &x);
                if(j != 0) A = (A*K+x)%MOD;
                if(j != m-1) B = (B*K+x)%MOD;
            }
            if(i && A != last) ok = 0;
            last = B;
        }
        puts(ok ? "Yes" : "No");
    }
}

