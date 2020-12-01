#include <iostream>
#include <string>

using namespace std;

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    uint32_t l = s.length();
    for(int i = 0;i < l;i++,cout << endl)
        for(int j = 0;j < l;j++)
            cout << s[(i + j) % l];
    return 0;
}
