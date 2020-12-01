#include <cstdio>

int main() {
    long long n;
    while(~scanf("%lld", &n)) {
        if(n > 600000000) printf("%lld\n", n-1);
        else {
            long long phi = 1;
            for(long long i = 2; i*i <= n; i++) if(n%i == 0) {
                phi *= i-1;
                n /= i;
                while(n%i == 0) n/=i, phi*=i;
            }
            if(n > 1) phi *= n-1;
            printf("%lld\n", phi);
        }
    }
}
