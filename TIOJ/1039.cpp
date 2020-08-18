#include <cstdio>
#include <cmath>
#include <algorithm>
struct Team {
    char name[10];
    int W, T, L, id;
    double rate;
    friend bool operator<(const Team &a, const Team &b) {
        return a.rate != b.rate ? a.rate > b.rate : a.id < b.id;
    }
} t[100];
int rest[100][100];
signed main() {
    int n, g;
    bool first = true;
    while(scanf("%d%d", &n, &g), n || g) {
        if(!first) puts("");
        first = false;
        for(int i = 0; i < n; i++) {
            scanf("%s%d%d%d", t[i].name, &t[i].W, &t[i].T, &t[i].L);
            t[i].id = i;
            t[i].rate = t[i].W / double(t[i].W+t[i].L);
        }
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) scanf("%d", &rest[i][j]);
        std::sort(t, t+n);
        int rk = 0;
        double last = 7122;
        for(int i = 0; i < n; i++) {
            if(t[i].rate != last) rk = i+1;
            last = t[i].rate;
            printf("%d:%-9s %.3f", rk, t[i].name, round(t[i].rate * 1000) / 1000);
            if(i) {
                int magic = 0;
                while((t[0].W + magic) / double(g - t[0].T) <= (g - t[i].T - t[i].L) / double(g - t[i].T)) ++magic;
                if(magic <= g - (t[0].W+t[0].T+t[0].L) - rest[t[0].id][t[i].id])
                    printf(" M%d", magic);
                else
                    printf(" --");
            }
            puts("");
        }
    }
}
