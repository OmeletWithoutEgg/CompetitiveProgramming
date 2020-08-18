#include <bits/stdc++.h>
using namespace std;
int Pile[4] = {0,10,15,20};
void Initialize() {
    ;
}
void Take_Stone(int pile_no, int num, int *com_pile, int *com_num) {
    Pile[pile_no] -= num;
    cout << "Take " << num << " from " << pile_no << '\n';
    for(int i = 1; i <= 3; i++) cout << Pile[i] << ' '; cout << '\n';
    cin >> *com_pile >> *com_num;
    Pile[*com_pile] -= *com_num;
    cout << "Take " << *com_num << " from " << *com_pile << '\n';
    for(int i = 1; i <= 3; i++) cout << Pile[i] << ' '; cout << '\n';
}
