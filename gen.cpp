#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "\e[032;1m(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\e[0m\n")));
}
#else
#define debug(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define pb emplace_back

using namespace std;
const int maxn = 100025, mod = 998244353, inf = 1e9, maxc = 100025;
const int64_t INF = 1e18;

signed main(int argc, char **argv) {
    assert (argc >= 2);
    ios_base::sync_with_stdio(0), cin.tie(0);
    const int seed = atoi(argv[1]);
    mt19937 rng(seed);

    vector<vector<int>> perms;
    int cnt = 0;
    for (int N = 2; N <= 8; N++) {
        vector<int> perm(N);
        iota(all(perm), 0);
        do {
            perms.emplace_back(perm);
            cnt += perm.size();
        } while (next_permutation(all(perm)));
    }

    // for (int it = 0; it < 5; it++) {
    //     int N = 1000000;
    //     vector<int> p(N);
    //     for (int i = 0; i < N; i++) {
    //         p[i] = (i & 1 ? N - i/2 : i/2);
    //     }
    //     cnt += N;
    //     perms.emplace_back(p);
    // }

    shuffle(perms.begin(), perms.end(), rng);

    int T = perms.size();
    debug(cnt, T);
    cout << T << '\n';
    for (const auto &perm: perms) {
        int N = perm.size() - 1;
        cout << N << '\n';
        for (int i = 1; i <= N; i++) {
            cout << perm[i] - perm[i-1] << (i==N ? '\n' : ' ');
        }
    }
}
