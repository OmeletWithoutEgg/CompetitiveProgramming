#include<bits/stdc++.h>
#define ll long long
#define pii pair<ll,ll>
using namespace std;

ll n, dis[200005];
set<ll, greater<ll>> s;
vector<pii> E[200005];

void dfs(int x, int p){
	for(auto i:E[x]){
		int to = i.first, d = i.second;
		if(to == p) continue;
		dis[to] = dis[x] + d;
		dfs(to, x);
	}
}

void dfs2(int x, int p, ll cur){
	s.insert(cur);
	for(auto i:E[x]){
		int to = i.first, d = i.second;
		if(to == p) continue;
		dfs2(to, x, cur + d);
	}
}

int main() {
	
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	
	auto st = clock();
	
	for(int i=1,a,b,c;i<n;i++) cin >> a >> b >> c, a++, b++, E[a].emplace_back(b, c), E[b].emplace_back(a, c);	
	dfs(1, 0);
	ll far = max_element(dis+1, dis+1+n) - dis;
	
	fill(dis+1, dis+n, 0);
	dfs(far, 0);
	
	ll md = *max_element(dis+1, dis+1+n);
	for(int i=1,cnt=0;i<=n;i++){
		if(dis[i] == md) dfs2(i, 0, 0), ++cnt;
		if(cnt > 100) break;
	}
	dfs2(far, 0, 0);
	s.erase(s.begin());
	cout << *s.begin() << '\n';
}
