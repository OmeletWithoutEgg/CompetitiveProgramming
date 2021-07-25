#include<bits/stdc++.h>
using namespace std;
#define RI(x) scanf("%d",&(x))
#define RII(x,y) scanf("%d %d",&(x),&(y))
#define RI64(x) scanf("%I64d",&(x))
#define RII64(x,y) scanf("%I64d%I64d",&(x),&(y))
#define SZ(x) ((int)x.size())
#define ALL(x) (x).begin(),(x).end()
#define pritnf printf
#define N 100514
using namespace std;

#define TIME Timer __timer(__PRETTY_FUNCTION__)
class Timer {
private:
    std::string title;
    chrono::high_resolution_clock::time_point start;
public:
    Timer(std::string t) :
        title(t), start(chrono::high_resolution_clock::now()) {}
    ~Timer() {
        auto finish = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
        double ms = double(duration) * 0.001;
        std::cerr << "Timer: " << title << " takes " << ms << " ms to finish.\n";
    }
};

typedef long long int lnt;
typedef double dou;
typedef struct{lnt x,y;}dot;
int cmp(dot a,dot b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
dot operator-(dot a,dot b){return(dot){a.x-b.x,a.y-b.y};}
lnt operator*(dot a,dot b){return a.x*b.y-a.y*b.x;}

lnt getarea(dot&a,dot&b,dot&c){
	return abs((a-b)*(a-c));
}
int p[N],*l[N],*r[N];
lnt MCIC(dot*d,int n,int m){
	for(int i=0;i<m;i++){
		p[i]=i;
		l[i]=p+(i-1+m)%m;
		r[i]=p+(i+1+m)%m;
	}
	lnt ans=0,area=0;
	for(int k=0,cnt=n+1;cnt;){
		int nx=(p[k]+1)%n;
		if(k==0){
			p[0]=nx;
			for(int i=1;i<m&&p[i]==p[i-1];i++){
				p[i]=(p[i]+1)%n;
			}
			area=0;
			for(int i=0;i<m;i++){
				area+=d[p[i]]*d[*r[i]];
			}
			area=abs(area);
			ans=max(ans,area);
			k=m-1;
			cnt--;
			continue;
		}
		lnt da=0;
		da+=getarea(d[*l[k]],d[nx],d[*r[k]]);
		da-=getarea(d[*l[k]],d[p[k]],d[*r[k]]);
		if( nx!=*r[k] && da>=0 ){
			p[k]=nx;
			ans=max(ans,area+=da);
			k=m-1;
		}
		else{
			k--;
		}
	}
	return ans;
}
int n;
dot d[N];
void sol(){
	for(int i=0;i<n;i++){
		int x,y;
		RII(x,y);
		d[i]=(dot){1ll*x,1ll*y};
	}
	pritnf("%lld\n",MCIC(d,n,3));
}
int main(){
	while(RI(n)!=EOF)sol();
	return 0;
}
