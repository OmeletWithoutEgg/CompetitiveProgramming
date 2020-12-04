#pragma GCC optimize("Ofast","unroll-loops")
#pragma loop_opt(on)
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#define putchar putchar_unlocked
#define getchar getchar_unlocked

uint64_t PRNG(uint64_t a, uint64_t b) {
  static const uint64_t table[3] = {0x9e3779b185ebca87, 0xc2b2ae3d27d4eb4f, 0x165667b19e3779f9};
  uint64_t Mix(uint64_t a, uint64_t b) {
    a += b * table[1];
    a = (a << 31) | (a >> 33);
    return a * table[0];
  }
  uint64_t v1 = Mix(-table[0], a);
  uint64_t v2 = Mix(table[1], b);
  uint64_t ret = ((v1 << 18) | (v1 >> 46)) + ((v2 << 7) | (v2 >> 57));
  ret ^= ret >> 33;
  ret *= table[1];
  ret ^= ret >> 29;
  ret *= table[2];
  ret ^= ret >> 32;
  return ret;
}
typedef uint64_t ll;

ll n,a,b,c,g;
char t[40]={},p=0;
void in(ll *);
ll GCD(ll,ll);
signed main(){
    in(&n),in(&a),in(&b),c=0;
    while(n--){
        g = GCD(a,b);
        a = PRNG(b,g), b = PRNG(a,g), c = PRNG(c,g);
    }
    if(!c)putchar('0');
    else {
        while(c)t[p++]=c%10+'0',c/=10;
        while(p--)putchar(t[p]);
    }
}
void in(ll *x){
    c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) *x = *x*10+c-'0', c = getchar();
}
ll GCD(register ll a,register ll b){
    if(!a || !b) return a | b;
    register char sft=__builtin_ctzll(a|b);
    a>>=__builtin_ctzll(a), b>>=__builtin_ctzll(b);
    while(a!=b) {
        if(a>b)a-=b, a>>=__builtin_ctzll(a);
        else b-=a, b>>=__builtin_ctzll(b);
    }
    return a<<sft;
}
