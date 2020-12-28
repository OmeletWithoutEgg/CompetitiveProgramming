#pragma GCC optimize("Ofast")
#pragma GCC optimize("popcnt")
#include <cstdio>
#include <cstdint>
#include <cctype>
#define ctz __builtin_ctzll
//#define putchar putchar_unlocked
//#define getchar getchar_unlocked

uint64_t PRNG(uint64_t a, uint64_t b) {
  static const uint64_t table[3] = {0x9e3779b185ebca87, 0xc2b2ae3d27d4eb4f, 0x165667b19e3779f9};
  auto Mix = [](uint64_t a, uint64_t b) {
    a += b * table[1];
    a = (a << 31) | (a >> 33);
    return a * table[0];
  };
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

using namespace std;
typedef uint64_t ll;

inline void input(ll &x){
    x = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x*10+c-'0', c = getchar();
}
inline ll gcd(register ll a,register ll b){
    if(!a || !b) return a | b;
    register int s = ctz(a|b);
    a >>= s, b >>= s;
    while(a != b) {
        a >>= ctz(a);
        b >>= ctz(b);
        if(a > b) a -= b;
        else if(a < b) b -= a;
        else return a << s;
    }
    return a << s;
}
ll c = 0;
char t[40]={},p=0;
ll n,a,b,g;
signed main(){
    input(n), input(a), input(b);
    while(n--){
        g = gcd(a,b);
        a = PRNG(b,g), b = PRNG(a,g), c = PRNG(c,g);
    }
    if(!c)putchar('0');
    else {
        while(c) t[p++]=c%10^'0' ,c/=10;
        while(p) putchar(t[--p]);
    }
}
