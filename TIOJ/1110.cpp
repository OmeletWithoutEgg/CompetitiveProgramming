#include <bits/stdc++.h>

using namespace std;

int q, l;
string s;
int ct[26] = {};
int main(){
    cin >> q;
    while(q--){
        cin >> l >> s;
        fill(ct,ct+26,0);
        for(int i = 0;i < s.length();i++){
            ct[s[i] - 'a']++;
        }
        int mx = 0;
        set<char> mxAp;
        for(int i = 0;i < 26;i++){
            if(ct[i] == mx)mxAp.insert('a'+i);
            else if(ct[i] > mx)mxAp.clear(),mxAp.insert('a'+i),mx = ct[i];
        }
        for(auto c:mxAp)cout << c;
        cout << '\n';
    }
}
