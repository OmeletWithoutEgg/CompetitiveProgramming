#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    uint32_t n, i;
    vector<pair<int64_t,int64_t> > itrvl;
    while(cin >> n){
        for(i = 0;i < n;i++){
            int l, r;
            cin >> l >> r;
            itrvl.push_back(pair<int64_t,int64_t>(l,r));
        }
        sort(itrvl.begin(),itrvl.end());
        //for(i = 0;i < n;i++)cout << itrvl[i].first << ' ' << itrvl[i].second << endl;
    }
    return 0;
}
