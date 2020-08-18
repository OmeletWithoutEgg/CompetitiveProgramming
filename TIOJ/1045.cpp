#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define debug(x) cerr<<#x<<" = "<<x<<'\n'
#define ff first
#define ss second

using namespace std;
typedef long long ll;
const int SZ = 75;

int n;
ll x, y, z, R, G, B, sum;
signed main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        scanf("%lld%lld%lld", &R, &G, &B);
        x = 5149 * R + 3244 * G + 1607 * B;
        y = 2654 * R + 6704 * G +  642 * B;
        z =  248 * R + 1248 * G + 8504 * B;
        printf("%lld.%04lld ", x/10000,x%10000);
        printf("%lld.%04lld ", y/10000,y%10000);
        printf("%lld.%04lld\n",z/10000,z%10000);
        sum += y*10;
    }
    sum /= n*n;
    if(sum%10 >= 5) sum += 5;
    sum /= 10;
    printf("The average of Y is %lld.%04lld\n", sum/10000, sum%10000);
}
