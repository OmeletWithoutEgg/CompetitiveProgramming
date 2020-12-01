#include "testlib.h"

int g[19][19];
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, 18, "n");
    inf.readSpace();
    int m = inf.readInt(1, n*(n-1)/2, "m");
    inf.readSpace();
    int k = inf.readInt(1, 18, "k");
    inf.readEoln();
    for(int i = 0; i < m; i++) {
        int x_i = inf.readInt(1, n, "x");
        inf.readSpace();
        int y_i = inf.readInt(1, n, "y");
        inf.readEoln();
        ensure(x_i < y_i);
        ensure(g[x_i][y_i] == 0);
        g[x_i][y_i] = 1;
    }
    inf.readEof();
}
