#include "lib1044.h"
#define INF (1<<20)
#define pb push_back

using namespace std;

int main(){
    int l = 0;
    int r = Initialize();
    while(l+1 < r){
        int mid = l+(r-l>>1);
        //cout << "mid = " << mid << '\n';
        if(!Guess(mid))l = mid;
        else r = mid;
    }
    //cout << "guesses " << r << '\n';
    Report(r);
    return 0;
}


