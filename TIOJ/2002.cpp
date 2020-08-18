#include <cstdio>

const int N = 10025;
int offset = 0;
void seek(int pos) {
    fseek(stdin, pos, SEEK_SET);
    offset = pos;
}
char readchar() {
    ++offset;
    return getchar();
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
inline int min(int a, int b){return a<b ? a : b;}
inline int max(int a, int b){return a>b ? a : b;}

int a[N],b[N],ans[N];
int mx[N<<1],s;
int query(int l, int r) {
    l = max(0, min(s, l));
    r = max(0, min(s, r));
    int res = 0;
    for(l+=s,r+=s; l<r; l>>=1,r>>=1) {
        if(l&1) res = max(res, mx[l++]);
        if(r&1) res = max(res, mx[--r]);
    }
    return res;
}
int main() {
    freopen("../in.txt", "r", stdin);
    int n = nextint(), q = nextint();
    int qpos = offset;
    for(int i = 0; i < q; i++) {
        int l = nextint();
        int r = nextint();
        //printf("%d,%d\n",l,r);
    }
    int apos = offset;
    seek(apos+2);
    //for(char c=readchar(); c != -1; c=readchar()) putchar(c);
    //puts("JIZZ\n");

    for(int i = 0; i < q; i += N) {
        seek(qpos);
        for(int j = 0; j < N && i*N+j < q; j++) {
            a[j] = nextint();
            b[j] = nextint();
            --a[j];
            //ans[j] = 0;
        }
        qpos = offset;
        seek(apos+2);
        for(int x = 0; x < n; x += N) {
            s = 0;
            for(int y = 0; y < N && x*N+y < n; y++) mx[s++] = nextint();
            //for(int i = 0; i < s; i++) printf("%d,", mx[i]);
            //puts("");
            for(int i = 0; i < s; i++) mx[i+s] = mx[i];
            for(int i = s-1; i > 0; i--) mx[i] = max(mx[i<<1],mx[i<<1|1]);
            for(int j = 0; j < N && i*N+j < q; j++)
                ans[j] = max(ans[j], query(a[j]-x*N,b[j]-x*N));
        }
        for(int j = 0; j < N && i*N+j < q; j++)
            printf("%d\n", ans[j]);
    }
}
