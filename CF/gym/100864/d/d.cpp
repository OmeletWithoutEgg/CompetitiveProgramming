
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

ll n,m,sx=1,sy,tx,ty;
char stat;
map<char,array<char,4>> to;
//0 -> front 1 -> left 2 -> right 3 -> back

string ans = "";
void roll(int x){
	if(x == 0){
		stat = to[stat][0];
		ans += 'F';
		sx++;
	}
	if(x == 1){
		stat = to[stat][1];
		ans += 'L';
		sy--;
	}
	if(x == 2){
		stat = to[stat][2];
		ans += 'R';
		sy++;
	}
	if(x == 3){
		stat = to[stat][3];
		ans += 'B';
		sx--;
	}
	/* cout<<stat<<'\n'; */
	assert(stat != 'X');
	/* cout<<sx<<" "<<sy<<'\n'; */
}


bool tryroll(){
	if(sx > 1 && sy > 1 && stat != 'B' && stat != 'L'){
		for(auto i:{3,1,0,2}) roll(i);
		return 1;
	}
	if(sx > 1 && sy < m && stat != 'B' && stat != 'R'){
		for(auto i:{3,2,0,1}) roll(i);
		return 1;
	}
	if(sx < n && sy < m && stat != 'F' && stat != 'R'){
		for(auto i:{0,2,3,1}) roll(i);
		return 1;
	}
	if(sx < n && sy > 1 && stat != 'F' && stat != 'L'){
		for(auto i:{0,1,3,2}) roll(i);
		return 1;
	}
	return 0;
}

signed main(){
	IOS;
	freopen("delivery.in","r",stdin);
	freopen("delivery.out","w",stdout);
	to['T'] = {'F','L','R','B'};
	to['B'] = {'T','B','B','X'};
	to['F'] = {'X','F','F','T'};
	to['L'] = {'L','X','T','L'};
	to['R'] = {'R','T','X','R'};
	cin>>n>>m>>sy>>tx>>ty;
	cin>>stat;
	while(sx != tx){
		if(sx < tx){
			while(sx != tx){
				while(sx != tx && to[stat][0] != 'X') roll(0);
				if(sx == tx) break;
				bool ok = tryroll();
				if(!ok){
					cout<<"IMPOSSIBLE\n";
					return 0;
				}
			}
		}
		else{
			while(sx != tx){
				while(sx != tx && to[stat][3] != 'X') roll(3);
				if(sx == tx) break;
				bool ok = tryroll();
				if(!ok){
					cout<<"IMPOSSIBLE\n";
					return 0;
				}
			}
		}
	}
	while(sy != ty){
		if(sy < ty){
			while(sy != ty){
				while(sy != ty && to[stat][2] != 'X') roll(2);
				if(sy == ty) break;
				bool ok = tryroll();
				if(!ok){
					cout<<"IMPOSSIBLE\n";
					return 0;
				}
			}
		}
		else{
			while(sy != ty){
				while(sy != ty && to[stat][1] != 'X') roll(1);
				if(sy == ty) break;
				bool ok = tryroll();
				if(!ok){
					cout<<"IMPOSSIBLE\n";
					return 0;
				}
			}
		}
	}
	cout<<ans<<'\n';
}

