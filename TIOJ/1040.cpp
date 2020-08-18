#include <bits/stdc++.h>
#define INF (1<<20)
#define pb push_back

using namespace std;

int main(){
    vector<int> ans;
    int a,b,t,q;
    cin >> q;
    while(q--){
        cin >> a >> b;
        cout << a << '/' << b << " = ";
        ans.clear();
        while(b)ans.pb(a/b),t = a%b,a = b,b = t;
        cout << ans[0];
        for(int i = 1;i < ans.size()-1;i++)
            cout << "+1/{" << ans[i];
        if(ans.size() > 1)cout << "+1/" << *ans.rbegin();
        for(int i = 1;i < ans.size()-1;i++)
            cout << '}';
        cout << '\n';
    }
    return 0;
}

