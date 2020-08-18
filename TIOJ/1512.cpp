#include <bits/stdc++.h>
using namespace std;
const long long N = 50025;

int n;
pair<int,int> v[N];
void t2(vector<int> &v) {
    for(int &x: v) x *= 2;
    v.push_back(0);
    for(int i = 0; i+1 < v.size(); i++) if(v[i] >= 10) {
        ++v[i+1];
        v[i] -= 10;
    }
    if(v.back() == 0) v.pop_back();
}
string pw(int x) {
    vector<int> v{1};
    while(x--) t2(v);
    reverse(v.begin(), v.end());
    string res;
    for(int x: v) res += char(x^'0');
    return res;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        double x;
        cin >> x;
        v[i] = {x, i+1};
    }
    sort(v, v+n);
    vector<int> fr, ba;
    int now = v[n-1].second;
    for(int i = n-2; i >= 0; i--) {
        if(v[i].second < now) {
            now = v[i].second;
            fr.push_back(v[i].second);
        } else {
            ba.push_back(v[i].second);
        }
    }
    cout << pw(n-1) << '\n';
    reverse(fr.begin(), fr.end());
    for(int x: fr) cout << x << '\n';
    cout << v[n-1].second << '\n';
    for(int x: ba) cout << x << '\n';
}
