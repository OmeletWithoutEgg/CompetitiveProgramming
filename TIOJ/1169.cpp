#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
const int maxn = 200025, inf = 1e9;

struct info {
    int ans, mn, mx;
    size_t sz;
    info () : ans(-inf), mn(-inf), mx(inf), sz(0) {}
    info (int x) : ans(0), mn(x), mx(x), sz(1) {}
    friend info operator+(const info &lhs, const info &rhs) {
        if (lhs.ans < 0) return rhs;
        if (rhs.ans < 0) return lhs;
        info res;
        res.ans = max({ lhs.ans, rhs.ans, rhs.mn - lhs.mx });
        res.mn = min(lhs.mn, rhs.mn);
        res.mx = max(lhs.mx, rhs.mx);
        res.sz = lhs.sz + rhs.sz;
        return res;
    }
};

template<class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
class node_update {
private:
    using Iterator = typename Node_Itr::value_type;
    using Key = typename iterator_traits<Iterator>::value_type;
    void __splay(Node_CItr it) {
        find(**it);
    }
public:
    typedef info metadata_type;
    void operator()(Node_Itr it, Node_CItr end_it) {
        info res((*it) -> second);
        Node_CItr lc = it.get_l_child();
        Node_CItr rc = it.get_r_child();
        if (lc != end_it)
            res = lc.get_metadata() + res;
        if (rc != end_it)
            res = res + rc.get_metadata();
        const_cast<metadata_type&>(it.get_metadata()) = res;
    }
    info query(Key L, Key R) {
        Node_CItr Lit = lower_bound(L).m_p_nd;
        Node_CItr Rit = lower_bound(R).m_p_nd;
        if (Lit == node_end() || Lit == Rit) {
            if (Lit != node_end())
                __splay(Lit);
            return info();
        }
        __splay(Lit);
        if (Rit != node_end()) {
            __splay(Rit);
            assert (Rit == node_begin());
            assert (Rit.get_l_child() == Lit);
        }
        return info((*Lit)->second)
            + (Lit.get_r_child() != node_end() ? Lit.get_r_child().get_metadata() : info());
    }
    virtual Node_CItr node_begin() const = 0;
    virtual Node_CItr node_end() const = 0;
    virtual Iterator find(const Key &) = 0;
    virtual Iterator lower_bound(const Key &) = 0;
};

using BST = __gnu_pbds::tree<pair<int,int>, __gnu_pbds::null_type, less<>, __gnu_pbds::splay_tree_tag, node_update>;
using BST_Itr = BST::iterator;

// overload std::distance for BST for efficiently split
namespace std {
    template<> iterator_traits<BST_Itr>::difference_type distance(BST_Itr begin, BST_Itr end) {
        if (begin == end)
            return 0;
        auto it = begin.m_p_nd;
        while (it->m_p_parent->m_p_parent != it)
            it = it->m_p_parent;
        return it->get_metadata().sz;
    }
}

BST tr;

int a[maxn];
signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    int n, q, C;
    cin >> n >> q >> C;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        tr.insert({ a[i], i });
    for(int i = 0; i < q; i++){
        int t;
        cin >> t;
        if (t == 0) {
            int x, k;
            cin >> x >> k;
            tr.erase({ a[x], x });
            a[x] = k;
            tr.insert({ a[x], x });
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            info res = tr.query({ k, l }, { k, r });
            if (res.ans < 0)
                cout << r - l << '\n';
            else
                cout << max({ res.ans, r - res.mx, res.mn - l + 1 }) - 1 << '\n';
        }
    }
}
