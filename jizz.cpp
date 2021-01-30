#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local

using namespace std;
const int N = 200025, inf = 1e9;
const int64_t INF = 1e18;


ostream & operator<<(ostream &O, vector<int> v) {
    int f = 0;
    O << "[";
    for(int x: v)
        O << (f++ ? ", " : "") << x;
    return O << "]";
}

vector<int> getZ(string s) {
    vector<int> Z(s.size());
    Z[0] = s.size();
    for(int i = 1, j = 0, r = 0; i < s.size(); i++) {
        Z[i] = max(min(Z[i-j], r-i), 0);
        while(i+Z[i] < s.size() && s[Z[i]] == s[i+Z[i]])
            ++Z[i], j = i, r = i+Z[i];
    }
    return Z;
}
vector<int> getKMP(string s) {
    vector<int> fail(s.size());
    fail[0] = -1;
    for(int i = 1, j = -1; i < s.size(); i++) {
        while(j != -1 && s[j+1] != s[i]) j = fail[j];
        if(s[j+1] == s[i]) ++j;
        fail[i] = j;
    }
    return fail;
}
vector<int> recover(vector<int> fail) {
    int n = fail.size();
    vector<int> Z(n);
    Z[0] = n;
    for(int i = 1; i < n; i++) {
        if(fail[i] != -1)
            Z[i-fail[i]] = max(Z[i-fail[i]], fail[i]+1);
    }
    for(int i = 1; i < n; i++) {
        int j = i-fail[i];
        if(i-j>=0)
            Z[i] = max(Z[i], min(Z[i-j], j+Z[j]-i));
    }
    return Z;
    for(int i = 1, j = 0, r = 0; i < n; i++) {
        Z[i] = max(Z[i], min(Z[i-j], r-i));
        if(i+Z[i] > r) {
            j = i;
            r = i+Z[i];
        }
    }
    return Z;
}
random_device rd;
mt19937 rng(rd());
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    string s;
    s = "cccbcccc";
    debug(s);
    debug(getKMP(s));
    debug(getZ(s));
    debug(recover(getKMP(s)));
    assert(recover(getKMP(s)) == getZ(s));
    /*
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> fail(n);
        for(int i = 0; i < n; i++) cin >> fail[i];
        vector<int> Z = recover(fail);
        for(int i = 0; i < n; i++)
            cout << Z[i] << (i+1==n ? '\n' : ' ');
    }
    */
}
