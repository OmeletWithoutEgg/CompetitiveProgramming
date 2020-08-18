#pragma gcc optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
//#define getchar getchar_unlocked
#define N 1000025

int bit[N],n,q,v[N],s[N],k,a,b;
int ans[N],p,top;
char stk[N*10]={};
inline void getInt(int &x){
    x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9') x = x*10+c-'0', c = getchar();
}
inline void build(){
    for(register int i=1;i<=n;i++){
        bit[i] ^= s[i];
        int j = i+(i&-i);
        if(j<=n) s[j] ^= s[i];
    }
}
inline void add(register int i,int d){for(;i<=n;i+=i&-i)bit[i]^=d;}
inline int qry(register int i){int res=0;for(;i;i-=i&-i)res^=bit[i];return res;}
signed main(){
    getInt(n),getInt(q);
    for(register int i=1;i<=n;i++) getInt(v[i]), s[i]=v[i];
    build();
    for(register int i=1;i<=q;i++){
        getInt(k),getInt(a),getInt(b);
        if(k) add(a,v[a]^b),v[a]=b;
        else ans[p++] = qry(b)^qry(a-1);
    }
    while(p--) {
        stk[top++] = '\n';
        if(!ans[p]) stk[top++] = '0';
        while(ans[p]) stk[top++] = ans[p]%10+'0', ans[p]/=10;
    }
    while(top--) putchar(stk[top]);
}
