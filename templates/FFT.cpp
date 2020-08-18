#include <bits/stdc++.h>

using namespace std;
typedef complex<long double> cd;
const long double PI = acos(-1);

void FFT(cd F[],int n,bool inv) {
    for(int i = 0, j = 0; i < n; i++) {
        if(i < j) swap(F[i],F[j]);
        for(int k = n>>1; (j^=k) < k; k>>=1);
    }
    for(int step = 1; step < n; step *= 2) {
        long double theta = inv ? PI/step : -PI/step;
        cd root(cos(theta),sin(theta));
        for(int i = 0; i < n; i += step*2) {
            cd now = 1;
            for(int j = 0; j < step; j++) {
                cd a = F[i+j];
                cd b = F[i+j+step]*now;
                F[i+j] = a+b;
                F[i+j+step] = a-b;
                now = now*root;
            }
        }
    }
    if(inv) for(int i = 0; i < n; i++) F[i]=F[i]/cd(n,0);
}

cd A[1<<20] = {1,2}, B[1<<20] = {1,2,3,5}; // (1+2x) * (1+2x+3x^2)
signed main() {
    // A*B
    int n = 1<<__lg(2+4)+1; // n = 2^k >= deg(A)+deg(B)
    FFT(A,n,0);
    FFT(B,n,0);
    for(int i = 0; i < n; i++) A[i] = A[i]*B[i];
    FFT(A,n,1);
    for(int i = 0; i < n; i++) cout << A[i].real() << ' ';
}
