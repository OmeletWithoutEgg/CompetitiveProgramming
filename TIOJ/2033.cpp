#include <bits/stdc++.h>

using namespace std;
const int N = 3000025;

int v[N*2], u[N], p;
int pos[N], vis[N];
char readchar() {
    static const int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && ((p=buf) == (q=buf+fread(buf, 1, B, stdin)))) return EOF;
    return *p++;
}
int nextint() {
    int x = 0, c = readchar();
    while(c < '0' && ~c) c = readchar();
    while(c >= '0') x = x*10 + (c^'0'), c = readchar();
    return x;
}
bool fail() {
    puts("-1");
    exit(0);
}
signed main() {
    int x;
    while(x = nextint()) v[p++] = x;
    if(p&1) fail();
    for(int i = p/2; i < p; i++) u[i-p/2] = v[i];
    p /= 2;
    int ans = p;
    for(int i = 0; i < p; i++) if(v[i] < 1 || v[i] > p) fail();
    for(int i = 0; i < p; i++) if(u[i] < 1 || u[i] > p) fail();
    for(int i = 0; i < p; i++) pos[--v[i]] = i;
    for(int i = 0; i < p; i++) if(!vis[i]) {
        for(int x = i; !vis[x]; x = pos[--u[x]])
            vis[x] = true;
        --ans;
    }
    printf("%d\n", ans);
}

