#include "jngen.h"
#include <iostream>
using namespace std;

template <typename ...T> string format(const char *s, T &&...args) {
    static char buf[1 << 10];
    sprintf(buf, s, args...);
    return string(buf);
}

string repeat(string s, int times) {
    string res;
    for (int i = 0; i < times; i++)
        res += s;
    return res;
}

void gen(string filename, int maxsz) {
    const int maxLen = 1000;

    int digitLength = to_string(maxsz).size();
    int parts = rnd.next(1, maxLen / (digitLength + 1));
    auto szs = Array::random(parts, 1, maxsz);
    auto dif = Array::random(parts-1, 1, 25);
    char ch = rnd.next('a', 'z');

    int orgLen = 0;
    string s;
    for (int i = 0; i < parts; i++) {
        if (szs[i] != 1)
            s += to_string(szs[i]);
        s += ch;
        if (i + 1 != parts)
            ch = ((ch - 'a') + dif[i]) % 26 + 'a';
        orgLen += szs[i];
    }

    ofstream fout(filename);
    fout << s << '\n';
    // cerr << orgLen << ' ' << s.size() << ' ' << parts << '\n';
}

void handMade(string filename, string s) {
    ofstream(filename) << s << '\n';
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    string prefix = getOpt("o");

    for(int i = 0; i < 8; i++)
        gen(prefix + format("%02d.in", i), 9);
    handMade(prefix + "08.in", "aquickbrownfoxjumpsoverthelazydog");
    handMade(prefix + "09.in", repeat("9k9c", 250));
    for(int i = 10; i < 30; i++)
        gen(prefix + format("%02d.in", i), 100);
    handMade(prefix + "15.in", repeat("abcdefghijklmnopqrstuvwxyz", 10));
    handMade(prefix + "25.in", repeat("100x100v", 125));
    handMade(prefix + "29.in", repeat("99h99a", 166) + "99k");
}
