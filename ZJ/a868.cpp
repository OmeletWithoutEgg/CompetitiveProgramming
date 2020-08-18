#include <iostream>
#include <string>

using namespace std;

string nums[] = {"ZERO","ONE","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE","TEN","ELEVEN","TWELVE","THIRTEEN"};

int main(){
    string obj[5] = {}, s;
    uint16_t ct[5] = {};
    uint16_t i, j, t, res = 1;
    for(i = 0;i < 4;i++)
        for(j = 0;j < 5;j++){
            cin >> s;
            switch(j){
                case 3:
                    for(t = 0;t < 14;t++)if(s == nums[t])break;
                    ct[i] = t;
                    break;
                case 4:
                    obj[i] = s;
                    break;
                default:
                    ;
            }
        }
    for(i = 0;i < 3;i++)cin >> s;
    s = s.substr(0,s.length() - 1);
    for(i = 0;obj[i] != s;i++)res *= ct[i];
    cout << res * ct[i] << " " << s << endl;
    return 0;
}
