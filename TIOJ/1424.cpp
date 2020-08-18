#include <bits/stdc++.h>

using namespace std;
const int N = 1<<20;

int n, v[N], a, b, res;
signed main(){
    cin >> n;
    for(int i = 0; i < n; i++) cin >> v[i];
    priority_queue<int,vector<int>,greater<int> > pq(v,v+n);
    while(pq.size() != 1) {
        a = pq.top(), pq.pop();
        b = pq.top(), pq.pop();
        res += a+b;
        pq.push(a+b);
    }
    cout << res << '\n';
}
