#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
int s[200], p;
signed main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        bool nf = true;
        for(int j = 0; nf && j < p; j++) if(s[j] < x) {
            s[j] = x;
            nf = false;
        }
        if(nf)
            s[p++] = x;
    }
    printf("%d\n", p);
}

