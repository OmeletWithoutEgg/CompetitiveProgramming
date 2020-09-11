#include <bits/stdc++.h>
using namespace std;

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


int calc(int n, int m) {
    int r = 0;
    for(int i = 1; i <= n; i++)
        r = (r + m) % i;
    return r;
    /* if(n == 1) return 0; */
    /* return (calc(n-1, m) + m) % n; */
}
signed main() {
    TIME;
    int n, k;
    cin >> n >> k;
    --k;
    for(int i = 2; i <= 30000; i++) if(calc(n, i) == k) return cout << i << '\n', 0;
    cout << 0 << '\n';
}
