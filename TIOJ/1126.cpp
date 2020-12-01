#pragma g++ optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

int manacher(const string &s) {
    int n = s.size()*2+1;
    vector<int> v(n,'$'), ans(n);
    for(int i = 0; i < s.size(); i++) v[i*2+1] = s[i];
    int j = 0, r = 0;
    for(int i = 0; i < n; i++) {
        ans[i] = max(0, min(ans[j*2-i],r-i));
        while(i+ans[i] < n && i-ans[i] >= 0 && v[i+ans[i]]==v[i-ans[i]]) ++ans[i];
        if(i+ans[i] > r) {
            r = i+ans[i];
            j = i;
        }
    }
    int mx = 0;
    for(int i = 0; i < n; i++) mx = max(mx, ans[i]);
    return mx-1;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    string s;
    while(cin >> s) cout << manacher(s) << '\n';
}
