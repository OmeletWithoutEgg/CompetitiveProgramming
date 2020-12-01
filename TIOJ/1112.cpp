#include <iostream>
#include <string>

using namespace std;

bitset<101> patt[101][101];
bitset<101> test[101];
int q, k;
char c;
int main(){
    cin >> q;
    while(q--){
        cin >> k;
        for(int i = 0;i < k;i++)
            for(int j = 0;j < k;j++){
                cin >> c;
                if(c == 'N')test[i][j] = true;
                else if(c == '.')test[i][j] = false;
            }
        for(int i = 0;i < n;i++)
            for(int i = 0;i < n;i++){
            if(match(patt[i],test))//«İ½s¼g
        }
    }
    return 0;
}

