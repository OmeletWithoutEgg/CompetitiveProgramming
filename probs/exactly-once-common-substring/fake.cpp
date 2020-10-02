#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<string> v(n);
    for(auto &s: v) cin >> s;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    if(v.size() == 1) return cout << v[0] << '\n', 0;
    string mn;
    for(auto &s: v) if(mn.empty() || s.size() < mn.size()) mn = s;
    /* for(auto &s: v) if(s.size() == mn.size() && s != mn) return cout << 7122 << '\n', 0; */
    auto check = [&](int len) -> int {
        bool bigger = false, smaller = false;
        for(int i = 0; i+len <= mn.size(); i++) {
            string ans = mn.substr(i, len);
            vector<int> fail(len);
            for(int i = 1, j = 0; i < ans.size(); i++) {
                while(j && ans[j] != ans[i]) j = fail[j-1];
                if(ans[i] == ans[j]) ++j;
                fail[i] = j;
            }
            bool ok = 1;
            for(auto &s: v) {
                int occ = 0;
                for(int i = 0, j = 0; i < s.size(); i++) {
                    while(j && s[i] != ans[j]) j = fail[j-1];
                    if(s[i] == ans[j]) ++j;
                    if(j == ans.size()) {
                        j = fail[j-1];
                        if(occ++) {
                            ok = 0;
                            bigger = true;
                            break;
                        }
                    }
                }
                if(!occ) {
                    ok = 0;
                    smaller = true;
                }
                if(!ok) break;
            }
            if(ok) return cout << ans << '\n', 0;
        }
        if(smaller) return -1;
        /* if(bigger && smaller) return 404; */
        return bigger ? 1 : -1;
    };
    int l = 1, r = mn.size()+1;
    while(l+1 != r) {
        int mid = l+(r-l)/2;
        int c = check(mid);
        /* if(c == 404) return cout << 7122 << '\n', 0; */
        if(c == 0) return 0;
        if(c == 1) l = mid;
        else r = mid;
    }
    cout << 7122 << '\n';
}
