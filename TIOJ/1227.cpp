#include "lib1227.h"

typedef long long ll;

int ODDl,EVENl;
ll *ODD,*EVEN;//1 base,len(ODD) = (n>>1)+(n&1)

inline int lowbit(int a){return a&-a;}

void init(int n,ll d[]){
    ODDl = (n>>1) + (n&1);
    EVENl = n >> 1;
}

void change(int a,int b,ll k){
    a++,b++;
    if(a&1)modify(ODD,a>>1,-k),modify(EVEN,b>>1,k);
    else modify(EVEN,a>>1,k),modify(EVEN,b>>1,-k);
}
