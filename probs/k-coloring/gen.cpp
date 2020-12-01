#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char *argv[]) {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int n = uniform_int_distribution<int>(1,N)(rng);
    int m = uniform_int_distribution<int>(0,min(M,n*(n-1)/2))(rng);
    int k = uniform_int_distribution<int>(1,N)(rng);
    vector<pair<int,int>> edge;
    for(int i = 1; i <= n; i++) for(int j = 1; j < i; j++) edge.emplace_back(j,i);
    shuffle(edge.begin(), edge.end(), rng);
    cout << n << ' ' << m << ' ' << k << '\n';
    for(int i = 0; i < m; i++) cout << edge[i].first << ' ' << edge[i].second << '\n';
}
