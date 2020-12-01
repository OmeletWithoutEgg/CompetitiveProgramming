#include <bits/stdc++.h>
#define INF (1<<20)
#define pb push_back
#define SQ(X) ((X)*(X))

using namespace std;

int main(){
    int a[3],t;
    cin >> t;
    while(t--){
        cin >> a[0] >> a[1] >> a[2];
        if(a[0] <= 0 || a[1] <= 0 || a[2] <= 0)cout << "no\n";
        else{
            sort(a,a+3);
            if(SQ(a[0]) + SQ(a[1]) == SQ(a[2]))cout << "yes\n";
            else cout << "no\n";
        }
    }
    return 0;
}
