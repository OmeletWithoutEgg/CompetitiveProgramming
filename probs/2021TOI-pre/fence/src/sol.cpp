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

using namespace std;
using ll = long long;

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

const int maxn = 200025;
template <typename T>
struct FenwickTree {
    T b[maxn];
    void add(int p, T v) {
        for (; p < maxn; p += p & -p)
            b[p] = max(b[p], v);
    }
    T qry(int p) {
        T mx{};
        for (; p > 0; p -= p & -p)
            mx = max(mx, b[p]);
        return mx;
    }
};

FenwickTree<tuple<int,int,int>> fwt;
signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    map<int,int> posb;
    for (int i = 0; i < n; i++) {
        posb[b[i]] = i;
    }
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = posb[a[i]];
    }
    vector<int> nxt(n);
    int bestLen = 0, bestStart = 0;
    for (int i = n-1; i >= 0; i--) {
        auto [len, _, j] = fwt.qry(n - p[i]);
        fwt.add(n - p[i], { len + 1, a[i], i });
        nxt[i] = j;
        if (bestLen < len + 1 || (bestLen == len + 1 && a[bestStart] < a[i])) {
            bestLen = len + 1;
            bestStart = i;
        }
    }
    vector<int> c;
    for (int i = 0, x = bestStart; i < bestLen; i++) {
        c.push_back(a[x]);
        x = nxt[x];
    }
    for (int i = 0; i < bestLen; i++)
        cout << c[i] << (i+1==bestLen ? '\n' : ' ');
    debug(bestLen);
}
