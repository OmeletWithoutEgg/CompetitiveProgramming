#include "interactive.h"
using namespace std;
#define all(v) begin(v),end(v)

vector<int> guess(int n) {
    int xn = ask(n);
    vector<int> ms[7];
    for (int b = 0; b < 7; b++) {
        vector<int> idx;
        for (int i = 1; i < n; i++) if (i >> b & 1) {
            idx.push_back(i);
        }
        auto org = get_pairwise_xor(idx);
        idx.push_back(n);
        auto jizz = get_pairwise_xor(idx);
        ms[b].assign(jizz.size() - org.size());
        org.push_back(0);
        sort(all(jizz)), sort(all(org));
        set_difference(all(jizz), all(org), ms[b].begin());
        for (int &x: ms[b]) x ^= xn;
    }
    vector<int> ans;
    for (int i = 1; i < n; i++) {
        for (int b = 0; b < 7; b++) {
            ;
        }
    }
    ans.push_back(xn);
    return ans;
}
