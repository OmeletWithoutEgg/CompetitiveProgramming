#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll gcd(ll a, ll b){
    ll t;
    while(b)t = a%b,a = b,b = t;
    return a;
}
int main(){
    ll q, p, g, t;
    scanf("%lld %lld",&q,&p);
    t = p/q + (p%q!=0);
    printf("%lld/%lld = (1/%lld)",q,p,t);
    q *= t,q -= p,p *= t;
    g = gcd(q,p),q /= g,p /= g;
    while(q > 0){
        t = p/q + (p%q!=0);
        //printf("%d/%d ",q,p);
        printf("+(1/%lld)",t);
        q *= t,q -= p,p *= t;
        g = gcd(q,p),q /= g,p /= g;
    }
    printf("\n");
    return 0;
}
