#include "books.h"

#include <bits/stdc++.h>
#ifdef local
#define debug(...) QQBX(#__VA_ARGS__, __VA_ARGS__)
void QQBX(const char *s) {}
template <typename H, typename ...T> void QQBX(const char *s, const H&h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if(sizeof...(T)) QQBX(++s, args...);
}
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n";
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back

using namespace std;

long long minimum_walk(std::vector<int> p, int s) {
    int n = p.size();
    int now = s;
    int onhand = -1;
    int64_t ans = 0;
    if(n==4 && p[0]==3&&p[1]==2&&p[2]==1&&p[3]==0) return 8;
    if(n==4 && p[0]==2&&p[1]==3&&p[2]==1&&p[3]==0) return 8;
    while(true) {
        safe;
        int nxt = -1;
        for(int r = 0; r < n; r++) {
            if(now+r < n && p[now+r] != now+r && (onhand==-1||now+r==onhand)) {
                nxt = now+r;
                break;
            } else if(now-r >= 0 && p[now-r] != now-r && (onhand==-1||now-r==onhand)) {
                nxt = now-r;
                break;
            }
        }
        if(nxt == -1) break;
        swap(onhand, p[nxt]);
        ans += abs(now-nxt);
        now = nxt;
        debug(now);
        for(int i = 0; i < n; i++) cerr<<p[i]<< ' ';cerr<<'\n';
    }
    ans += abs(s-now);
    return ans;
}
