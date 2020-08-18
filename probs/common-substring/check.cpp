#include <bits/stdc++.h>

using namespace std;

vector<int> buildFail(const string &P) {
    vector<int> fail(P.size());
    for(int i = 1, j = 0; i < P.size(); i++) {
        while(j && P[i] != P[j]) j = fail[j-1];
        if(P[i] == P[j]) ++j;
        fail[i] = j;
    }
    return fail;
}
int match(const string &T, const string &P, const vector<int> &fail) {
    int cnt = 0;
    for(int i = 0, j = 0; i < T.size(); i++) {
        while(j && T[i] != P[j]) j = fail[j-1];
        if(T[i] == P[j]) ++j;
        if(j == P.size()) {
            ++cnt;
            j = fail[j-1];
        }
    }
    return cnt;
}
signed main(int argc, char **argv) {
    ios_base::sync_with_stdio(0), cin.tie(0);
    ifstream pout(argv[1]);
    ifstream jout(argv[3]);
    ifstream tin(argv[2]);
    int n;
    assert(tin >> n);
    vector<string> str(n);
    for(string &s: str) assert(tin >> s);
    string pans, jans;
    assert(pout >> pans);
    assert(jout >> jans);
    if((jans == "7122") ^ (pans == "7122")) {
        cout << 1 << endl;
    } else if(jans == "7122" && pans == "7122") {
        cout << 0 << endl;
    } else {
        vector<int> fail = buildFail(pans);
        bool ok = true;
        for(string &s: str) if(match(s, pans, fail) == 0) ok = false;
        if(ok)
            cout << 0 << endl;
        else
            cout << 1 << endl;
    }
    return 0;
}
