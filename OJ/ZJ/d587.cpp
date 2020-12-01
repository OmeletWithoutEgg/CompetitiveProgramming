#include <iostream>
#define REP(X) for(int i = 0;i < X;i++)

using namespace std;

int main(){
    int ct[3] = {}, n;
    cin >> n;
    while(cin >> n)ct[n % 3]++;
    REP(ct[1])cout << "1 ";
    REP(ct[2])cout << "2 ";
    REP(ct[0])cout << "3 ";
    cout << endl;
    return 0;
}
