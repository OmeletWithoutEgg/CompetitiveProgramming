#include <bits/stdc++.h>
#ifdef local
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(...) qqbx(#__VA_ARGS__,  __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...); // C++ 17!
}
#endif // local
#define pb emplace_back

using namespace std;

array<int,52> card[11];
array<int,52> perfectShuffle(const array<int,52> &v, bool inv) {
    array<int,52> res;
    if(!inv) {
        for(int i = 0; i < 26; i++) res[i<<1] = v[i+26], res[i<<1|1] = v[i];
    } else {
        for(int i = 0; i < 26; i++) res[i+26] = v[i<<1], res[i] = v[i<<1|1];
    }
    return res;
}
int dist(const array<int,52> &a, array<int,52> b) {
    int cnt = 0;
    array<int,52> pos;
    for(int i = 0; i < 52; i++) pos[a[i]] = i;
    for(int i = 0; i < 52; i++) {
        if(pos[b[i]] != i) {
            swap(b[i], b[pos[b[i]]]);
            ++cnt;
        }
    }
    return cnt;
}
vector<pair<int,int>> error, best;
bool found;
bool cmp(vector<pair<int,int>> a, vector<pair<int,int>> b) {
    if(a.size() != b.size()) return a.size() < b.size();
    if(a.empty()) return 0;
    for(int i = a.size()-1; i >= 0; i--) if(a[i] != b[i]) return a[i] < b[i];
    return 0;
}
void dfs(array<int,52> v, int dep) {
    int diff = dist(v, card[dep]);
    if(diff > dep) return;
    if(found && error.size()+diff > best.size()) return;
    if(dep == 0) {
        if(!found || cmp(error, best))
            best = error;
        found = true;
        return;
    }
    dfs(perfectShuffle(v, true), dep-1);
    for(int i = 0; i+1 < 52; i++) {
        if(v[i] == card[dep][i] && v[i+1] == card[dep][i+1]) continue; // good pruning?
        swap(v[i], v[i+1]);
        error.pb(i, dep);
        dfs(perfectShuffle(v, true), dep-1);
        swap(v[i], v[i+1]);
        error.pop_back();
    }
}
void solve(array<int,52> v) {
    for(int i = 0; i <= 10; i++) {
        if(dist(v, card[i]) <= i) {
            found = false;
            dfs(v, i);
            assert(found);
            cout << "Number of shuffles = " << i << '\n';
            if(best.empty()) {
                cout << "No error in any shuffle\n";
            } else {
                reverse(best.begin(), best.end());
                for(auto p: best)
                    cout << "Error in shuffle " << p.second << " at location " << p.first << '\n';
            }
            cout << '\n';
            return;
        }
    }
    cout << "QAQ\n";
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    iota(card[0].begin(), card[0].end(), 0);
    for(int i = 1; i <= 10; i++) card[i] = perfectShuffle(card[i-1], false);
    int t = 1;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        array<int,52> in;
        for(int i = 0; i < 52; i++) cin >> in[i];
        cout << "Case " << tc << '\n';
        solve(in);
    }
}
