#include <bits/stdc++.h>
#define debug(x) (cerr<<#x<<" = "<<x<<'\n')
#include "lib1087.h"
using namespace std;
int pile[3] = {10,15,20}, n = 3;
signed main() {
    //ios_base::sync_with_stdio(0), cin.tie(0);
    Initialize();
    while(accumulate(pile, pile+n, 0)) {
        int x=-1,y=-1,cx,cy;
        int cnt = count_if(pile, pile+n, [](int x){return x>1;});
        if(cnt > 1) {
            int SG = accumulate(pile, pile+n, 0, bit_xor<int>());
            for(int i = 0; i < n; i++) if(pile[i] > (pile[i] ^ SG)) {
                x = i;
                y = pile[i] - (pile[i]^SG);
                break;
            }
        }else {
            int one = count_if(pile, pile+n, [](int x){return x==1;});
            for(int i = 0; i < n; i++) if(pile[i] > 1) x = i;
            y = pile[x]-!(one&1);
        }
        Take_Stone(x+1,y,&cx,&cy);
        pile[x] -= y;
        pile[cx-1] -= cy;
    }
    return 0;
}
