#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename H, typename ...T> void qqbx(const char *s, const H&h, T&&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)
using namespace std;
const int N = 1025;

int n, m, q;
int C[N][N], ok[N][N];
int ap[N][N];
int a[N*N], b[N*N];
bool DP() {
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) ok[i][j] = false;
    ok[0][0] = true;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        if(i) ok[i][j] |= ok[i-1][j];
        if(j) ok[i][j] |= ok[i][j-1];
        if(C[i][j]) ok[i][j] = false;
    }
    return ok[n-1][m-1];
}
bool canAddTo(int l, int r) {
    for(int i = l; i < r; i++) if(!ap[a[i]][b[i]]) C[a[i]][b[i]] += 1;
    bool res = DP();
    for(int i = l; i < r; i++) if(!ap[a[i]][b[i]]) C[a[i]][b[i]] -= 1;
    return res;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> C[i][j];
    cin >> q;
    for(int i = 0; i < q; i++) cin >> a[i] >> b[i], --a[i], --b[i];
    int now = 0;
    while(now < q) {
        if(ap[a[now]][b[now]]) {
            cout << 0 << '\n';
            ++now;
            continue;
        }
        int x = now;
        for(int s = 1<<__lg(q); s; s>>=1) if(x+s <= q && canAddTo(now, x+s)) x += s;
        for(int i = now; i < x; i++) cout << ap[a[i]][b[i]] << '\n';
        for(int i = now; i < x; i++) if(!ap[a[i]][b[i]]) C[a[i]][b[i]] += 1;
        ap[a[x]][b[x]] = true;
        now = x;
    }
}
