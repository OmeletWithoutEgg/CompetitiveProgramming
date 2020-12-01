#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int n = rnd.next(1, N);
    int m = rnd.next(1, M);
    int k = rnd.next(0, n*m/2) * 2;
    cout << n << ' ' << m << ' ' << k << '\n';
}
