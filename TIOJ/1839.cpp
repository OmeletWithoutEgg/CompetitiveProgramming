#ifndef local
#include "lib1839.h"
#else
#include <iostream>
#include <vector>
#define debug(x) cerr<<#x<<" = "<<(x)<<'\n'
using namespace std;

int N, realS[5025], realD[5025];
int cnt;
int tryCombination(const int S[]) {
    ++cnt;
    vector<int> on(N);
    for(int i = 0; i < N; i++) on[realD[i]] = S[i] == realS[i];
    for(int i = 0; i < N; i++) if(!on[i]) return i;
    return -1;
}
void answer(int S[], int D[]) {
    debug(cnt);
    for(int i = 0; i < N; i++) cout << S[i] << (i+1==N ? '\n' : ' ');
    for(int i = 0; i < N; i++) cout << D[i] << (i+1==N ? '\n' : ' ');
}
#include <random>
#include <algorithm>
mt19937 rng(7122);
int Initialize() {
    cnt = 0;
    cin >> N;
    for(int i = 0; i < N; i++) cin >> realS[i];
    for(int i = 0; i < N; i++) cin >> realD[i];
    /* for(int i = 0; i < N; i++) realS[i] = rng() & 1; */
    /* iota(realD, realD+N, 0); */
    /* shuffle(realD, realD+N, rng); */
    return N;
}
#endif // local
int D[5025], S[5025];
int on[5025];
int n;
int checkPrefix(int x) {
    for(int i = 0; i < n; i++) {
        if(D[i] == -1)
            on[i] = S[i] ^ (i < x);
        else
            on[i] = S[i];
    }
    return tryCombination(on);
}
void toggle(int x) {
    for(int i = 0; i < x; i++) if(D[i] == -1) S[i] ^= 1;
}
void solve(int _n) {
    n = _n;
    for(int i = 0; i < n; i++) D[i] = -1, S[i] = on[i] = 0;
    for(int now = 0; now < n; now++) {
        if(checkPrefix(n) == now) toggle(n);
        int x = 0;
        for(int s = 1<<15; s; s>>=1) if(x+s < n && checkPrefix(x+s) == now) x += s;
        toggle(x+1);
        D[x] = now;
    }
    answer(S, D);
}

signed main() {
    while(n = Initialize()) {
        solve(n);
    }
}
