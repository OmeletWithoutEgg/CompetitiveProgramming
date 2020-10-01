#include <bits/stdc++.h>
#define debug(x) cerr<<#x<<" = "<<x<<'\n'
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

constexpr int base[2] = {293, 123}, mod[2] = {1000000007, 998244353};
struct Hasher : array<int,2> {
    void operator+=(char x) {
        for(int i = 0; i < 2; i++) at(i) = (1LL * at(i) * base[i] + x) % mod[i];
    }
};
signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    string s;
    cin >> n;
    vector<Hasher> ans;
    for(int i = 0; i < n; i++) {
        cin >> s;
        vector<Hasher> v, ok;
        for(int j = 0; j < s.size(); j++) {
            Hasher H = {};
            for(char c: s.substr(j)) {
                H += c;
                v.push_back(H);
            }
        }
        sort(v.begin(), v.end());
        for(int i = 0, j = 0; i < int(v.size()); i = j) {
            for(j = i; j < int(v.size()); j++) if(v[i] != v[j]) break;
            if(j == i+1) ok.push_back(v[i]);
        }
        debug(ok.size());
        sort(ok.begin(), ok.end());
        if(i) {
            vector<Hasher> tmp;
            set_intersection(ok.begin(), ok.end(), ans.begin(), ans.end(), back_inserter(tmp));
            ans = tmp;
        } else {
            ans = ok;
        }
    }
    if(ans.empty()) {
        cout << 7122 << '\n';
    } else {
        for(int j = 0; j < s.size(); j++) {
            Hasher H = {};
            int len = 0;
            for(char c: s.substr(j)) {
                ++len;
                H += c;
                if(binary_search(ans.begin(), ans.end(), H)) {
                    return cout << s.substr(j, len) << '\n', 0;
                }
            }
        }
        exit(3);
    }
}
