
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define pb emplace_back
#define all(n) (n).begin(),(n).end()
#define mem(n,x) memset(n,x,sizeof(n))
#define IOS ios::sync_with_stdio(0),cin.tie(0)
#define pii pair<ll,ll>
#define vi vector<ll>
#define dbg(...) cerr<<#__VA_ARGS__<<" = ";_do(__VA_ARGS__);
template<typename A> void _do(A x){ cerr<<x<<"\n"; }
template<typename A, typename ...B> void _do(A x, B ...y){ cerr<<x<<", "; _do(y...);}

int n,m;
char arr[205][205];

signed main(){
	freopen("japanese.in","r",stdin);
	freopen("japanese.out","w",stdout);
	IOS;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>arr[i][j];
		}
	}

	deque<int> r[205], c[205];

	for(int i=1;i<=n;i++){
		int res = 0;
		for(int j=1;j<=m;j++){
			if(arr[i][j] == '.'){
				if(res) r[i].pb(res);
				res = 0;
			}
			else res++;
		}
		if(res) r[i].pb(res);
	}

	for(int j=1;j<=m;j++){
		int res = 0;
		for(int i=1;i<=n;i++){
			if(arr[i][j] == '.'){
				if(res) c[j].pb(res);
				res = 0;
			}
			else res++;
		}
		if(res) c[j].pb(res);
	}

	int mxi = 0, mxj = 0;
	for(int i=1;i<=n;i++) mxi = max(mxi, (int)r[i].size());
	for(int i=1;i<=n;i++) while(r[i].size() < mxi) r[i].push_front(0); 
	for(int j=1;j<=m;j++) mxj = max(mxj, (int)c[j].size());
	for(int j=1;j<=m;j++) while(c[j].size() < mxj) c[j].push_front(0);
	
	for(int i=0;i<mxj;i++){
		for(int j=0;j<mxi;j++) cout<<"*";
		for(int j=1;j<=m;j++){
			if(c[j][i] == 0) cout<<"_";
			else cout<<c[j][i];
		}
		cout<<'\n';
	}

	for(int i=1;i<=n;i++){
		for(int x:r[i]){
			if(x == 0) cout<<"_";
			else cout<<x;
		}
		for(int j=1;j<=m;j++){
			cout<<".";
		}
		cout<<'\n';
	}
}

