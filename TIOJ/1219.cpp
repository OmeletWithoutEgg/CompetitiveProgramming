#include <cstdio>
#include <vector>

const int N = 50025;
bool sv[N];
int mu[N], smu[N];
std::vector<int> prs;
inline int min(int a, int b) {return a<b?a:b;}
signed main() {
    mu[1] = 1;
    for(int i = 2; i < N; i++) {
        if(!sv[i]) prs.emplace_back(i), mu[i] = -1;
        for(int p: prs) {
            if(i*p >= N) break;
            sv[i*p] = true;
            if(i%p) {
                mu[i*p] = -mu[i];
            }else {
                mu[i*p] = 0;
                break;
            }
        }
    }
    for(int i = 1; i < N; i++) smu[i] = smu[i-1]+mu[i];
    int n, m, g;
    while(scanf("%d%d%d", &n, &m, &g), n || m || g) {
        n /= g, m /= g;
        long long ans = 0;
        for(int i = 1, j; i <= n && i <= m; i = j) {
            j = min(n/(n/i), m/(m/i))+1;
            ans += 1LL * (smu[j-1] - smu[i-1]) * (n/i) * (m/i);
        }
        printf("%lld\n", ans);
    }
}
