#include <bits/stdc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
#define TAK(args...) std::ostream& operator<<(std::ostream &O, args)
#define NIE(STL, BEG, END, OUT) template <typename ...T> TAK(std::STL<T...> v) \
    { O << BEG; int f=0; for(auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }
NIE(deque, "[", "]", e) ; NIE(vector, "[", "]", e)
NIE(set, "{", "}", e) ; NIE(multiset, "{", "}", e) ; NIE(unordered_set, "{", "}", e)
NIE(map , "{", "}", e.first << ":" << e.second)
NIE(unordered_map , "{", "}", e.first << ":" << e.second)
template <typename ...T> TAK(std::pair<T...> p) { return O << '(' << p.first << ',' << p.second << ')'; }
template <typename T, size_t N> TAK(std::array<T,N> a) { return O << std::vector<T>(a.begin(), a.end()); }
template <typename ...T> TAK(std::tuple<T...> t) {
    return O << "(", std::apply([&O](T ...s){ int f=0; (..., (O << (f++ ? ", " : "") << s)); }, t), O << ")";
}
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    if(!cnt) return std::cerr << "\033[1;32m() = ()\033\[0m\n", void();
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
}
#define pb emplace_back

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

signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    string ans, C;
    cin >> C;
    int last = 0, cnt = 0;
    for (char c: C) {
        if (isdigit(c)) {
            last = last * 10 + (c - '0');
        } else {
            ans += string(max(1, last), c);
            last = 0;
            ++cnt;
        }
    }
    assert( last == 0 && cnt > 0 );
    cout << ans << '\n';
    debug(C.size(), ans.size(), cnt);
}
