#include <iostream>
#include <string>

using namespace std;

string tmp;
int n, k;
int main(){
    while(cin >> n >> k){
        for(int i = 0;i < n;i++){
            cin >> tmp;
            if(i == n-k)cout << tmp << '\n';
        }
    }
    return 0;
}
