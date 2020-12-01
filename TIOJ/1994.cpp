#include <bits/stdc++.h>

using namespace std;
const int N = 1<<11;

int tab[2][N][N];
signed main(){
    int n,L = 1,d=1;
    cin >> n;
    for(int p = 1; p <= n; p++) {
        for(int i = 0; i < L; i++)
            for(int j = 0; j < L; j++)
                tab[d][i][j] = tab[!d][j][i];
        for(int i = 0; i < L; i++)
            for(int j = 0; j < L; j++)
                tab[d][L+i][j] = tab[!d][i][j]+L*L;
        for(int i = 0; i < L; i++)
            for(int j = 0; j < L; j++)
                tab[d][i][L+j] = tab[!d][L-1-j][L-1-i]+L*L*3;
        for(int i = 0; i < L; i++)
            for(int j = 0; j < L; j++)
                tab[d][L+i][L+j] = tab[!d][i][j]+L*L*2;
        L <<= 1;
        d = !d;
    }
    for(int i = 0; i < L; i++)
        for(int j = 0; j < L; j++)
            cout << tab[!d][i][j] << " \n"[j==L-1];
}
