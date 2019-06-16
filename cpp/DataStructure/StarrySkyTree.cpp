#include <bits/stdc++.h>
using namespace std;

/*StarrySKyTree(RAQ + RMQ)
遅延セグ木の一つ。以下のことができる。
・一様加算O[logn]
    add(l, r, x) : [l, r) に +x
・連続区間での最小・最大値の取得O[logn]
    get(l, r) : [l, r) の min, max を取得
*/

//get min
struct StarrySkyTree {
    int size;
    vector<int> node, lazy;
 
    StarrySkyTree (int n) {
        size = 1;
        while (size < n) size *= 2;
        node.resize(2 * size - 1, INFLL / 2);
        lazy.resize(2 * size - 1, 0);
    }
 
    void eval(int l, int r, int k) {
        node[k] += lazy[k];
        if (r - l > 1) {
            lazy[2 * k + 1] += lazy[k];
            lazy[2 * k + 2] += lazy[k];
        }
        lazy[k] = 0;
    }
 
    void add(int L, int R, int x, int k, int nodeL, int nodeR) {
        eval(nodeL, nodeR, k);
        if (nodeR <= L || R <= nodeL) return;
        if (L <= nodeL && nodeR <= R) {
            lazy[k] += x;
            eval(nodeL, nodeR, k);
            return;
        }
        int nodeM = (nodeL + nodeR) / 2;
        add(L, R, x, 2 * k + 1, nodeL, nodeM);
        add(L, R, x, 2 * k + 2, nodeM, nodeR);
        node[k] = min(node[2 * k + 1], node[2 * k + 2]);
    }
    void add(int L, int R, int x) {
        add(L, R, x, 0, 0, size);
    } 
     
    int get(int queryL, int queryR, int k, int nodeL, int nodeR) {
        eval(nodeL, nodeR, k);
        if (nodeR <= queryL || queryR <= nodeL) return INFLL;
        if (queryL <= nodeL && nodeR <= queryR) {
            return node[k];
        }
        int nodeM = (nodeL + nodeR) / 2;
        int vl = get(queryL, queryR, 2 * k + 1, nodeL, nodeM);
        int vr = get(queryL, queryR, 2 * k + 2, nodeM, nodeR);
        return min(vl, vr);
    }
    int get(int queryL, int queryR) {
        return get(queryL, queryR, 0, 0, size);
    }
};

//get max
struct StarrySkyTree {
    int size;
    vector<int> node, lazy;
 
    StarrySkyTree (int n) {
        size = 1;
        while (size < n) size *= 2;
        node.resize(2 * size - 1, -INFLL / 2);
        lazy.resize(2 * size - 1, 0);
    }
 
    void eval(int l, int r, int k) {
        node[k] += lazy[k];
        if (r - l > 1) {
            lazy[2 * k + 1] += lazy[k];
            lazy[2 * k + 2] += lazy[k];
        }
        lazy[k] = 0;
    }
 
    void add(int L, int R, int x, int k, int nodeL, int nodeR) {
        eval(nodeL, nodeR, k);
        if (nodeR <= L || R <= nodeL) return;
        if (L <= nodeL && nodeR <= R) {
            lazy[k] += x;
            eval(nodeL, nodeR, k);
            return;
        }
        int nodeM = (nodeL + nodeR) / 2;
        add(L, R, x, 2 * k + 1, nodeL, nodeM);
        add(L, R, x, 2 * k + 2, nodeM, nodeR);
        node[k] = max(node[2 * k + 1], node[2 * k + 2]);
    }
    void add(int L, int R, int x) {
        add(L, R, x, 0, 0, size);
    } 
     
    int get(int queryL, int queryR, int k, int nodeL, int nodeR) {
        eval(nodeL, nodeR, k);
        if (nodeR <= queryL || queryR <= nodeL) return -INFLL;
        if (queryL <= nodeL && nodeR <= queryR) {
            return node[k];
        }
        int nodeM = (nodeL + nodeR) / 2;
        int vl = get(queryL, queryR, 2 * k + 1, nodeL, nodeM);
        int vr = get(queryL, queryR, 2 * k + 2, nodeM, nodeR);
        return max(vl, vr);
    }
    int get(int queryL, int queryR) {
        return get(queryL, queryR, 0, 0, size);
    }
};

signed main() {	
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    StarrySkyTree SST(n);
    rep(i, q) {
        int query;
        cin >> query;
        //query = 0 => add x to [s, t]
        if (query == 0) {
            int s, t, x;
            cin >> s >> t >> x;
            SST.add(s, t + 1, x);
        }
        //output min(s, s + 1, ..., t - 1, t)
        else {
            int s, t;
            cin >> s >> t;
            cout << SST.get(s, t + 1) << endl;
        }
    }
}
