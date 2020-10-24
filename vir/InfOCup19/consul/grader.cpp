#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

static const int MIN_VALUE = 0, MAX_VALUE = (1e9) - 1;

static map<int,int> mp;
static int Q, N, a[5005];
static bool issol, answer;

void solve(int N);

void say_answer(int k)
{
    if(answer)
    {
        cout << "Multiple answers provided for the same testcase!\n";
        exit(0);
    }
    answer = 1;

    if(k == -1)
    {
        if(issol)
        {
            cout << "Wrong answer\n";
            exit(0);
        }
        else cout << "Correct! Number of queries: " << Q << '\n';
    }
    else
    {
        if(!issol || mp[k] <= N/3)
        {
            cout << "Wrong answer\n";
            exit(0);
        }
        else cout << "Correct! Number of queries: " << Q << '\n';
    }
}

int cnt(int k)
{
    ++Q;
    if(!(k>=MIN_VALUE && k<=MAX_VALUE))
    {
        cout << "Wrong query format\n";
        exit(0);
    }
    return mp[k];
}

int kth(int k)
{
    ++Q;
    if(!(k>=1 && k<=N))
    {
        cout << "Wrong query format\n";
        exit(0);
    }
    return a[k];
}

int main()
{
    int tests, i;
    cin >> tests;

    while(tests--)
    {
        cin >> N; mp.clear();
        Q = 0; issol = 0; answer = 0;

        for(i=1; i<=N; ++i) cin >> a[i], ++mp[a[i]];
        for(i=1; i<=N; ++i) issol |= (mp[a[i]] > N/3);
        solve(N);
    }

    return 0;
}

