#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, 20, "n");
    inf.readSpace();
    int m = inf.readInt(1, 7, "m");
    inf.readSpace();
    int k = inf.readInt(0, n*m, "k");
    inf.readEoln();
    inf.readEof();
}
