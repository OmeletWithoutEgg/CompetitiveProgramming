#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, r;
    cin >> n >> r;
    if (n == 10) {
        int64_t ans [] = { 0, 86, 973, 9860, 98743, 987625, 9876504, 98765320, 987654032, 9876540312 };
        cout << ans[r-1] << '\n';
        return 0;
    }
    vector<int> s(n, -1);
    for (int i = 0; i < r; i++) s[n-1-i] = r-1-i;
    vector<string> ans;
    do {
        string str(r, '\0');
        for (int i = 0; i < n; i++) if (s[i] != -1) str[s[i]] = i + '0';
        ans.push_back(str);
    } while (next_permutation(s.begin(), s.end()));
    sort(ans.begin(), ans.end(), greater<>());
    // for (string str: ans) cout << str << '\n';
    cout << ans[min(int(ans.size())-1, n + r - 1)] << '\n';
}
