#include <bits/stdc++.h>

using namespace std;
const int K = 1050;

vector<int> primes;
bitset<K> notP;
void init(){
    for(int i=2;i<K;i++){
        if(!notP[i]) primes.push_back(i);
        for(int p:primes){
            if(i*p>=K) break;
            notP[i*p] = true;
            if(i%p == 0) break;
        }
    }
}
int mu(int n){
    int res = 1;
    for(int p:primes) if(n%p==0){
        n /= p, res *= p-1;
        while(n%p == 0) res *= p, n/=p;
        if(n==1) return res;
    }
    return res*(n-1);
}
signed main(){
    init();
    int n,v;
    double sum;
    ios_base::sync_with_stdio(0),cin.tie(0),cout << fixed << setprecision(2);
    for(cin>>n;cin>>n;){
        sum = 0;
        for(int i = 0; i < n; i++) cin >> v, sum += mu(v);
        cout << sum/n << '\n';
    }
}
