#include <bits/stdc++.h>
#define debug(x) cout << #x << ':' << (x) << '\n'
#define pb emplace_back

using namespace std;

int a[50010],n,q;
// Operation type : 0 = add, 1 = delete, 2 = query, -1 = jizz
struct Operation{
    char type;
    int args[3],ans;
    /*friend ostream& operator<<(ostream &o,Operation &x) {
        if(x.type == 0) o << "ADD " << x.args[1] << " at pos " << x.args[0];
        else if(x.type == 1) o << "DEL " << x.args[1] << " at pos " << x.args[0];
        else if(x.type == 2) o << "QRY [" << x.args[0] << ',' << x.args[1] << "] with " << x.args[2];
        else if(x.type == -1) o << "JIZ";
        else cerr<<"type="<<x.type<<"args="<<x.args[0]<<','<<x.args[1]<<','<<x.args[2]<<"id="<<x.id<<"ans="<<x.ans;
        return o;
    }*/
};
vector<int> u,v;
vector<Operation> QS;
int bit[60010] = {};
int qry(int i) {
    int res = 0;
    for(;i;i-=i&-i) res += bit[i];
    return res;
}
void add(int i) { for(;i<=n;i+=i&-i) ++bit[i]; };
void sub(int i) { for(;i<=n;i+=i&-i) --bit[i]; };
void part(vector<int> &V,vector<int> &L,vector<int> &R,int x) {
    for(auto &i:V) {
        auto &Q = QS[i];
        if(Q.type == 0) {
            if(Q.args[1]<=u[x]) add(Q.args[0]), L.pb(i);
            else R.pb(i);
        }else if(Q.type == 1){
            if(Q.args[1]<=u[x]) sub(Q.args[0]), L.pb(i);
            else R.pb(i);
        }else if(Q.type == 2) {
            int cnt = qry(Q.args[1])-qry(Q.args[0]);
            if(Q.args[2]<=cnt) L.pb(i);
            else Q.args[2]-=cnt, R.pb(i);
        }else L.pb(i);
    }
    for(auto &i:V) {
        auto &Q = QS[i];
        if(Q.type == 0 && Q.args[1]<=u[x]) sub(Q.args[0]);
        if(Q.type == 1 && Q.args[1]<=u[x]) add(Q.args[0]);
    }
    //vector<int>().swap(V);
}
void totBS(vector<int> &V,int l,int r) {
    if(V.empty() || l == r) {
        //cout << "solved!OAO\n";
        for(auto &i:V) QS[i].ans = l;
        return;
    }
    vector<int> L,R;
    int m = l+(r-l>>1);
    part(V,L,R,m);
    totBS(L,l,m); //二分搜左邊的數:答案小於m的
    totBS(R,m+1,r); //二分搜右邊的數:答案不小於m的
}
void solve(){
    //vector<Operation>().swap(QS);
    QS.clear(),u.clear();
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i], u.pb(a[i]), QS.push_back({0,i,a[i]});
    int op,l,r,k,c,x;
    for(int i = 0; i < q; i++) {
        cin >> op;
        if(op == 1) {
            cin >> l >> r >> k, --l;
            QS.push_back({2,l,r,k});
        }else if(op == 2) {
            cin >> c >> x, u.pb(x);
            QS.push_back({1,c,a[c]});
            QS.push_back({0,c,a[c]=x});
        }else if(op == 3) {
            cin >> c >> x;
            QS.push_back({-1});
        }
    }
    sort(u.begin(),u.end()),u.erase(unique(u.begin(),u.end()),u.end());
    v.resize(QS.size());
    iota(v.begin(),v.end(),0);
    totBS(v,0,u.size()-1);
    for(auto &Q:QS) {
        if(Q.type == -1) cout << 7122 << '\n';
        else if(Q.type == 2) cout << u[Q.ans] << '\n';
    }
}
signed main() {
    ios_base::sync_with_stdio(0),cin.tie(0);
    int t;
    cin >> t;
    while(t--) solve();
}
