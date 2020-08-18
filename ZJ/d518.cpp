#include <bits/stdc++.h>
#define pb push_back
#define mkp make_pair

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int n;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> n){
        map<string,int> patt;
        string s;
        int l = 0;
        for(int i = 0;i < n;i++){
            cin >> s;
            if(patt.count(s))cout << "Old! " << patt[s] << '\n';
            else cout << "New! " << (patt[s] = ++l) << '\n';
        }
    }
    return 0;
}


