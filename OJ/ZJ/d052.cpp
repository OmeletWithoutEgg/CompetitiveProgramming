#include <bits/stdc++.h>

using namespace std;

int main(){
    int n, t = 0;
    int w[2001] = {};
    int lis[2001] = {};
    cin >> t;
    for(int l = 0;l < t;l++){
        cin >> n;
        for(int i = 0;i < n;i++)cin >> w[i];

        fill(lis,lis + n,INT_MAX);
        for(int i = 0;i < n;i++)*lower_bound(lis,lis + n,w[i]) = w[i];
        cout << (lower_bound(lis,lis + n,INT_MAX) - lis) << endl;

        //for(int i = 0;i < n && lis[i] < INT_MAX;i++)cout << lis[i] << ' ';

    }
}
