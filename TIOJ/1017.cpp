#include <cstdio>
#include <cstring>
#define N 1000000

int n,x[N+1] = {}, mi, mx, r;
int match[N+1] = {};
signed main(){
    for(scanf("%lld",&n);~scanf("%lld",&n);){
        for(int i=0;i<n;i++)scanf("%lld",x+i);
        mx = x[0], mi = x[n-1], memset(match,0,sizeof(int)*n), r = 0;
        for(int i=1;i<n-1;i++)if(x[i]>mx)match[i] = true,mx = x[i];
        for(int i=n-2;i>=1;i--)if(x[i]<mi)mi = x[i], match[i]&&(++r);
        printf("%lld\n",r);
    }
}
