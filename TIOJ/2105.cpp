#include <bits/stdc++.h>
#define ints long long

using namespace std;

int M = 4353;
int x = 27;

int h[10005], xp[10005];

void Hash(string& s) {
    h[s.length()] = 0;
    for(int i = s.length()-1 ; i >= 0 ; i--) {
        h[i] = (h[i+1]*x%M + s[i]-'a'+1)%M;
    }
}

int gethashvalue(int L, int len) {
    return (h[L] - h[L+len]*xp[len]%M + M)%M;
}

int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    xp[0] = 1;
    for(int i = 1 ; i < 10005 ; i++) xp[i] = xp[i-1]*x%M;

    int t, q; cin >> t;
    while(t--) {
        string s, p; cin >> s;
        Hash(s);
        cin >> q;
        while(q--) {
            cin >> p;
            int ph = 0;
            for(int i = p.length()-1 ; i >= 0 ; i--) {
                ph = (ph*x%M + p[i]-'a'+1)%M;
            }
            int cnt = 0;
            for(int i = 0 ; i+p.length()-1 < s.length() ; i++) {
                if(gethashvalue(i, p.length()) == ph) cnt++;
            }
            cout << cnt << '\n';
        }
    }
}
