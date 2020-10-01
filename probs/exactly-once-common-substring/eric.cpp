#include<bits/stdc++.h>
#define ll long long
using namespace std;
string str;
vector<int> all;
int from[500009];
int SA[500009];
int lcp[500009];
int rnk[500009];
int nrnk[500009];
int cnt[500009];
int mc[500009];
int g;
bool cmp(int i,int j)
{
    if(rnk[i] != rnk[j])
        return rnk[i] < rnk[j];
    i += g;
    j += g;
    if(i < all.size() && j < all.size())
        return rnk[i] < rnk[j];
    return i > j;
}
vector<int> temp;
void build_SA(vector<int> A)
{
    int N = A.size();
    int i,j;

    for(i = 0;i < N;i++)
    {
        rnk[i] = A[i];
        SA[i] = i;
    }
    sort(SA,SA+N,cmp);
    for(g = 1;;g *= 2)
    {
        temp.clear();
        for(i = N-g;i < N;i++)
        {
            temp.push_back(i);
        }
        for(i = 0;i < N;i++)
        {
            if(SA[i] >= g)
                temp.push_back(SA[i]-g);
        }

        for(i = 0;i < 250000;i++)
        {
            cnt[i] = 0;
        }
        for(i = 0;i < N;i++)
            cnt[rnk[i]]++;
        for(i = 1;i < 250000;i++)
            cnt[i] += cnt[i-1];
        for(i = N-1;i >= 0;i--)
        {
            SA[--cnt[rnk[temp[i]]]] = temp[i];
        }
        nrnk[SA[0]] = 0;
        for(i = 1;i < N;i++)
        {
            nrnk[SA[i]] = nrnk[SA[i-1]];
            if(cmp(SA[i-1],SA[i]))
                nrnk[SA[i]]++;
        }
        for(i = 0;i < N;i++)
        {
            rnk[i] = nrnk[i];
        }
        if(rnk[SA[N-1]] == N-1) break;
    }
    int now = 0;
    for(i = 0;i < N;i++)
    {
        if(rnk[i] == N-1)
        {
            now = 0;
            continue;
        }
        while(now + i < N && now+SA[rnk[i]+1] < N && A[now+i] == A[now+SA[rnk[i]+1]]) now++;
        lcp[rnk[i]] = now;
        if(now > 0) now--;
    }

}
multiset<int> st;
int main()
{
    int N,M,i,j,k;
    cin >> N;
    if(N == 1)
    {
        cin >> str;
        cout << str <<endl;
        return 0;
    }
    all.clear();
    for(i = 0;i < N;i++)
    {
        cin >> str;
        for(j = 0;j < str.size();j++)
        {
            from[all.size()] = i;
            all.push_back(str[j] - 'a');
        }
        from[all.size()] = N;
        all.push_back(26 + i);

    }

    build_SA(all);
    /*for(i = 0;i < all.size();i++)
    {
        cout << SA[i] << " ";
    }
    cout << endl;*/
    int r = 0,h = 1,al = 0,as = 0;
    mc[from[SA[0]]] = 1;
    while(r < N-1)
    {
        st.insert(lcp[r]);
        r++;
        if(mc[from[SA[r]]] == 0)
        {
            h++;
        }
        mc[from[SA[r]]] ++;
    }
    for(i = 0;i + N -1 < all.size();i++)
    {
        int tp = (*st.begin());
        //cout << i << " " << r << " " << h <<" " <<tp << endl;
        if(h == N && (i == 0 || lcp[i-1] < tp) && (r == all.size()-1 || lcp[r] < tp) && tp > 0)
        {
            as = SA[i];
            al = tp;
            break;
        }

        st.erase(st.find(lcp[i]));
        mc[from[SA[i]]]--;
        if(mc[from[SA[i]]] == 0)
        {
             h--;
             //cout << "one" << endl;
        }
        st.insert(lcp[r]);
        r++;
        if(from[SA[r]] == N) break;
        mc[from[SA[r]]]++;
        if(mc[from[SA[r]]] == 1)
        {
            h++;
            //cout << "two" <<endl;
        }
    }
    if(al == 0)
        cout << 7122 << endl;
    else
    {
        for(i = as;i < as + al;i++)
        {
            cout << char(all[i] + 'a');
        }
        cout << endl;
    }
}
