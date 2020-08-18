#include <cstdio>
#define M 7122
#define N 131

int n,a,sum;
int cnt1[M] = {};
int cnt2[N] = {};
signed main(){
    scanf("%d",&n);
    sum = n;
    while(n--) {
        scanf("%d",&a);
        sum += cnt1[a%M]+cnt2[a%N];
        cnt1[a%M]++, cnt2[a%N]++;
    }
    printf("%d\n",sum);
}
