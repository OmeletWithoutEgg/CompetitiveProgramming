#include <bits/stdc++.h>

#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
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

#else
#define debug(...) ((void)0)
#define TIME ((void)0)
#endif // local
#define pb emplace_back

using namespace std;
const int N = 200025;

int n, m;
int cnt[N];
int mx;
set<int> cntPos[N];
vector<int> ans;
void add(int x, int c) {
    cntPos[cnt[x]].erase(x);
    cnt[x] += c;
    cntPos[cnt[x]].insert(x);
    mx = max(mx, cnt[x]);
    while(cntPos[mx].empty()) --mx;
}
bool tryTake(int i, int &r, pair<int,int> &f) {
    int R = r;
    pair<int,int> F = f;
    add(i, -1);
    if(f.first == i) ++f.second;
    else if(f.second > 0) --f.second, r -= 2;
    else f = {i, 1};
    if(max(mx, f.second) * 2 <= r) return true;
    add(i, 1);
    r = R;
    f = F;
    return false;
}
signed main() {
// #ifndef local
//     freopen("gangs.in", "r", stdin);
//     freopen("gangs.out", "w", stdout);
// #endif // !local

    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) cin >> cnt[i];
    if(m == 1) {
        cout << "YES\n";
        cout << n << '\n';
        for(int i = 0; i < n; i++) cout << 1 << '\n';
        return 0;
    } else if(m == 2) {
        if(cnt[0] <= cnt[1]) cout << "NO\n";
        else {
            cout << "YES\n";
            cout << cnt[0] - cnt[1] << '\n';
            for(int i = 0; i < cnt[0]; i++) cout << 1 << '\n';
            for(int i = 0; i < cnt[1]; i++) cout << 2 << '\n';
        }
        return 0;
    }
    for(int i = 1; i < m; i++) {
        cntPos[cnt[i]].insert(i);
        mx = max(mx, cnt[i]);
    }
    if(mx * 2 > n - 1) return cout << "NO\n", 0;
    int keep = cnt[0];
    while(mx * 2 > n - keep || (n - keep) % 2 == 1) --keep;
    if(keep <= 0) return cout << "NO\n", 0;
    debug(keep);
    for(int i = 0; i < cnt[0] - keep; i++) ans.pb(0);
    pair<int,int> field = {0, cnt[0] - keep};
    /* ans.pb(-2); */
    int rest = n - keep;
    for(int t = 0, i = 1; t < n - cnt[0]; t++) {
        while(i < m && !cnt[i]) ++i;
        vector<int> candidate{i, field.first, *cntPos[mx].begin()};
        sort(candidate.begin(), candidate.end());
        for(int x: candidate) {
            if(x && x < m && cnt[x]) {
                // debug(x);
                if(tryTake(x, rest, field)) {
                    ans.pb(x);
                    break;
                }
            }
        }
        /* cerr << "cnt =\n"; */
        /* for(int j = 0; j < m; j++) cerr << cnt[j] << ' '; */
        /* cerr << '\n'; */
    }
    for(int i = 0; i < keep; i++) ans.pb(0);
    cout << "YES\n";
    cout << keep << '\n';
    for(int x: ans) cout << x+1 << '\n';
}

/*
8 4
2 2 2 2

9 3
4 4 1

8 3
4 3 1 (perm)

5 3
2 1 2
*/
