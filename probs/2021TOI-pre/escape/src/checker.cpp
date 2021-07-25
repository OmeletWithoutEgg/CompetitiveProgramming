#include <iostream>
#include <fstream>
#include <climits>
#include <cassert>
#include <vector>

using namespace std;

void fail(const char *s) {
    cerr << s << endl;
    exit(0);
}
long long readInt(istream &fin, long long l=LLONG_MIN, long long r=LLONG_MAX) {
    long long x;
    if ((fin >> x) && l <= x && x <= r)
        return x;
    fail("wrong output format");
    return 7122;
}

long long strictReadInt(istream &fin, long long l=LLONG_MIN, long long r=LLONG_MAX) {
    long long x;
    assert ((fin >> x) && l <= x && x <= r);
    return x;
}

bool ok(vector<vector<int>> &a, vector<int> r, vector<int> c) {
    int n = a.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (r[i] + c[j] < a[i][j])
                return false;
    return true;
}

int main(int argc, char *argv[]) {
    assert (argc >= 4);
    ifstream pout(argv[1]);
    ifstream tin(argv[2]);
    ifstream tout(argv[3]);

    int n;
    n = strictReadInt(tin, 1, 500);
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = strictReadInt(tin, 0, 2000000);
    int provide_solution = strictReadInt(tout, 0, 1);

    long long jm;
    vector<int> jr(n), jc(n);
    jm = strictReadInt(tout);
    for (int i = 0; i < n; i++)
        jr[i] = strictReadInt(tout, 0, 2000000);
    for (int i = 0; i < n; i++)
        jc[i] = strictReadInt(tout, 0, 2000000);

    long long pm;
    vector<int> pr(n), pc(n);
    pm = readInt(pout);
    for (int i = 0; i < n; i++)
        pr[i] = readInt(pout, 0, 2000000);
    for (int i = 0; i < n; i++)
        pc[i] = readInt(pout, 0, 2000000);

    assert (ok(a, jr, jc));
    if (provide_solution == 1 && !ok(a, pr, pc))
        fail("wrong arrangement");

    assert (jm <= pm);
    if (pm == jm)
        cout << 0 << endl;
}
