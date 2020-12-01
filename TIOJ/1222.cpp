#include <bits/stdc++.h>

using namespace std;

void preprocess(string s, vector<int> &res) {
    int n = s.size();
    for(int i = 0; i < n; i++) {
        if(s[i] == '_') {
            res[i] += 1;
        } else if(s[i] == '#') {
            combo[i] += 1;
            while(i < n && s[i] == '#') {
                ++i;
            }
        }
    }
    return res;
}
void DP() {
    for(int i = 0; i < n; i++) {
        ;
    }
}
signed main() {
    freopen("djmax.in", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        string v[6];
        for(int i = 0; i < n; i++) {
            string sp;
            cin >> sp;
            for(int j = 0; j < 16; j++) {
                string s;
                getline(cin, s);
                for(int c = 0; c < 6; c++) v[c] += s[c];
            }
        }
        vector<int> combo(n*16);
        for(int i = 0; i < 6; i++) preprocess(v[i], combo);
        DP(combo);
    }
}
