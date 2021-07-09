#ifndef local
#include "transportations.h"
#else
#include "Azer.h"
#include "Baijan.h"
#endif // local

#include <bits/stdc++.h>

#ifdef local
template <typename ...T> void debug(T ...a) {
    ((std::cerr << a << ", ") , ... , (std::cerr << "\n"));
}
#else
#define debug(...) ((void)0)
#endif // local

using namespace std;
const int maxn = 2005;
const int inf = 1e9;
const int PHASE1 = 9, PHASE2 = 11;
const int MAX_CALL = 58000;


struct Solver {

    vector<pair<int,int>> g[maxn];
    int64_t dis[maxn];
    bool vis[maxn];


    void sendInt(int x, int lg) {
        debug(name, "want to sendInt", x, lg);
        for (int i = lg-1; i >= 0; i--)
            sendBit(x >> i & 1);
    }

    int N;
    int mymn, mydist;
    int last;
    void relax(int i) {
        last = i;
        vis[i] = true;
        for (auto [j, c]: g[i]) {
            if (dis[j] > dis[i] + c)
                dis[j] = dis[i] + c;
        }
        mymn = N, mydist = inf;
        for (int i = 0; i < N; i++) if (!vis[i] && dis[i] < mydist) mymn = i, mydist = dis[i];
    }

    void init(int _N, int M, vector<int> U, vector<int> V, vector<int> C) {
        N = _N;
        for (int i = 0; i < M; i++) {
            g[U[i]].emplace_back(V[i], C[i]);
            g[V[i]].emplace_back(U[i], C[i]);
            // debug(name+"::C[i]", C[i]);
        }
        fill(dis, dis+N+1, inf);
        dis[0] = 0;
        relax(0);
        // debug(name+"::mymn", mymn, dis[mymn]);
        if (mydist != inf)
            sendInt(mydist, PHASE1);
        else
            sendInt(505, PHASE1);
    }

    int cnt = 0;
    int yourdist = 0, yourmn = 0;
    int phase = 0;
    void receive(bool f) {

        const auto init = [&]{
            cnt = yourdist = yourmn = phase = 0;
        };
        if (cnt < PHASE1) {
            yourdist = yourdist * 2 + f;
            if (cnt + 1 < PHASE1) return ++cnt, void();
        }
        if (phase == 0) {
            debug("cnt", cnt);
            debug(name, "received dist", yourdist);
            if (yourdist > 500) {
                yourdist = inf;
            } else {
                yourdist += dis[last];
            }
            ++phase;
            debug("dist = ", yourdist, mydist);
        }
        if (yourdist == inf && mydist == inf)
            return;
        if (yourdist < mydist || (yourdist == mydist && name == "B")) {
            if (PHASE1 <= cnt && cnt < PHASE1 + PHASE2) {
                yourmn = yourmn * 2 + f;
                if (cnt + 1 < PHASE1 + PHASE2) return ++cnt, void();
            } else if (cnt == PHASE1 - 1)
                return ++cnt, void();
            // debug("cnt", cnt);
            debug(name, "received ", yourmn);
            dis[yourmn] = yourdist;
            relax(yourmn);
        } else {
            // debug(name, "mymn is", mymn);
            sendInt(mymn, PHASE2);
            assert( dis[mymn] == mydist );
            relax(mymn);
        }
        if (mydist != inf)
            sendInt(mydist - dis[last], PHASE1);
        else
            sendInt(505, PHASE1);
        init();
    }

    function<void(int)> sendBit;
    string name;

    Solver(const function<void(int)> &f, string s) : sendBit(f), name(s) {}

};

Solver Alice(SendA, "A"), Bob(SendB, "B");

void InitA(int n, int m, vector<int> a, vector<int> b, vector<int> c) {
    Alice.init(n, m, a, b, c);
}

void InitB(int n, int m, vector<int> a, vector<int> b, vector<int> c) {
    Bob.init(n, m, a, b, c);
}

void ReceiveA(bool f) {
    Alice.receive(f);
}

void ReceiveB(bool f) {
    Bob.receive(f);
}

vector<int> Answer() {
    return vector<int>(Alice.dis, Alice.dis + Alice.N);
}

