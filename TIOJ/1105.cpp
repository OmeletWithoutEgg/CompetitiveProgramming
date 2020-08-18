
//   __________________
//  | ________________ |
//  ||          ____  ||
//  ||   /\    |      ||
//  ||  /__\   |      ||
//  || /    \  |____  ||
//  ||________________||
//  |__________________|
//  \###################\
//   \###################\
//    \        ____       \
//     \_______\___\_______\
// An AC a day keeps the doctor away.

#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define all(v) begin(v),end(v)
#define pb emplace_back
#define ff first
#define ss second

using namespace std;
typedef pair<int,int> pii;
constexpr int N = 3001;
inline int readch() {
    const int B = 1<<15;
    static char buf[B], *p = buf, *tail = buf;
    if(p==tail) {
        tail = buf+fread(buf, 1, B, stdin);
        if(tail==buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int next_int() {
    int x = 0, c = readch();
    while('0'>c || c>'9') c=readch();
    while('0'<=c&&c<='9') x=x*10+c-'0', c=readch();
    return x;
}
int n,m;
int lc[N],uc[N],cv[N],id[N];
pii v[N];
inline int operator^(pii a,pii b){return a.ff*b.ss - a.ss*b.ff;}
inline int operator*(pii a,pii b){return a.ff*b.ff + a.ss*b.ss;}
inline pii operator-(pii a,pii b){return {a.ff-b.ff, a.ss-b.ss};}
inline int mag(pii a,pii b){return (a-b)*(a-b);}
void solve() {
    int mx = 0, x, y;
    for(register int i = 0, j = n-1; i < n; i++) {
        while((v[cv[(i+1)%n]]-v[cv[i]] ^ v[cv[(j-1+n)%n]]-v[cv[j]]) >= 0) j = (j-1+n)%n;
        int d = mag(v[cv[i]], v[cv[j]]);
        int a = cv[i], b = cv[j];
        if(mx < d) mx = d, x = a, y = b;
        else if(mx == d && (x > a || (x==a && y>b))) x = a, y = b;
    }
    printf("%d %d\n", x, y);
}
//int mx[10001],mi[10001],mxi[10001],mii[10001];
signed main() {
    //ios_base::sync_with_stdio(0), cin.tie(0);
    while(n=next_int()) {
        int mxx=00, mix=10000;
        for(int i = 0; i < n; i++) {
            v[i].ff = next_int(), v[i].ss = next_int();
            if(v[i].ff>mxx) mxx=v[i].ff;
            if(v[i].ff<mix) mix=v[i].ff;
        }
        iota(id,id+n,0);
        sort(id,id+n,[](int a,int b){return v[a]<v[b];});
        int l = 0, u = 0;
        for(register int i = 0; i < n; i++) {
            while(l >= 2 && (v[id[i]] - v[lc[l-2]] ^ v[id[i]] - v[lc[l-1]]) <= 0) --l;
            while(u >= 2 && (v[id[i]] - v[uc[u-2]] ^ v[id[i]] - v[uc[u-1]]) >= 0) --u;
            lc[l++] = uc[u++] = id[i];
        }
        n = 0;
        for(int i = 0; i < l; i++) cv[n++] = lc[i];
        for(int i = u-2; i >= 1; i--) cv[n++] = uc[i];
        solve();
    }
}

