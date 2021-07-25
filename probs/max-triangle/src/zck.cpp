#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
const int maxn = 500010;
int n;
ll x[maxn], y[maxn], res;
ll area(int i, int j, int k){
	return abs(x[i]*y[j]+x[j]*y[k]+x[k]*y[i] - y[i]*x[j] - y[j]*x[k] - y[k]*x[i]);
}
signed main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for(int i = 0;i < n;++i)cin >> x[i] >> y[i];
	for(int i = n;i < maxn;++i)x[i] = x[i-n], y[i] = y[i-n];
	n *= 4;
	for(int i = 0, j = 1, k = 2;k < n;++i){
		while(k < n && area(i, j, k) <= area(i, j, k+1))++k;
		res = max(res, area(i, j, k)); 
		while(j < k && area(i, j, k) <= area(i, j+1, k))++j;
		res = max(res, area(i, j, k));
	}
	cout << res << '\n';
}
