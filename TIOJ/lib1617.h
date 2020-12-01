#include <bits/stdc++.h>

using namespace std;

int N,arr[1500];
int Get_Box(){return cin >> N, iota(arr+1,arr+N+1,1), random_shuffle(arr+1,arr+N+1), N;}
int Med3(int x,int y,int z){
    for(int i = 1;i <= N;i++) cout << arr[i] << " \n"[i==N];
    int a = arr[x], b = arr[y], c = arr[z];
    if((a-b)*(a-c)<=0) return x;
    if((b-c)*(b-a)<=0) return y;
    if((c-a)*(c-b)<=0) return z;
    assert(false);
}
void Report(int x){
    cout << x << '\n';
    cout << arr[x] << '\n';
    if(arr[x] == N/2+1) cout << "AC\n";
    else cout << "WA\n";
}
