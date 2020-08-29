#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    for(int tc = 0; tc < 20; tc++) {
        ofstream fout("dui.in");
        fout << n << '\n';
        vector<int> a(n+1);
        for(int i = 2; i <= n; i++) {
            a[i] = uniform_int_distribution<int>(1, i-1)(rng);
            fout << i << ' ' << a[i] << '\n';
        }
        fout.close();
        system("./main <dui.in >dui.out");
        system("./tmp <dui.in >duit.out");
        if(system("diff dui.out duit.out")) {
            cerr << "Error!\n";
            for(int i = 2; i <= n; i++) cout << i << ' ' << a[i] << '\n';
            return 0;
        }
    }
}
