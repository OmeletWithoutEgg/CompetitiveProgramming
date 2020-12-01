#include <iostream>

#include <algorithm>
#include <string>

using namespace std;

inline int LCSlen(string &,string &);
inline bool similar(string &a,string &b){
    return (LCSlen(a,b) >= (min(a.length(),b.length()) / 2.0));
}
inline int findBiggestBlock(int [][51],int);
int visit(int [][51],int,bool [],int);

int main(){
    int t, n;
    //string s1("BEN"),s2("BENS");
    //cout << LCSlen(s1,s2) << endl;
    cin >> t;
    while(t--){
        string names[51] = {};
        bool sim[51][51] = {};
        cin >> n;
        for(int i = 0;i < n;i++)cin >> names[i];
        for(int i = 0;i < n;i++)
            for(int j = i;j < n;j++)
                if(i != j)sim[i][j] = sim[j][i] = similar(names[i],names[j])\
                    ,cout << names[i] << " & " << names[j] << (sim[i][j]?" are similar":" aren't similar") << endl;
        for(int i = 0;i < n;i++,cout << endl)
            for(int j = 0;j < n;j++)
                cout << sim[i][j] << ' ';
        //cout << findBiggestBlock(sim,n) << endl;

    }
    return 0;
}

inline int LCSlen(string &a,string &b){
    /*
    return
    (la <= 0 || lb <= 0)
        ?0
        :(a[la - 1] == b[lb - 1])
            ?LCSlen(a,b,la - 1,lb - 1) + 1
            :max(LCSlen(a,b,la,lb - 1) , LCSlen(a,b,la - 1,lb));*/

    int DP[51][51] = {}, i, j;
    for(i = 1;i <= a.length();i++)
        for(j = 1;j <= b.length();j++){
            (a[i - 1] == b[j - 1])
                ?DP[i][j] = DP[i - 1][j - 1] + 1
                :DP[i][j] = max(DP[i - 1][j],DP[i][j - 1]);
            }
    return DP[i - 1][j - 1];
}

inline int findBiggestBlock(int g[][51],int tot_s){
    bool visited[51] = {};
    int max_s = -1, cur_s;
    for(int i = 0;i < tot_s;i++){
        if(visited[i])continue;
        cur_s = visit(g,i,visited,tot_s);
        max_s = max(max_s,cur_s);
    }
    return max_s;
}
int visit(int g[][51],int p,bool vstd[],int s){
    int r = 0;
    for(int i = 0;i < s;i++)
        if(!vstd[i]){
            r++,vstd[i] = 1;
            if(g[p][i])visit(g,i,vstd,s);
        }
    return r;
}



