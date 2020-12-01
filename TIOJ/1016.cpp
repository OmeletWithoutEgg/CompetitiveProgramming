#include <bits/stdc++.h>
#define mem(v,x) memset(v,x,sizeof v)

using namespace std;

string s;
void solve() {
    int score[2] = {}, out = 0, att = 0;
    int player[9] = {};
    for(char c:s) {
        if(c == 'O' || c == 'K') out++;
        else if(c == 'W') { // Walk
            for(int i = 0; i < 9; i++) if(player[i] == 0) {
                player[i] = 1;
                break;
            }
        }else {
            int step = (c=='S') ? 1 : (c=='D') ? 2 : (c=='T') ? 3 : (c=='H') ? 4 : (assert(0),0);
            for(int i = 8; i >= step; i--) if(player[i-step]) player[i] = 1, player[i-step] = 0;
            player[step-1] = 1;
        }
        for(int i = 3; i < 9; i++) if(player[i]) score[att]++, player[i] = 0;
        if(out == 3) att = !att, out = 0, mem(player,0);
    }
    cout << score[0] << ' ' << score[1] << '\n';
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    while(cin >> s) solve();
}
