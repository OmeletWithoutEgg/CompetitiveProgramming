
#include <bits/stdc++.h>
#define pb push_back
#define mkp make_pair

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int l = 0,i,j;
ll cur;
ll a[100001] = {};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> cur){
        if(l < 100000)l++;
        i = lower_bound(a,a+l,cur) - a;//a[i] >= cur
        for(j = l-1;j > i;j--)a[j] = a[j-1];
        a[j] = cur;
        //for(i = 0;i < l;i++)cout << a[i] << ' ';
        //cout << '\n';
        if(l&1)cout << a[l>>1] << '\n';
        else cout << ((a[l>>1]+a[(l>>1)-1])>>1) << '\n';
    }
    return 0;
}

