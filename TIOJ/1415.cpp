#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll N = 1000000;

int delMx[N+1],delMi[N+1];
signed main(){
    int n,k,v,r;
    while(~scanf("%d",&n)){
        priority_queue<int> max_heap;
        priority_queue<int,vector<int>,greater<int> > min_heap;
        r = 0, memset(delMx,0,sizeof delMx), memset(delMi,0,sizeof delMi);
        while(n--){
            scanf("%d",&k);
            while(k--) scanf("%d",&v), max_heap.push(v), min_heap.push(v);
            while(delMx[max_heap.top()]) --delMx[max_heap.top()], max_heap.pop();
            int mx = max_heap.top(); max_heap.pop(); ++delMi[mx];
            while(delMi[min_heap.top()]) --delMi[min_heap.top()], min_heap.pop();
            int mi = min_heap.top(); min_heap.pop(); ++delMx[mi];
            r += mx-mi;
        }
        printf("%d\n",r);
    }
}
