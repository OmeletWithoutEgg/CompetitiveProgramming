#include <bits/stdc++.h>

using namespace std;
const int maxn = 500025;

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

int N, M, T, D;
int w[maxn];
int64_t K;
vector<pair<int,bool>> evt[maxn];
vector<pair<int,int64_t>> piece;
map<int,pair<int,int>> mp;
void add(int x, int d, int i) {
    if(!mp.count(x)) mp[x] = {0, -1};
    auto &[cnt, last] = mp[x];
    piece.emplace_back(x, 1LL * cnt * (i - last));
    cnt += d;
    last = i;
}
signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> N >> M >> K >> T >> D;
    for(int i = 0; i < N; i++) cin >> w[i];
    sort(w, w+N);
    for(int i = 0; i < M; i++) {
        int t, a, b;
        cin >> t >> a >> b;
        int apos = lower_bound(w, w+N, a) - w;
        int bpos = upper_bound(w, w+N, b) - w;
        evt[apos].emplace_back(t, 1);
        evt[bpos].emplace_back(t, 0);
    }
    set<int> s{T};
    int ans = 0;
    for(int i = 0; i < N; i++) {
        for(auto [t, type]: evt[i]) {
            if(type) {
                // add t
                auto it = s.insert(t).first;
                if(it != s.begin()) {
                    int nxt = *next(it), prv = *prev(it);
                    add(nxt - prv, -1, i);
                    add(t - prv, 1, i);
                    add(nxt - t, 1, i);
                } else {
                    int nxt = *next(it);
                    add(nxt - t, 1, i);
                }
            } else {
                // delete t;
                auto it = s.find(t);
                if(it != s.begin()) {
                    int nxt = *next(it), prv = *prev(it);
                    add(nxt - prv, 1, i);
                    add(t - prv, -1, i);
                    add(nxt - t, -1, i);
                } else {
                    int nxt = *next(it);
                    add(nxt - t, -1, i);
                }
                s.erase(it);
            }
        }
        ans = (ans + *s.begin()) % D;
    }
    for(auto [t, _]: mp) add(t, 0, N);
    ans = 1LL * ans * (K%D) % D;
    sort(piece.begin(), piece.end(), greater<>());
    for(auto [len, cnt]: piece) {
        len %= D;
        if(cnt < K) {
            // K;
            int C = cnt & 1 ? (cnt%D) * ((2*K-cnt+1)/2%D) % D
                            : (cnt/2)%D * ((2*K-cnt+1)%D) % D;
            ans = (ans + 1LL * len * C) % D;
            K -= cnt;
        } else {
            int C = K & 1 ? (K%D) * ((K+1)/2%D) % D
                          : (K/2)%D * ((K+1)%D) % D;
            ans = (ans + 1LL * len * C) % D;
            K = 0;
            break;
        }
    }
    cerr << N << ' ' << M << ' ' << D << '\n';
    if(K != 0) {
        cerr << "K = " << K << '\n';
    }
    cout << ans << '\n';
}
