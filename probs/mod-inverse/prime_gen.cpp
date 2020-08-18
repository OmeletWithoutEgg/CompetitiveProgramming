#include <bits/stdc++.h>

using namespace std;

int np[10000001];
vector<int> prs;
void init(int M) {
    for(int i = 2; i <= M; i++) {
        if(!np[i]) prs.push_back(i);
        for(int64_t p:prs) {
            if(i*p > M) break;
            np[i*p] = 1;
            if(i%p == 0) break;
        }
    }
}
signed main(int argc, char *argv[]) {
    //ios_base::sync_with_stdio(0), cin.tie(0);
    mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
    init(atoi(argv[1]));
    int Q = atoi(argv[2]);
    int m = prs[uniform_int_distribution<int>(0,prs.size()-1)(rnd)];
    int q = uniform_int_distribution<int>(1,min(Q,m-1))(rnd);
    vector<int> x(q);
    for(int &t:x) t = uniform_int_distribution<int>(1,m-1)(rnd);
    cout << m << ' ' << q << '\n';
    for(int t:x) cout << t << '\n';
}
