#include <bits/stdc++.h>
#define int long long
#define N 10000000

using namespace std;

vector<int> primes;
void init(){
    bitset<N+1> notP;
    for(int i = 2;i < N;i++){
		if(!notP[i])primes.push_back(i);
        for(auto p:primes){
            if(i*p<N)notP[i*p] = true;
			else break;
            if(i%p == 0)break;
        }}

}
signed main(){
    ios::sync_with_stdio(false), cin.tie(0);
    int q, t;
    init();
    cin >> q;
    while(q--){
        cin >> t;
        cout << (upper_bound(primes.begin(),primes.end(),t) - primes.begin()) << '\n';
    }
    return 0;
}
