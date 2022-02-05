#include <bits/stdc++.h>
#include "testlib.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readSpace();
    int C = inf.readInt(1, 30, "C");
    inf.readEoln();
    for (int i = 0; i < n; i++) {
        int ai = inf.readInt(0, (1<<C)-1);
        if (i+1 != n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }
    for (int i = 0; i < q; i++) {
        int t = inf.readInt(1, 2);
        inf.readSpace();
        if (t == 1) {
            int l = inf.readInt(1, n);
            inf.readSpace();
            int r = inf.readInt(1, n);
            ensure(l <= r);
        } else {
            int p = inf.readInt(1, n);
            inf.readSpace();
            int x = inf.readInt(0, (1<<C)-1);
        }
        inf.readEoln();
    }
    inf.readEof();
}
