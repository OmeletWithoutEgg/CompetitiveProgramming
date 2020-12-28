#include <bits/stdc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}

using namespace std;
void ensure(bool flag, string s, int code) {
    if(!flag)
        cerr << s << '\n', exit(code);
}

int perform(vector<int> cows, vector<int> seq) {
    pair<int,int> field(-1, 0);
    for(int x: seq) {
        --x;
        ensure(x >= 0 && x < cows.size() && cows[x] > 0, "PLEASE PERFORM CORRECTLY", 3);
        cows[x] -= 1;
        if(x == field.first)
            ++field.second;
        else if(field.second > 0)
            --field.second;
        else
            field = {x, 1};
        ++x;
        ++field.first;
        debug(x, field.first, field.second);
        --field.first;
    }
    return field.first == 0 ? field.second : 0;
}
signed main(int argc, char **argv) {
    ios_base::sync_with_stdio(0), cin.tie(0);
    ifstream pout(argv[1]);
    ifstream jout(argv[3]);
    ifstream tin(argv[2]);
    int n, m;
    assert(tin >> n >> m);
    vector<int> cows(m);
    for(int i = 0; i < m; i++) assert(tin >> cows[i]);
    string pok, jok;
    int pans, jans;
    vector<int> pseq(n), jseq(n);
    assert(pout >> pok);
    assert(jout >> jok);
    if(jok == "YES") {
        cerr << "JANS\n";
        assert(jout >> jans);
        debug(jans);
        for(int i = 0; i < n; i++) assert(jout >> jseq[i]);
        ensure(perform(cows, jseq) == jans, "Judge solution provides wrong sequence QAQ", 3);
    }
    if(pok == "YES") {
        cerr << "PANS\n";
        assert(pout >> pans);
        for(int i = 0; i < n; i++) assert(pout >> pseq[i]);
        ensure(perform(cows, pseq) == pans, "Your solution provides wrong sequence.", 0);
    }
    if(jok == "YES" && pok == "YES") {
        ensure(jans >= pans, "You have better answer than judge QAQ", 3);
        ensure(jans == pans, "Judge has better solution.", 0);
        ensure(jseq <= pseq, "Judge solution is not lexicographically smallest QAQ", 3);
        ensure(jseq == pseq, "Your solution is not lexicographically smallest.", 0);
    } else {
        ensure(jok != "NO", "You have solution but I don't QAQ", 3);
        ensure(jok == pok, "Judge has solution but you don't.", 0);
    }
}
