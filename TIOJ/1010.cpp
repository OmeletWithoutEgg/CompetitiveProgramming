#include <bits/stdc++.h>

using namespace std;

int main(){
    string p, q;
    cin >> p >> q;
    for(int i = 0;i < q.length();i++){
        bool match = true;
        for(int j = 0;i+j < q.length();j++){
            if(j >= p.length() || p[j] != q[i+j]){match = false;break;}
        }
        if(match){cout << q.length()-i << '\n';return 0;}
    }
    cout << 0 << '\n';
    return 0;
}
