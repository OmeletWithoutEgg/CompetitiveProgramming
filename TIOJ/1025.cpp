#include <cstdio>

int v[9][9];
int nxt[90];
int row[9],col[9],blk[9];
int solution;
void print() {
    //for(int i = 0; i < 9; i++) if(row[i] != (1<<9)-1) return;
    //for(int i = 0; i < 9; i++) if(col[i] != (1<<9)-1) return;
    //for(int i = 0; i < 9; i++) if(blk[i] != (1<<9)-1) return;
    solution++;
    for(int i = 0; i < 9; i++) for(int j = 0; j < 9; j++) printf("%d%c", v[i][j]+1, " \n"[j==8]);
    puts("");
}
void dfs(int id) {
    if(id == 81) return print(), void();
    int i = id/9, j = id%9;
    int &R = row[i];
    int &C = col[j];
    int &B = blk[i/3*3 + j/3];
    for(int x = 0, s = 1; x < 9; x++, s<<=1) {
        if((R|B|C) & s) continue;
        R |= s, C |= s, B |= s;
        v[i][j] = x;
        dfs(nxt[id]);
        v[i][j] = -1;
        R &= ~s, C &= ~s, B &= ~s;
    }
}
signed main() {
    //ios_base::sync_with_stdio(0), cin.tie(0);
    for(int i = 0; i < 9; i++) for(int j = 0; j < 9; j++) scanf("%d", &v[i][j]), --v[i][j];
    int last = -1, head = 81;
    for(int i = 0; i < 9; i++) for(int j = 0; j < 9; j++) if(~v[i][j]) {
        row[i] |= 1<<v[i][j];
        col[j] |= 1<<v[i][j];
        blk[i/3*3 + j/3] |= 1<<v[i][j];
    }else {
        if(~last) nxt[last]=i*9+j;
        else head = i*9+j;
        last = i*9+j;
    }
    nxt[last] = 81;
    dfs(head);
    printf("there are a total of %d solution(s).", solution);
}
