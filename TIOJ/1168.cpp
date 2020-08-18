#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <queue>
#include "lib1168.h"
#define ff first
#define ss second

const int N = 500001;

struct node {
    int ff, ss;
    bool operator<(const node &b)const{return ff<b.ff;}
};
struct heap {
    node v[N];
    int sz;
    void push(node x) {
        v[sz++] = x;
        std::push_heap(v,v+sz);
        if(sz >= N) sz = N-1;
    }
    node top() {return v[0];}
    void pop() {
        std::pop_heap(v,v+sz);
        --sz;
    }
} mx, mn;
int tot;
bool popped[N];
inline void push(int x) {
    mx.push({x, tot});
    mn.push({-x, tot});
    ++tot;
}
inline int big() {
    while(popped[mx.top().ss]) mx.pop();
    return mx.top().ff;
}
inline int small() {
    while(popped[mn.top().ss]) mn.pop();
    return -mn.top().ff;
}
inline void pop_big() {
    while(popped[mx.top().ss]) mx.pop();
    popped[mx.top().ss] = 1;
    mx.pop();
}
inline void pop_small() {
    while(popped[mn.top().ss]) mn.pop();
    popped[mn.top().ss] = 1;
    mn.pop();
}
