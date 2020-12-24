#include<bits/stdc++.h> 
#define LL long long 
#define int LL
using namespace std; 
LL N,M;
LL arr[105],T=0,sum;
bool vis[105]; 
bool cmp(int a,int b){ 
    return a>b; 
} 
bool dfs(int n,int num,int t){ 
    T++; 
    if(t==N)return 1; 
    for(int i=n;i<M;i++){ 
        if(vis[i])continue; 
        vis[i]=1; 
        if(num+arr[i]==sum){ 
            if(dfs(0,0,t+1))return 1; 
        } 
        else if(num+arr[i]<sum){ 
            if(dfs(i+1,num+arr[i],t))return 1; 
        }  
        vis[i]=0; 
    } 
    return 0; 
} 
signed main(){ 
    ios::sync_with_stdio(0); 
    cin>>N>>M; 
    sum=0; 
    for(int i=0;i<M;i++){ 
        cin>>arr[i]; 
        sum+=arr[i];  
    } 
    sort(arr,arr+M,cmp); 
    cerr<<arr[0]<<'\n';
    if(arr[0]*N>sum || sum%N!=0)cout<<"no QQ\n";
    else {
        sum /= N;
        if(dfs(0,0,0))cout<<"yes\n"; 
        else cout<<"no\n"; 
        cerr<<T<<'\n';
    }
    return 0; 
} 
