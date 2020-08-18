#include <cstdio>

int __lg(int x){

}
int a,res;
signed main(){
    while(1){
        scanf("%d",&a);
        if(!a) return 0;
        res = 0;
        while(a) res += 1<<__lg(a), scanf("%d",&a);
        printf("%d\n",res);
    }
}
