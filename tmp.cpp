#include <bits/stdc++.h>
#define TIME Timer __timer(__PRETTY_FUNCTION__)
using namespace std;
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

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for(int &x: v) cin >> x;
    TIME;
// #define SORT_UNIQUE
#ifdef SORT_UNIQUE
    vector<int> u = v;
    sort(u.begin(), u.end());
    u.erase(unique(u.begin(), u.end()), u.end());
#else
    unordered_set<int> s(v.begin(), v.end());
    vector<int> u(s.begin(), s.end());
#endif
    cout << accumulate(u.begin(), u.end(), 0LL) << '\n';
}
