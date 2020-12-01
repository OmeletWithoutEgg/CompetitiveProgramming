#include <bits/stdc++.h>
//#undef local
using namespace std;
#ifdef local
const int N = 64;
#else
const int N = 131072;
#endif // local
int ask[N], qq[N], sum[N];

#ifndef local
#include "lib1945.h"
#else
int ans[N], cnt, lie;
void Init() {
    srand(time(0));
    cin >> lie;
    for(int i = 0; i < N; i++) ans[i] = rand()%2;
}
int Query(int n,int a[]) {
    int r = 0;
    if(cnt++ == lie) r = 1;
    for(int i = 0; i < n; i++) r^=ans[a[i]];
    return r;
}
#endif // local

signed main() {
    //ios_base::sync_with_stdio(0), cin.tie(0);
    Init();
    for(int i = 0; i < N; i++) {
        ask[i] = i;
        qq[i] = Query(1,ask+i);
    }
    sum[0] = qq[0];
    for(int i = 1; i < N; i++) sum[i] = sum[i-1]^qq[i];
    int x = 0;
    for(int s = N>>1; s; s>>=1) if(Query(x+s+1,ask) == sum[x+s]) x+=s;
    //cerr<<"x="<<x<<'\n';
    x++;
    if(x < N) {
        int jx = Query(1,ask+x);
        if(jx != qq[x]) qq[x] = Query(1,ask+x);
    }
    for(int i = 0; i < N; i++) cout << qq[i] << " \n"[i+1==N];
    #ifdef local
    cerr<<"cnt = "<<cnt<<'\n';
    for(int i = 0; i < N; i++) cout << ans[i] << " \n"[i+1==N];
    for(int i = 0; i < N; i++) if(qq[i]!=ans[i]) cout << "WA\n";
    #endif // local
}
