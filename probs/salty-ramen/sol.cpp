#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 400025;
int a[N],b[N];
int n,k,x,sum;
signed main(){
	cin>>n>>k;
	for(int i=0;i<n;i++)
		cin>>a[i];
	cin>>x;
	for(int i=0;i<n;i++)
		cin>>b[i];
	priority_queue<int,vector<int>,greater<int> > pq;
	for(int i=0;i<n;i++){
		pq.push(b[i]);
		while(k<a[i]){
			if(pq.size()==0){
				cout<<-1<<endl;
				return 0;
			}
			sum+=pq.top();
			k+=x;
			pq.pop();
		}
	}
	cout<<sum<<endl;
	return 0;
}
