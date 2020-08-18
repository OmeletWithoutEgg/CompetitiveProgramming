#include <bits/stdc++.h>
#define pb push_back
#define mkp make_pair

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

inline int abs(int a){return a>=0 ? a : -a;}
int main(){
    string s;
    vector<int> v;
    int sum;
    while(cin >> s){
        sum = 0;
        v.clear();
        for(int i = 0;i < s.length();i++)if(s[i] == 'y')v.pb(i);
        for(int i = 0;i < v.size();i++)sum += abs(v[i] - i - (i<<1));
        cout << sum << '\n';
    }
    return 0;
}

