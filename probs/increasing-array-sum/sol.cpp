#include <bits/stdc++.h>
#define TIME Timer __timer(__PRETTY_FUNCTION__)
class Timer {
private:
    std::string title;
    std::chrono::high_resolution_clock::time_point start;
public:
    Timer(std::string t) :
        title(t), start(std::chrono::high_resolution_clock::now()) {}
    ~Timer() {
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
        double ms = double(duration) * 0.001;
        std::cerr << "Timer: " << title << " takes " << ms << " ms to finish.\n";
    }
};

using namespace std;
const int N = 1000025;

signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for(int &x: a) cin >> x;
    vector<int> cnt(N);
    for(int i = 0; i < n; i++) {
        int sum = 0;
        for(int j = i; j < n; j++) {
            sum += a[j];
            if(sum >= N) break;
            ++cnt[sum];
        }
    }
    int q;
    cin >> q;
    while(q--) {
        int x;
        cin >> x;
        cout << cnt[x] << '\n';
    }
}
