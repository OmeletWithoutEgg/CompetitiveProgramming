#include "party.h"

#include <vector>

int findUnusualGuest(int N, int M, int Q) {
    int l1 = 0, r1 = N;
    int l2 = N, r2 = N+M;
    while(l1+1 != r1 || l2+1 != r2) {
        int m1 = l1+(r1-l1)/2;
        int m2 = l2+(r2-l2)/2;
        std::vector<int> QS;
        for(int i = l1; i < m1; i++) QS.push_back(i);
        for(int i = l2; i < m2; i++) QS.push_back(i);
        auto ret = ask(QS);
        int c1 = 0, c2 = 0;
        for(int x: ret) if(x < N) ++c1;
        for(int x: ret) if(x >= N) ++c2;
        if(c2 == m1 - l1)
            l1 = m1;
        else
            r1 = m1;
        if(c1 == m2 - l2)
            l2 = m2;
        else
            r2 = m2;
    }
    auto ret = ask({ l1, l2 });
    int c1 = 0, c2 = 0;
    for(int x: ret) if(x < N) ++c1;
    for(int x: ret) if(x >= N) ++c2;
    return c1 == 1 ? l1 : l2;
}
