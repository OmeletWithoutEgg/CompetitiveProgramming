#include "lib1271.h"
#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define debug(x) (cerr<<#x<<" = "<<(x)<<'\n')

using namespace std;
const int N = 1000025, K = 26;

struct Trie {
    int ch[N][K], pa[N][20], dep[N];
    int tot, head, his[N], cnt;
    int newnode(int p) {
        ++tot;
        dep[tot] = dep[p] + 1;
        pa[tot][0] = p;
        for(int i = 1; i < 20; i++) pa[tot][i] = pa[pa[tot][i-1]][i-1];
        for(int i = 0; i < K; i++) ch[tot][i] = 0;
        return tot;
    }
    int jump(int p, int k) {
        for(int i = 0; i < 20; i++) if(k>>i & 1) p = pa[p][i];
        return p;
    }
    void ins(int c) {
        if(!ch[head][c])
            ch[head][c] = newnode(head);
        head = his[cnt++] = ch[head][c];
        //debug(head);
    }
    void undo(int k) {
        head = his[cnt] = his[cnt-1-k];
        ++cnt;
    }
    int kth(int k) {
        int p = jump(head, dep[head] - k - 1);
        for(int i = 0; i < K && p; i++) if(ch[pa[p][0]][i] == p) return i;
        return -1;
    }
} T;
void Init(){
    T.head = T.tot = T.cnt = 0;
    for(int i = 0; i < K; i++) T.ch[0][i] = 0;
}
void TypeLetter(char c) {
    T.ins(c-'a');
}
void UndoCommands(int k) {
    T.undo(k);
}
char GetLetter(int k) {
    return T.kth(k) + 'a';
}
#ifdef local
signed main(){
    char cmd, c;
    int k;
    Init();
    while(cin >> cmd){
        if(cmd == 'I') Init();
        else if(cmd == 'T') cin >> c, TypeLetter(c);
        else if(cmd == 'U') cin >> k, UndoCommands(k);
        else if(cmd == 'G') cin >> k, cout << GetLetter(k) << '\n';
    }
}
#endif

/*
T i
I
T p
G 0
*/
