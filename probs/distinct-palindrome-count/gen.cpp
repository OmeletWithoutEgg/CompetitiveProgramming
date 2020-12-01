#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/extc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
signed main(int argc, char *argv[]) {
    if(argc < 2) return 0;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int N = atoi(argv[1]);
    int K = atoi(argv[2]);
    int n = uniform_int_distribution<int>(1,N)(rng);
    string s(n, '\0');
    for(char &c: s) c = char('a'+uniform_int_distribution<int>(0,K-1)(rng));
    cout << s << '\n';
}

