#include <bits/stdc++.h>
#define all(v) begin(v),end(v)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}

using namespace std;

// C++ 17
int n, m;
void solve() {
    vector<pair<int,int>> A(m), B(n);
    /* for(auto &[a, b]: A) cin >> a >> b; */
    /* for(auto &[a, b]: B) cin >> a >> b; */
    mt19937 rng(m+n);
    auto randint = [&rng](int l, int r) { return uniform_int_distribution<int>(l, r)(rng); };
    for(auto &[a, b]: A) a = randint(1, 1000), b = randint(1, 1000);
    for(auto &[a, b]: B) a = randint(1, 1000), b = randint(1, 1000);
    sort(all(A)), sort(all(B));
    {
        vector<pair<int,int>> va, vb;
        sort(A.begin(), A.end());
        sort(B.begin(), B.end(), greater<pair<int,int>>());
        for(auto p: A) if(va.empty() || va.back().second > p.second) va.push_back(p);
        for(auto p: B) if(vb.empty() || vb.back().second < p.second) vb.push_back(p);
        A = va, B = vb;
        reverse(B.begin(), B.end());
    }
}
signed main() {
    /* ios_base::sync_with_stdio(0), cin.tie(0); */
    while(cin >> m >> n) solve();
}
