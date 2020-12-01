#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
typedef long long ll;

int t,cnt[5];
string s;
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> t;
    while(t--) {
        for(int i = 0; i < 5; i++) cnt[i] = false;
        for(int i = 0; i < 12; i++) {
            cin >> s;
            for(auto &c:s) switch(c) {
                case 'R': cnt[0] = true; break;
                case 'G': cnt[1] = true; break;
                case 'B': cnt[2] = true; break;
                case 'Y': cnt[3] = true; break;
                case 'P': cnt[4] = true; break;
            }
        }
        cout << accumulate(cnt,cnt+5,0) << '\n';
    }
}
