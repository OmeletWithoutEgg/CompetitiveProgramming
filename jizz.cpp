#include <bits/stdc++.h>
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#define all(v) begin(v),end(v)

using namespace std;
const int maxn = 2000;

int n, type;
bool has[maxn];
bitset<maxn> bs[maxn];
bool insert(bitset<maxn> b) {
    for(int i = n-1; i >= 0; i--) if(b[i]) {
        if(has[i]) {
            b ^= bs[i];
        } else {
            bs[i] = b;
            has[i] = true;
            return true;
        }
    }
    return false;
}
int addBit(bitset<maxn> b) {
    for(int i = n-1; i >= 0; i--) if(!has[i]) {
        b[i] = !b[i];
        assert( insert(b) );
        return i;
    }
    abort();
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> type;
    vector<bool> isBasis(n);
    vector<string> ans(n);
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        ans[i] = s;
        if(insert(bitset<maxn>(s))) {
            isBasis[i] = true;
        }
    }
    if (n == 1 && type == 2)
        return cout << ans[0] << '\n', 0;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(!isBasis[i]) {
            int pos = addBit(bitset<maxn>(ans[i]));
            ans[i][n-1-pos] ^= 1;
            ++cnt;
        }
    }
    if(type == 1)
        cout << cnt << '\n';
    else if(type == 2)
        for(int i = 0; i < n; i++)
            cout << ans[i] << '\n';
}
