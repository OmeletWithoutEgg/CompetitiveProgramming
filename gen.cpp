#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
typedef long long ll;
const ll inf = 1e15;

signed main(int argc, char *argv[]) {
    if(argc < 2) return 0;
    ios_base::sync_with_stdio(0), cin.tie(0);
    random_device rd;
    mt19937_64 rng(rd());
    const int N = atoi(argv[1]);
    const int C = atoi(argv[2]);
    int n = uniform_int_distribution<int>(1, N)(rng);
    int m = uniform_int_distribution<int>(1, N)(rng);
    int k = uniform_int_distribution<int>(1, N)(rng);
    for(int i = 0; i < n; i++) cout << uniform_int_distribution<int>(0, C) << " \n"[i+1==n];
    for(int i = 0; i < m; i++) cout << uniform_int_distribution<int>(0, 1000) << " \n"[i+1==m];
}
