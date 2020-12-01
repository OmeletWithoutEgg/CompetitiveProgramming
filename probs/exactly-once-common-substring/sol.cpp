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
const int N = 400025;

struct SuffixArray {
    int sa[N], rk[N], nrk[N];
    int H[N];
    int n;
    string S;
    void build(const string &_S) {
        S = _S;
        n = S.size();
        for(int i = 0; i < n; i++) sa[i] = i, rk[i] = S[i];
        for(int L = 1; L < n; L <<= 1) {
            auto cmp = [&](int a, int b) {
                if(rk[a] != rk[b]) return rk[a] < rk[b];
                int ra = a+L < n ? rk[a+L] : -1;
                int rb = b+L < n ? rk[b+L] : -1;
                return ra < rb;
            };
            sort(sa, sa+n, cmp);
            nrk[0] = 0;
            for(int i = 1; i < n; i++) nrk[i] = nrk[i-1] + cmp(sa[i-1], sa[i]);
            for(int i = 0; i < n; i++) rk[sa[i]] = nrk[i];
        }
        for(int i = 0, h = 0; i < n; i++) {
            if(rk[i] == n-1) continue;
            int j = sa[rk[i]+1];
            while(i+h < n && j+h < n && S[i+h] == S[j+h]) ++h;
            H[rk[i]] = h;
            if(h > 0)
                --h;
        }
        /* for(int i = 0; i < n; i++) cout << H[i] << ' ' << S.substr(sa[i]) << '\n'; */
    }
    string solve(int k, vector<int> block) {
        vector<bool> cnt(k+1);
        deque<pair<int,int>> dq;
        for(int i = 0, j = 0; i < n; i++) {
            while(cnt[block[sa[i]]] || cnt[k]) {
                cnt[block[sa[j++]]] = false;
                if(dq.size() && dq.front().second < j) dq.pop_front();
            }
            cnt[block[sa[i]]] = true;
            if(i-j+1 == k && !cnt[k]) {
                int LCP = dq.size() ? dq.front().first : n - sa[j]; // lcp [j .. i] == min H [j .. i)
                if((j == 0 || H[j-1] < LCP) && (i == n-1 || H[i] < LCP)) {
                    string R = S.substr(sa[j], LCP);
                    return R;
                }
            }
            while(dq.size() && dq.back().first >= H[i]) dq.pop_back();
            dq.emplace_back(H[i], i);
        }
        return "7122";
    }
} SA;
signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    /* string t; */
    /* cin >> t; */
    /* SA.build(t); */
    /* return 0; */
    int n, tot = 0;
    cin >> n;
    vector<string> v(n);
    for(string &s: v) cin >> s, tot += s.size()+1;
    vector<int> block(--tot);
    string T;
    for(int i = 0, p = 0; i < n; i++) {
        T += v[i];
        while(p < T.size()) block[p++] = i;
        if(i != n-1) T += '$', block[p++] = n;
    }
    SA.build(T);
    string ans = SA.solve(n, block);
    cout << ans << '\n';
    debug(ans.size());
    /* if(ans.size() > 256) */
    /*     cerr << ans.substr(0, 256) << " ...\n"; */
    /* else */
    /*     cerr << ans << '\n'; */
}
