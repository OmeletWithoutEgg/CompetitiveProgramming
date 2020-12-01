#include <bits/stdc++.h>
#define pb push_back
#define mkp make_pair

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int pw(int e,int p){
    int res = 1;
    while(p){
        if(p&1)res *= e;
        e *= e,p >>= 1;
    }
    return res;
}
int main(){
    int base;
    string s;
    cin >> base >> s;
    int x = 0,y = 0;
    for(auto c:s)x *= base,x += c - '0',y += pw(c - '0',s.length());
    cout << ((x == y)?"YES\n":"NO\n");
    return 0;
}
