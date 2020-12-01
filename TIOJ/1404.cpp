#include <bits/stdc++.h>
#define debug(x) cerr<<#x<<" = "<<x<<'\n'

using namespace std;
const int N = 100025;
signed main() {
    //ios_base::sync_with_stdio(0), cin.tie(0);
    int m, n, T;
    while(cin >> m) {
        vector<pair<int,int>> v(m);
        for(auto &[x, y]: v) cin >> x >> y;
        cin >> n >> T;
        vector<int> bulb(n);
        for(int &x: bulb) cin >> x;
        vector<pair<int,int>> seg(m, pair<int,int>(0, n));

        {
            auto better = [](pair<int,int> a, pair<int,int> b, pair<int,int> c) {
                pair<int,int> AB(b.first-a.first, b.second-a.second);
                pair<int,int> BC(c.first-b.first, c.second-b.second);
                return 1LL * AB.first * BC.second - 1LL * BC.first * AB.second > 0;
            };
            vector<pair<int,int>> stk;
            for(int i = 0; i < m; i++) {
                while(stk.size() >= 2 && better(stk[stk.size()-2], stk[stk.size()-1], v[i]))
                    stk.pop_back();
                if(stk.size() && stk.back().second > v[i].second) {
                    double x = v[i].first + (T - v[i].second) * (stk.back().first - v[i].first) / double(stk.back().second - v[i].second);
                    seg[i].first = upper_bound(bulb.begin(), bulb.end(), x) - bulb.begin();
                }
                stk.push_back(v[i]);
            }
        }

        {
            auto better = [](pair<int,int> a, pair<int,int> b, pair<int,int> c) {
                pair<int,int> AB(b.first-a.first, b.second-a.second);
                pair<int,int> BC(c.first-b.first, c.second-b.second);
                return 1LL * AB.first * BC.second - 1LL * BC.first * AB.second < 0;
            };
            vector<pair<int,int>> stk;
            for(int i = m-1; i >= 0; i--) {
                while(stk.size() >= 2 && better(stk[stk.size()-2], stk[stk.size()-1], v[i]))
                    stk.pop_back();
                if(stk.size() && stk.back().second > v[i].second) {
                    double x = v[i].first + (T - v[i].second) * (stk.back().first - v[i].first) / double(stk.back().second - v[i].second);
                    seg[i].second = lower_bound(bulb.begin(), bulb.end(), x) - bulb.begin();
                }
                stk.push_back(v[i]);
            }
        }

        bool ok = true;
        for(int i = 0; i < m; i++) if(seg[i].first == seg[i].second) {
            cout << "you need more bulbs!\n";
            ok = false;
            break;
        }
        if(!ok) continue;
        sort(seg.begin(), seg.end(), [](pair<int,int> a, pair<int,int> b){return a.second < b.second;});
        int last = -1, ans = 0;
        for(auto [l, r]: seg) {
            //cout << l << ' ' << r << '\n';
            if(l >= last) {
                last = r;
                ++ans;
            }
        }
        cout << ans << '\n';
    }
}
